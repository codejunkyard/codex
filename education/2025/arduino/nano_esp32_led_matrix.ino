#include <Arduino.h>
#include <math.h>

// Update these pin assignments to match how you wired the 8x8 LED matrix.
// The sketch assumes a common-anode row / common-cathode column layout where
// driving a row HIGH and a column LOW lights the selected LED.
const uint8_t rowPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const uint8_t colPins[8] = {10, 11, 12, 13, A0, A1, A2, A3};

static uint8_t displayBuffer[8];

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

const uint16_t ROW_HOLD_MICROS = 1100; // Tune for brightness vs. flicker.

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
  {4, 2}, {3, 2}, {3, 3}, {3, 4}, {4, 4}, {4, 3}
};

void clearBuffer() {
  memset(displayBuffer, 0, sizeof(displayBuffer));
}

void setPixel(uint8_t row, uint8_t col, bool on = true) {
  if (row >= 8 || col >= 8) {
    return;
  }
  if (on) {
    displayBuffer[row] |= (1 << col);
  } else {
    displayBuffer[row] &= ~(1 << col);
  }
}

void renderSpiral(uint8_t headIndex) {
  clearBuffer();
  const uint8_t tailLength = 8;
  for (uint8_t i = 0; i < tailLength; ++i) {
    uint8_t index = (headIndex + SPIRAL_PATH_LENGTH - i) % SPIRAL_PATH_LENGTH;
    setPixel(spiralPath[index][0], spiralPath[index][1], true);
  }
}

void renderWave(uint16_t step) {
  clearBuffer();
  for (uint8_t col = 0; col < 8; ++col) {
    float angle = (step * 0.32f) + (col * 0.55f);
    float normalized = (sinf(angle) + 1.0f) * 3.5f; // Map sine output (-1..1) to (0..7).
    uint8_t primaryRow = static_cast<uint8_t>(normalized + 0.5f);
    if (primaryRow > 7) {
      primaryRow = 7;
    }
    setPixel(primaryRow, col, true);

    int secondaryRow = primaryRow + (sinf(angle + 1.2f) > 0 ? 1 : -1);
    if (secondaryRow >= 0 && secondaryRow < 8) {
      setPixel(static_cast<uint8_t>(secondaryRow), col, true);
    }
  }
}

void renderSparkle(uint8_t frame) {
  (void)frame;
  clearBuffer();
  const uint8_t sparkleCount = 12;
  for (uint8_t i = 0; i < sparkleCount; ++i) {
    setPixel(random(8), random(8), true);
  }
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

void refreshDisplay() {
  static uint8_t currentRow = 0;
  static unsigned long lastSwitch = 0;
  unsigned long now = micros();

  if ((now - lastSwitch) < ROW_HOLD_MICROS) {
    return;
  }

  // Turn off previous row and reset columns.
  digitalWrite(rowPins[currentRow], LOW);
  for (uint8_t col = 0; col < 8; ++col) {
    digitalWrite(colPins[col], HIGH);
  }

  currentRow = (currentRow + 1) % 8;

  // Apply column states for the new row.
  for (uint8_t col = 0; col < 8; ++col) {
    bool ledOn = (displayBuffer[currentRow] & (1 << col)) != 0;
    digitalWrite(colPins[col], ledOn ? LOW : HIGH);
  }

  digitalWrite(rowPins[currentRow], HIGH);
  lastSwitch = now;
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
  for (uint8_t i = 0; i < 8; ++i) {
    pinMode(rowPins[i], OUTPUT);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
    digitalWrite(colPins[i], HIGH);
  }

  randomSeed(analogRead(A0));

  phaseStartTime = millis();
  lastFrameTime = phaseStartTime;
  renderSpiral(spiralIndex);
}

void loop() {
  refreshDisplay();
  runAnimation();
}
