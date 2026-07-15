import { forwardRef, Module } from '@nestjs/common';
import { MqttModule } from 'src/mqtt/mqtt.module';
import { StatusModule } from 'src/status/status.module';
import { SerialService } from './serial.service';

@Module({
  imports: [MqttModule, forwardRef(() => StatusModule)],
  providers: [SerialService],
  exports: [SerialService],
})
export class SerialModule {}
