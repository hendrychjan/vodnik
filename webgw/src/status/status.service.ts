import { Inject, Injectable, Logger, forwardRef } from '@nestjs/common';
import { ApplicationStatus, VodnikStatus } from './entities/status.entity';
import { MqttService } from 'src/mqtt/mqtt.service';
import { SerialService } from 'src/serial/serial.service';

@Injectable()
export class StatusService {
  private readonly logger: Logger = new Logger(StatusService.name);

  constructor(
    private readonly mqttService: MqttService,
    @Inject(forwardRef(() => SerialService))
    private readonly serialService: SerialService,
  ) {}

  private vodnikStatus: VodnikStatus = {
    reservoir: 0,
    pumps: [0, 0, 0],
    soilSensors: [0, 0, 0, 0, 0, 0],
    ardErrors: [],
  };

  public setReservoir(value: number) {
    this.vodnikStatus.reservoir = value;
  }

  public setPump(index: number, value: number) {
    if (index >= this.vodnikStatus.pumps.length) {
      this.logger.error(
        `Failed to update pump state: index ${index} out of range.`,
      );
      return;
    }

    this.vodnikStatus.pumps[index] = value;
  }

  public setSoilSensor(index: number, value: number) {
    if (index >= this.vodnikStatus.soilSensors.length) {
      this.logger.error(
        `Failed to update soil sensor state: index ${index} out of range.`,
      );
      return;
    }

    this.vodnikStatus.soilSensors[index] = value;
  }

  public addArdError(error: string) {
    if (this.vodnikStatus.ardErrors.length >= 100) {
      // Maximum of 100 errors are kept
      this.vodnikStatus.ardErrors.shift();
    }

    this.vodnikStatus.ardErrors.push(error);
  }

  public getStatus(): ApplicationStatus {
    return {
      vodnik: this.vodnikStatus,
      mqtt: this.mqttService.isHealthy(),
      serial: this.serialService.isHealthy(),
    };
  }
}
