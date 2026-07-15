import { forwardRef, Module } from '@nestjs/common';
import { MqttModule } from 'src/mqtt/mqtt.module';
import { SerialModule } from 'src/serial/serial.module';
import { StatusService } from './status.service';
import { StatusController } from './status.controller';

@Module({
  imports: [MqttModule, forwardRef(() => SerialModule)],
  providers: [StatusService],
  controllers: [StatusController],
  exports: [StatusService],
})
export class StatusModule {}
