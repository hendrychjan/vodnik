# WebGW

Web gateway for Vodnik. It listens to MQTT, reads the serial line connected to the Arduino, and exposes status and control endpoints.

## Development

### Prerequisites

The app expects these environment variables:

```bash
PORT=3001
MQTT_URL=mqtt://localhost:1883
MQTT_USERNAME=test
MQTT_PASSWORD=pass
SERIAL_DEVICE=/dev/ttyUSB0
SERIAL_BAUD_RATE=9600
```

### Useful commands

```bash
npm install
npm run start:dev
npm run build
npm run test
```

## Docker

The repository contains a production `Dockerfile` and a `.dockerignore` tuned for the NestJS build.

An example compose file is available as `example.docker-compose.yaml`.

Build the image for the `pha` registry location:

```bash
docker build \
  --no-cache \
  --platform=linux/amd64 \
  --tag registry.ws.pha.vpn/webgw:v \
  .
```

Run the container with the serial device passed through from the host:

```bash
docker run \
  --rm \
  --env-file .env \
  --device=/dev/ttyUSB0:/dev/ttyUSB0 \
  -p 3001:3001 \
  registry.ws.pha.vpn/webgw:v
```

If the serial device path differs on the host, update both `SERIAL_DEVICE` and the `--device` mapping.

To start from compose:

```bash
docker compose -f example.docker-compose.yaml up -d
```

## Endpoints

- `GET /status`
- `GET /status/raw`
- `POST /control/stop`
- `POST /control/refresh`
- `POST /control/pump/:index/:state`
