# Calibration of the RGB leds

The light sensor generates a frequency that is directly proportional to the energy of the light, with a maximal value of 500 kHz.

In order to use the full range of frequencies, it is important to be at the closest possible to 500 kHz when testing with a water sample (indeed, more light goes through when a water sample is inserted than when there is no sample at all). To modify the intensity of the LEDs, change the 3 resistors labelled R, G and B.

<img src='pcb-description.001.jpeg' width='600' />

By default the resistors are 1k which prevents any saturation.

There is a special mode designed to calibrate the resistors: menu -> Utilities -> Test LEDs.

If the resistors are not strong enough the sensor will saturate and a value just over 50000 will appear (only one acquisition is done instead of 10, which means the LEDs only blink once). A correct value should be somewhere between 350'000 and 450'000.

### Example (on D1)

| R red | Red (Hz) | R green | Green (Hz) | R blue | Blue (Hz) | R uv | UV (Hz) |
| ----- | -------- | ------- | ---------- | ------ | --------- | ---- | ------- |
| 1k    | 95240    | 1k      | 185230     | 1k     | 201170    | 22   | 9940    |
| 330   | 276500   | 330     | 416200     | 470    | 383320    |      |         |
| 220   | 383700   |         |            | 330    | 506290    |      |         |

### Example (on D3)

| R red | Red (Hz) | R green | Green (Hz) | R blue | Blue (Hz) | R uv | UV (Hz) |
| ----- | -------- | ------- | ---------- | ------ | --------- | ---- | ------- |
| 1k    | 53670    | 1k      | 124882     | 1k     | 62626     | 22   | 11059   |
| 150   | 326653   | 330     | 290518     | 220    | 304900    |      |         |

### Example (on D4)

| R red | Red (Hz)                      | R green | Green (Hz) | R blue | Blue (Hz) | R uv | UV (Hz) |
| ----- | ----------------------------- | ------- | ---------- | ------ | --------- | ---- | ------- |
| 1k    | 97830                         | 1k      | 245500     | 1k     | 142391    | 22   | 74888   |
| 150   | Problem, just one blink 53513 | 470     | 430676     | 330    | 352858    |      |         |

### Example (on D5)

| R red | Red (Hz)        | R green | Green (Hz)         | R blue | Blue (Hz)       | R uv | UV (Hz) |
| ----- | --------------- | ------- | ------------------ | ------ | --------------- | ---- | ------- |
| 1k    | 103874          | 1k      | 295699             | 1k     | 243137          | 22   | 11484   |
| 150   | problem 1 blink | 330     | problem 1 blink    | 330    | problem 1 blink |      |         |
