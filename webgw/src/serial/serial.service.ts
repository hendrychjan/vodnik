import {
  Inject,
  Injectable,
  Logger,
  OnModuleDestroy,
  OnModuleInit,
  forwardRef,
} from '@nestjs/common';
import { ReadlineParser } from '@serialport/parser-readline';
import { SerialPort } from 'serialport';
import { ConfigService } from 'src/config/config.service';
import { MqttService } from 'src/mqtt/mqtt.service';
import { StatusService } from 'src/status/status.service';

@Injectable()
export class SerialService implements OnModuleInit, OnModuleDestroy {
  private readonly logger: Logger = new Logger(SerialService.name);
  private serialPort?: SerialPort;
  private reconnectTimer?: NodeJS.Timeout;
  private isShuttingDown = false;
  private readonly reconnectDelayMs = 2000;

  constructor(
    private readonly configService: ConfigService,
    private readonly mqttService: MqttService,
    @Inject(forwardRef(() => StatusService))
    private readonly statusService: StatusService,
  ) {}

  onModuleInit(): void {
    this.initPort();
    this.tryOpenPort();
  }

  async onModuleDestroy(): Promise<void> {
    this.isShuttingDown = true;

    if (this.reconnectTimer) {
      clearTimeout(this.reconnectTimer);
      this.reconnectTimer = undefined;
    }

    if (!this.serialPort || !this.serialPort.isOpen) {
      return;
    }

    await new Promise<void>((resolve, reject) => {
      this.serialPort!.close((error) => {
        if (error) {
          reject(error);
          return;
        }

        resolve();
      });
    });

    this.logger.log('Serial port closed.');
  }

  public isHealthy(): boolean {
    return this.serialPort?.isOpen === true;
  }

  public sendStop(): Promise<SendCommandResult> {
    return this.safeWrite('stop');
  }

  public sendRefresh(): Promise<SendCommandResult> {
    return this.safeWrite('refresh');
  }

  public sendPumpState(
    index: number,
    state: number,
  ): Promise<SendCommandResult> {
    const command = `pump ${index} ${state}`;
    return this.safeWrite(command);
  }

  private safeWrite(command: string): Promise<SendCommandResult> {
    if (!this.serialPort || !this.serialPort.isOpen) {
      const reason = 'serial port is not open';
      this.logger.error(`Cannot send command '${command}': ${reason}.`);
      return Promise.resolve({ success: false, command, reason });
    }

    return new Promise<SendCommandResult>((resolve) => {
      this.serialPort!.write(`${command}\n`, (error) => {
        if (error) {
          this.logger.error(
            `Failed to send command '${command}' to serial port: ${error.message}`,
            error.stack,
          );
          resolve({ success: false, command, reason: error.message });
          return;
        }

        this.logger.debug(`Sent serial command '${command}'`);
        resolve({ success: true, command });
      });
    });
  }

  private initPort(): void {
    const { serialDevice, baudRate } = this.configService.serial;

    this.serialPort = new SerialPort({
      path: serialDevice,
      baudRate,
      autoOpen: false,
    });

    this.serialPort.on('open', () => {
      this.logger.log(
        `Listening for serial messages on ${serialDevice} at ${baudRate} baud.`,
      );
    });

    this.serialPort.on('error', (error: Error) => {
      this.logger.error(`Serial port error: ${error.message}`, error.stack);
      this.scheduleReconnect();
    });

    this.serialPort.on('close', () => {
      this.logger.warn('Serial port connection closed.');
      this.scheduleReconnect();
    });

    this.serialPort
      .pipe(new ReadlineParser({ delimiter: '\n' }))
      .on('data', (chunk: Buffer | string) => {
        const message = chunk.toString().replace(/\r$/, '');
        this.logger.debug(
          `Received serial message: ${JSON.stringify(message)}`,
        );
        void this.handleMessage(message);
      });
  }

  private tryOpenPort(): void {
    if (!this.serialPort || this.isShuttingDown || this.serialPort.isOpen) {
      return;
    }

    this.serialPort.open((error) => {
      if (!error) {
        return;
      }

      this.logger.error(
        `Failed to open serial port: ${error.message}. Retrying in ${this.reconnectDelayMs}ms.`,
        error.stack,
      );
      this.scheduleReconnect();
    });
  }

  private scheduleReconnect(): void {
    if (this.isShuttingDown || this.reconnectTimer) {
      return;
    }

    this.reconnectTimer = setTimeout(() => {
      this.reconnectTimer = undefined;
      this.tryOpenPort();
    }, this.reconnectDelayMs);
  }

  private async handleMessage(message: string): Promise<void> {
    let parsed: {
      topic: string;
      payload: string;
    } | null;
    try {
      parsed = this.parseMessage(message);

      if (!parsed) return;
    } catch (e) {
      this.logger.error('Failed to handle serial message.', e);
      return;
    }

    try {
      await this.mqttService.sendMessage(parsed.topic, parsed.payload);
    } catch (error) {
      const err = error as Error;
      this.logger.error(
        'Failed to publish MQTT message for serial message.',
        err.message,
        err.stack,
      );
    }
  }

  private parseMessage(
    message: string,
  ): { topic: string; payload: string } | null {
    const trimmed = message.trim();
    if (!trimmed) {
      throw new Error('Empty serial message.');
    }

    const parts = trimmed.split(/\s+/);
    const command = parts[0]?.toLowerCase();

    switch (command) {
      case 'pump': {
        if (parts.length !== 3) {
          throw new Error(`Bad serial message: ${message}`);
        }

        const index = Number(parts[1]);
        const state = Number(parts[2]);

        if (!Number.isInteger(index) || (state !== 0 && state !== 1)) {
          throw new Error(`Bad serial message: ${message}`);
        }

        this.statusService.setPump(index, state);

        return { topic: `vodnik/pump/${index}`, payload: state.toString() };
      }
      case 'soil': {
        if (parts.length !== 3) {
          throw new Error(`Bad serial message: ${message}`);
        }

        const index = Number(parts[1]);
        const value = Number(parts[2]);

        this.statusService.setSoilSensor(index, value);

        if (!Number.isInteger(index) || !Number.isFinite(value)) {
          throw new Error(`Bad serial message: ${message}`);
        }

        return { topic: `vodnik/soil/${index}`, payload: value.toString() };
      }
      case 'reservoir': {
        if (parts.length !== 2) {
          throw new Error(`Bad serial message: ${message}`);
        }

        const distance = Number(parts[1]);

        this.statusService.setReservoir(distance);

        if (!Number.isFinite(distance)) {
          throw new Error(`Bad serial message: ${message}`);
        }

        return { topic: `vodnik/reservoir`, payload: distance.toString() };
      }
      case 'err': {
        this.statusService.addArdError(message);

        this.logger.error('Arduino error:', message);
        return null;
      }
      default:
        throw new Error(`Bad serial message: ${message}`);
    }
  }
}

type SendCommandResult =
  | {
      success: true;
      command: string;
    }
  | {
      success: false;
      command: string;
      reason: string;
    };
