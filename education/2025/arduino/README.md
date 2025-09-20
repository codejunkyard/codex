# Arduino Nano ESP32 8x8 LED Matrix Demo

This example sketch drives a classic 8x8 LED matrix directly from an **Arduino Nano ESP32**, multiplexing the rows and columns to create an eye-catching animation loop. Three scenes run in sequence:

1. **Spiral comet** that traces the perimeter and then dives toward the center.
2. **Ocean wave** made from sine curves sweeping across the grid.
3. **Sparkling stars** that twinkle randomly before the cycle restarts.

## Hardware assumptions

- An 8x8 LED matrix wired with its **rows on the anode side** and **columns on the cathode side** (common-cathode columns).
- Each row and column line is connected through an appropriate current-limiting resistor or driver stage.
- The matrix is multiplexed directly from 16 GPIO pins of the Nano ESP32. Adjust the `rowPins` and `colPins` arrays in `nano_esp32_led_matrix.ino` if you use different wiring or transistor drivers.

> 💡 If your matrix is wired the opposite way (common-cathode rows / common-anode columns), invert the logic inside `refreshDisplay()` so that the active row is driven LOW and active columns are driven HIGH.

## Wiring reference

| Matrix connection | Nano ESP32 pin (default) |
|-------------------|---------------------------|
| Rows R0..R7       | D2, D3, D4, D5, D6, D7, D8, D9 |
| Columns C0..C7    | D10, D11, D12, D13, A0, A1, A2, A3 |

Feel free to remap these pins to match your build. Keep the row set on one side of the board and the column set on the other to simplify the refresh routine.

## Uploading the sketch

1. Open `nano_esp32_led_matrix.ino` in the Arduino IDE or Arduino CLI environment.
2. Select **Arduino Nano ESP32** as the target board and choose the correct serial port.
3. Compile and upload. Once the board resets you should see the animation cycle endlessly.

## Customizing the show

- **Brightness**: change `ROW_HOLD_MICROS`. Longer hold times increase brightness but can introduce flicker.
- **Animation speed**: tweak the timing constants inside `runAnimation()` (e.g., 80 ms for the spiral step, 60 ms for the wave step).
- **Effects**: add your own scene by extending the `AnimationPhase` enum and adding a new renderer.

Enjoy turning the 8x8 grid into a mini light show!
