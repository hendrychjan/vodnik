ARG NODE_VERSION=24.16.0

FROM node:${NODE_VERSION}-bookworm-slim AS builder

WORKDIR /usr/src/app

RUN apt-get update \
    && apt-get install -y --no-install-recommends python3 make g++ pkg-config libudev-dev \
    && rm -rf /var/lib/apt/lists/*

COPY package*.json ./

RUN --mount=type=cache,target=/root/.npm \
    npm ci

COPY . .

RUN npm run build


FROM node:${NODE_VERSION}-bookworm-slim

ARG PORT=3001

ENV NODE_ENV=production
ENV PORT=${PORT}

WORKDIR /usr/src/app

RUN apt-get update \
    && apt-get install -y --no-install-recommends libudev1 \
    && rm -rf /var/lib/apt/lists/*

COPY package*.json ./

RUN --mount=type=cache,target=/root/.npm \
    npm ci --omit=dev

COPY --from=builder /usr/src/app/dist ./dist
COPY --from=builder /usr/src/app/views ./views

EXPOSE ${PORT}

USER node

CMD ["node", "dist/main.js"]