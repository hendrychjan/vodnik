import { Controller, Get, Render } from '@nestjs/common';
import { StatusService } from './status.service';
import { type ApplicationStatus } from './entities/status.entity';

@Controller('status')
export class StatusController {
  constructor(private readonly statusService: StatusService) {}

  @Get('/raw')
  getStatus(): ApplicationStatus {
    return this.statusService.getStatus();
  }

  @Get()
  @Render('status')
  getStatusView() {
    return this.statusService.getStatus();
  }
}
