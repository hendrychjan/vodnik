### AT commands

### Input

| Command                | Example    | Description                                                                                           |
| ---------------------- | ---------- | ----------------------------------------------------------------------------------------------------- |
| `pump <index> <state>` | `pump 2 1` | For state `0` clears the queued time for pump `index`, for state `1` it adds one cycle to it's queue. |
| `refresh`              | `refresh`  | Triggers an immediate refresh of sensors.                                                             |
| `stop`                 | `stop`     | Clears all pump time queues.                                                                          |

### Output

| Command                    | Example                                                   | Description                                                    |
| -------------------------- | --------------------------------------------------------- | -------------------------------------------------------------- |
| `err <function> <message>` | `err getPumpRemainingTimeQueued Pump index out of bounds` | An error and the function the error comes from.                |
| `soil <index> <value>`     | `soil 1 80`                                               | The `value` % humidity in soil sensor of `index` index.        |
| `pump <index> <state>`     | `pump 2 1`                                                | The `state` (1 = on, 0 = off) change on pump of `index` index. |
| `reservoir <distance>`     | `reservoir 40`                                            | The `distance` to water level measured in the water reservoir. |
