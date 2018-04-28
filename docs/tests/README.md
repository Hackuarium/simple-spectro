# Expected voltages for USB powered without battery

Testing points are marked on the eagle file and are between ground and the specific point:

* A: 5.01v
* B: 4.78v
* C: 4.55v
* D: 3.35v
* E: 2.92v
* F: 0.23v
* G: 0.35v
* H: 0.86v
* I: 0.86v
* J: 0.05v
* K: 0.00v
* L: 3.25v
* M; 0.81v
* N: 2.90v

# Callibration of the RGB leds

The sensor is able to generate a frequency of maximum 500 kHz and that is directly proportional to the energy of the light.

In order to use the full range of frequency it is important to be at the limit of 500 kHz by changing the 3 resistors that limit the current to the leds.

By default the resistors are 1k.

Example

| R red | Red (Hz) | R green | Green  | R blue | Blue   | R uv | UV   |
| ------|----------|--------|--------|--------|
| 1k    | 95240 | 1k |  185230 | 1k  | 201170 | 22 | 9940



