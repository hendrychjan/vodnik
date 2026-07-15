import { z } from 'zod';

const mqttConfigurationSchema = z.object({
  url: z.url(),
  username: z.string(),
  password: z.string(),
});

const serialConfigurationSchema = z.object({
  serialDevice: z.string(),
  baudRate: z.number(),
});

export const configurationSchema = z.object({
  mqttConfig: mqttConfigurationSchema,
  serialConfig: serialConfigurationSchema,
});

export type Configuration = z.infer<typeof configurationSchema>;
export type MqttConfiguration = z.infer<typeof mqttConfigurationSchema>;
export type SerialConfiguration = z.infer<typeof serialConfigurationSchema>;
