import { Module } from '@nestjs/common';
import { ControlController } from './control.controller';
import { SerialModule } from 'src/serial/serial.module';

@Module({
  imports: [SerialModule],
  controllers: [ControlController],
})
export class ControlModule {}
