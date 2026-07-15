import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { join } from 'path';
import { NestExpressApplication } from '@nestjs/platform-express';

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);

  app.enableShutdownHooks();

  const isProd = process.env.NODE_ENV === 'production';

  app.useLogger(
    isProd
      ? ['error', 'warn', 'log']
      : ['log', 'error', 'warn', 'debug', 'verbose'],
  );

  app.setViewEngine('pug');
  app.setBaseViewsDir(join(__dirname, '..', 'views'));

  await app.listen(process.env.PORT ?? 3000);
}
void bootstrap();
