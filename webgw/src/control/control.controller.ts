import { BadRequestException, Controller, Param, Post } from '@nestjs/common';
import { SerialService } from 'src/serial/serial.service';

@Controller('control')
export class ControlController {
  constructor(private readonly serialService: SerialService) {}

  @Post(`/stop`)
  async postStop() {
    return this.serialService.sendStop();
  }

  @Post(`refresh`)
  async postRefresh() {
    return this.serialService.sendRefresh();
  }

  @Post(`pump/:index/:state`)
  async setPumpState(
    @Param('index') indexRaw: string,
    @Param('state') stateRaw: string,
  ) {
    const index = Number(indexRaw);
    const state = Number(stateRaw);

    if (!Number.isInteger(index) || index < 0) {
      throw new BadRequestException('Parameter index must be integer >= 0.');
    }

    if (!Number.isInteger(state) || (state !== 0 && state !== 1)) {
      throw new BadRequestException('Parameter state must be 0 or 1.');
    }

    return this.serialService.sendPumpState(index, state);
  }
}
