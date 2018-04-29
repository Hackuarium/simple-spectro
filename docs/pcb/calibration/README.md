# Callibration of the RGB leds

The sensor is able to generate a frequency of maximum 500 kHz and that is directly proportional to the energy of the light.

In order to use the full range of frequency it is important to be at the limit of 500 kHz by changing the 3 resistors that limit the current to the leds.

By default the resistors are 1k.

Example (on D1)

| R red | Red (Hz) | R green | Green (Hz) | R blue | Blue (Hz) | R uv | UV (Hz) |
|-------|----------|---------|------------|--------|-----------|------|---------|
| 1k    | 95240    | 1k      | 185230     | 1k     | 201170    | 22   | 9940    |
| 330   | 276500   | 330     | 416200     | 470    | 383320    |      |         |
| 220   | 383700   |         |            | 330    | 506290    |      |         |

Example (on D3)

| R red | Red (Hz) | R green | Green (Hz) | R blue | Blue (Hz) | R uv | UV (Hz) |
|-------|----------|---------|------------|--------|-----------|------|---------|
| 1k    | 53670    | 1k      | 124882     | 1k     | 62626     | 22   | 11059   |
| 150   | 326653   | 330     | 290518     | 220    | 304900    |      |         |

