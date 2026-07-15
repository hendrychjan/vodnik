import { Module } from '@nestjs/common';
import { SerialModule } from './serial/serial.module';
import { ConfigModule } from './config/config.module';
import { MqttModule } from './mqtt/mqtt.module';
import { StatusModule } from './status/status.module';
import { ControlModule } from './control/control.module';

@Module({
  imports: [
    ConfigModule,
    SerialModule,
    MqttModule,
    StatusModule,
    ControlModule,
  ],
  controllers: [],
  providers: [],
})
export class AppModule {}
