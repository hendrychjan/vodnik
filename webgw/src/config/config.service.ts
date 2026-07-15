import { Injectable, Logger } from '@nestjs/common';
import {
  Configuration,
  MqttConfiguration,
  SerialConfiguration,
} from './entities/configuration.entity';
import { z } from 'zod';
import { configDotenv } from 'dotenv';

@Injectable()
export class ConfigService {
  private readonly config: Configuration;
  private readonly logger: Logger = new Logger(ConfigService.name);

  constructor() {
    this.loadDotenv();

    this.config = this.parseAndMerge();
  }

  private loadDotenv() {
    configDotenv();

    this.validateEnv();
  }

  private validateEnv() {
    const check = (key: string) => {
      const validationRes = z.string().safeParse(process.env[key]);
      if (!validationRes.success) {
        this.logger.fatal(
          `Failed to load environment variable ${key}, the issue is:`,
          validationRes.error,
        );
        throw validationRes.error;
      }
    };

    check('MQTT_URL');
    check('MQTT_USERNAME');
    check('MQTT_PASSWORD');
    check('SERIAL_DEVICE');

    const baudRateValidation = z.coerce
      .number()
      .int()
      .positive()
      .safeParse(process.env.SERIAL_BAUD_RATE);

    if (!baudRateValidation.success) {
      this.logger.fatal(
        'Failed to load environment variable SERIAL_BAUD_RATE, the issue is:',
        baudRateValidation.error,
      );
      throw baudRateValidation.error;
    }
  }

  private parseAndMerge(): Configuration {
    const baudRate = Number.parseInt(process.env.SERIAL_BAUD_RATE!, 10);

    const config: Configuration = {
      mqttConfig: {
        url: process.env.MQTT_URL!,
        username: process.env.MQTT_USERNAME!,
        password: process.env.MQTT_PASSWORD!,
      },
      serialConfig: {
        serialDevice: process.env.SERIAL_DEVICE!,
        baudRate,
      },
    };

    this.logger.log(`Loaded configuration.`);

    return config;
  }

  get(): Configuration {
    return this.config;
  }

  get mqtt(): MqttConfiguration {
    return this.config.mqttConfig;
  }

  get serial(): SerialConfiguration {
    return this.config.serialConfig;
  }
}
