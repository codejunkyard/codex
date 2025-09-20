#include <Arduino.h>
#include <math.h>
#include <Adafruit_NeoPixel.h>

// 8x8 NeoPixel matrix driven from a single data pin. Adjust DATA_PIN if you
// soldered the signal wire to a different GPIO on the Nano ESP32.
const uint8_t DATA_PIN = 6;

const uint8_t NUM_ROWS = 8;
const uint8_t NUM_COLS = 8;
const uint16_t NUM_PIXELS = NUM_ROWS * NUM_COLS;

// Most WS2812 / SK6812 matrices use GRB order running at 800 KHz.
Adafruit_NeoPixel strip(NUM_PIXELS, DATA_PIN, NEO_GRB + NEO_KHZ800);

// In-memory frame buffer storing the color for each LED.
static uint32_t frameBuffer[NUM_PIXELS];

enum AnimationPhase {
  PHASE_SPIRAL = 0,
  PHASE_WAVE,
  PHASE_SPARKLE
};

AnimationPhase currentPhase = PHASE_SPIRAL;
unsigned long phaseStartTime = 0;
unsigned long lastFrameTime = 0;

uint8_t spiralIndex = 0;
uint8_t spiralLoops = 0;

uint16_t waveStep = 0;
uint8_t waveLoops = 0;

uint8_t sparkleFrame = 0;

// Spiral path that walks the entire matrix from the outside in.
const uint8_t SPIRAL_PATH_LENGTH = 64;
const uint8_t spiralPath[SPIRAL_PATH_LENGTH][2] = {
  {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7},
  {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7},
  {7, 6}, {7, 5}, {7, 4}, {7, 3}, {7, 2}, {7, 1}, {7, 0},
  {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0},
  {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
  {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6},
  {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1},
  {5, 1}, {4, 1}, {3, 1}, {2, 1},
  {2, 2}, {2, 3}, {2, 4}, {2, 5},
  {3, 5}, {4, 5}, {5, 5},
  {5, 4}, {5, 3}, {5, 2},
  {4, 2}, {3, 2}, {3, 3}, {3, 4}, {4, 4}, {4, 3},
};

void clearBuffer() {
  memset(frameBuffer, 0, sizeof(frameBuffer));
}

// Convert a row/column pair into the NeoPixel index. Most 8x8 matrices are
// wired in a serpentine layout where adjacent columns run in opposite
// directions. Flip the logic here if your panel is wired differently.
uint16_t xyToIndex(uint8_t row, uint8_t col) {
  if (col % 2 == 0) {
    return (col * NUM_ROWS) + row;
  }
  return (col * NUM_ROWS) + (NUM_ROWS - 1 - row);
}

void setPixel(uint8_t row, uint8_t col, uint32_t color) {
  if (row >= NUM_ROWS || col >= NUM_COLS) {
    return;
  }
  frameBuffer[xyToIndex(row, col)] = color;
}

uint32_t makeColor(uint8_t r, uint8_t g, uint8_t b) {
  return strip.Color(r, g, b);
}

void pushBuffer() {
  for (uint16_t i = 0; i < NUM_PIXELS; ++i) {
    strip.setPixelColor(i, frameBuffer[i]);
  }
  strip.show();
}

void renderSpiral(uint8_t headIndex) {
  clearBuffer();
  const uint8_t tailLength = 10;
  for (uint8_t i = 0; i < tailLength; ++i) {
    uint8_t index = (headIndex + SPIRAL_PATH_LENGTH - i) % SPIRAL_PATH_LENGTH;
    uint8_t row = spiralPath[index][0];
    uint8_t col = spiralPath[index][1];
    uint8_t intensity = 20 + (tailLength - i) * 12;
    setPixel(row, col, makeColor(intensity, intensity / 4, 0));
  }
  pushBuffer();
}

void renderWave(uint16_t step) {
  clearBuffer();
  for (uint8_t col = 0; col < NUM_COLS; ++col) {
    float angle = (step * 0.32f) + (col * 0.55f);
    float normalized = (sinf(angle) + 1.0f) * 3.5f; // Map -1..1 to 0..7.
    uint8_t primaryRow = static_cast<uint8_t>(normalized + 0.5f);
    if (primaryRow > 7) {
      primaryRow = 7;
    }
    setPixel(primaryRow, col, makeColor(0, 0, 150));

    int secondaryRow = primaryRow + (sinf(angle + 1.2f) > 0 ? 1 : -1);
    if (secondaryRow >= 0 && secondaryRow < NUM_ROWS) {
      setPixel(static_cast<uint8_t>(secondaryRow), col, makeColor(0, 40, 120));
    }
  }
  pushBuffer();
}

void renderSparkle(uint8_t frame) {
  (void)frame;
  clearBuffer();
  const uint8_t sparkleCount = 14;
  for (uint8_t i = 0; i < sparkleCount; ++i) {
    uint8_t row = random(NUM_ROWS);
    uint8_t col = random(NUM_COLS);
    uint8_t hue = random(3);
    uint32_t color = 0;
    switch (hue) {
      case 0:
        color = makeColor(120, 120, 20);
        break;
      case 1:
        color = makeColor(30, 0, 140);
        break;
      default:
        color = makeColor(0, 80, 150);
        break;
    }
    setPixel(row, col, color);
  }
  pushBuffer();
}

void nextPhase(AnimationPhase newPhase) {
  currentPhase = newPhase;
  phaseStartTime = millis();
  lastFrameTime = phaseStartTime;

  switch (currentPhase) {
    case PHASE_SPIRAL:
      spiralIndex = 0;
      spiralLoops = 0;
      renderSpiral(spiralIndex);
      break;
    case PHASE_WAVE:
      waveStep = 0;
      waveLoops = 0;
      renderWave(waveStep);
      break;
    case PHASE_SPARKLE:
      sparkleFrame = 0;
      renderSparkle(sparkleFrame);
      break;
  }
}

void runAnimation() {
  unsigned long now = millis();

  switch (currentPhase) {
    case PHASE_SPIRAL:
      if (now - lastFrameTime >= 80) {
        lastFrameTime = now;
        spiralIndex = (spiralIndex + 1) % SPIRAL_PATH_LENGTH;
        if (spiralIndex == 0) {
          ++spiralLoops;
          if (spiralLoops >= 3) {
            nextPhase(PHASE_WAVE);
            return;
          }
        }
        renderSpiral(spiralIndex);
      }
      break;

    case PHASE_WAVE:
      if (now - lastFrameTime >= 60) {
        lastFrameTime = now;
        ++waveStep;
        renderWave(waveStep);
        if (waveStep % 64 == 0) {
          ++waveLoops;
          if (waveLoops >= 4) {
            nextPhase(PHASE_SPARKLE);
            return;
          }
        }
      }
      break;

    case PHASE_SPARKLE:
      if (now - lastFrameTime >= 120) {
        lastFrameTime = now;
        ++sparkleFrame;
        renderSparkle(sparkleFrame);
        if (now - phaseStartTime >= 8000) {
          nextPhase(PHASE_SPIRAL);
          return;
        }
      }
      break;
  }
}

void setup() {
  strip.begin();
  strip.setBrightness(80); // Master brightness scaler (0-255).
  strip.show();            // Clear all pixels.

  randomSeed(analogRead(A0));

  phaseStartTime = millis();
  lastFrameTime = phaseStartTime;
  renderSpiral(spiralIndex);
}

void loop() {
  runAnimation();
}
