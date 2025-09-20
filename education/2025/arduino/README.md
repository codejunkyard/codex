# Arduino Nano ESP32 8x8 LED Matrix Demo

This example sketch drives a classic 8x8 **NeoPixel-compatible** LED matrix from an Arduino Nano ESP32. Three scenes run in sequence:

1. **Spiral comet** that traces the perimeter and then dives toward the center.
2. **Ocean wave** made from sine curves sweeping across the grid.
3. **Sparkling stars** that twinkle randomly before the cycle restarts.

## Hardware assumptions

- The matrix is built from WS2812, SK6812, or another single-wire addressable LED technology (three-pin connector: 5V, GND, DIN).
- The matrix is arranged as an 8×8 serpentine grid where neighbouring columns run in opposite directions. If your wiring differs, adjust `xyToIndex()` inside `nano_esp32_led_matrix.ino`.
- A common 5 V supply powers both the board and the matrix. Make sure to connect the grounds.

## Wiring reference

| Matrix connection | Nano ESP32 pin (default) |
|-------------------|---------------------------|
| DIN               | D6                        |
| 5V                | 5V                        |
| GND               | GND                       |

Feel free to move the data line to another digital-capable pin by changing `DATA_PIN` in `nano_esp32_led_matrix.ino`.

## Software setup

1. Install the **Adafruit NeoPixel** library (Sketch → Include Library → Manage Libraries… → search for “Adafruit NeoPixel”).
2. Open `nano_esp32_led_matrix.ino` in the Arduino IDE or Arduino CLI environment.
3. Select **Arduino Nano ESP32** as the target board and choose the correct serial port.
4. Compile and upload. Once the board resets you should see the animation cycle endlessly.

## Customizing the show

- **Brightness**: adjust `strip.setBrightness()` in `setup()`. Lower values reduce current draw.
- **Data pin**: change the `DATA_PIN` constant if you wired the matrix to a different IO.
- **Orientation**: edit `xyToIndex()` to match your panel’s wiring pattern.
- **Effects**: add your own scene by extending the `AnimationPhase` enum and adding a new renderer.

Enjoy turning the 8x8 grid into a mini light show!
