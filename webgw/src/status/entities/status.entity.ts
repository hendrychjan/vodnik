import { z } from 'zod';

const vodnikStatusSchema = z.object({
  reservoir: z.number(),
  pumps: z.array(z.number()),
  soilSensors: z.array(z.number()),
  ardErrors: z.array(z.string()),
});

export const applicationStatusSchema = z.object({
  vodnik: vodnikStatusSchema,
  mqtt: z.boolean(),
  serial: z.boolean(),
});

export type VodnikStatus = z.infer<typeof vodnikStatusSchema>;
export type ApplicationStatus = z.infer<typeof applicationStatusSchema>;
