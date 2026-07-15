import {
  Injectable,
  Logger,
  OnModuleDestroy,
  OnModuleInit,
} from '@nestjs/common';
import mqtt, { MqttClient } from 'mqtt';
import { ConfigService } from 'src/config/config.service';

@Injectable()
export class MqttService implements OnModuleInit, OnModuleDestroy {
  private client!: MqttClient;
  private readonly logger: Logger = new Logger(MqttService.name);

  constructor(private readonly configService: ConfigService) {}

  onModuleInit() {
    this.connectToBroker();
    this.initBrokerHandlers();
  }

  onModuleDestroy() {
    this.disconnectBroker();
  }

  public isHealthy(): boolean {
    const hasClient = !!this.client;
    const isConnected = this.client?.connected === true;

    return hasClient && isConnected;
  }

  public async sendMessage(topic: string, data: string) {
    this.logger.debug(`Publishing data ${data} on topic ${topic}`);
    return this.client.publishAsync(topic, data);
  }

  private disconnectBroker() {
    this.client.end();
  }

  private connectToBroker() {
    const connectionConfig = this.configService.mqtt;

    this.client = mqtt.connect(connectionConfig.url, {
      username: connectionConfig.username,
      password: connectionConfig.password,
    });
  }

  private initBrokerHandlers() {
    this.client.on('connect', () => {
      this.logger.log('MQTT broker connected');
    });

    this.client.on('error', (err) => {
      this.logger.error('MQTT error', err);
    });

    this.client.on('reconnect', () => {
      this.logger.warn('MQTT reconnecting');
    });

    this.client.on('offline', () => {
      this.logger.warn('MQTT offline');
    });

    this.client.on('close', () => {
      this.logger.warn('MQTT closed connection');
    });
  }
}
