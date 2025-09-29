#include <Arduino.h>

// Switches → input
const int switchPins[3] = {10, 11, 12}; // adjust these to your 3 buttons
// LEDs → output (bar graph style)
const int ledPins[7] = {2, 3, 4, 5, 6, 7, 8}; // adjust to your wiring

void setup()
{
    // Setup switches
    for (int i = 0; i < 3; i++)
    {
        pinMode(switchPins[i], INPUT); // assuming pulldown resistors
    }

    // Setup LEDs
    for (int i = 0; i < 7; i++)
    {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }

    Serial.begin(115200);
    Serial.println("Hello, connected!");
}

void loop()
{
    // Read the 3 switches as a number 0–7
    int value = 0;
    for (int i = 0; i < 3; i++)
    {
        if (digitalRead(switchPins[i]) == HIGH)
        {
            value |= (1 << i);
        }
    }

    // Print once for switches
    Serial.print("Switches value: ");
    Serial.println(value);

    // Light up LEDs bar-style: first `value` LEDs ON
    for (int i = 0; i < 7; i++)
    {
        if (i < value)
        {
            digitalWrite(ledPins[i], HIGH);
        }
        else
        {
            digitalWrite(ledPins[i], LOW);
        }
    }

    // Print once for LEDs
    Serial.print("LED bar showing: ");
    Serial.println(value);

    delay(200); // small debounce / reduce spam
}
