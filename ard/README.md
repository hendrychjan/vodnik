### AT commands

### Output

| Command                    | Example                                                   | Description                                                                            |
| -------------------------- | --------------------------------------------------------- | -------------------------------------------------------------------------------------- |
| `err <function> <message>` | `err getPumpRemainingTimeQueued Pump index out of bounds` | An error and the function the error comes from.                                        |
| `mode <value>`             | `mode 1`                                                  | The mode that the system is set to operate in (`1` for automatic and `2` for override) |
| `soil <index> <value>`     | `soil 1 80`                                               | The `value` % humidity in soil sensor of `index` index.                                |
| `pump <index> <state>`     | `pump 2 1`                                                | The `state` (1 = on, 0 = off) change on pump of `index` index.                         |
