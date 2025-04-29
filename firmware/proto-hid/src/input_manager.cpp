// input_manager.cpp - Handles I2C rotary encoders and keypad input for Proto-HID
#include <Arduino.h>
#include <Wire.h>
#include "input_manager.h"
#include "config.h"
#include "cli_parser.h"
#include "midi_manager.h"

// Placeholder addresses for devices
#define ENCODER1_ADDR  0x36
#define ENCODER2_ADDR  0x37
#define NEOKEY_ADDR    0x30

// Placeholder states
static int encoder1_position = 0;
static int encoder2_position = 0;
static bool encoder1_button_pressed = false;
static bool encoder2_button_pressed = false;
static uint8_t neokey_pressed = 0; // Bitmap: bit0..bit3 for 4 keys

// Previous states for monitoring changes
static int last_encoder1_position = 0;
static int last_encoder2_position = 0;
static bool last_encoder1_button = false;
static bool last_encoder2_button = false;
static uint8_t last_neokey_pressed = 0;

void init_inputs() {
  Wire.begin();
  logInfo("I2C initialized for input devices.");

  // Future: Initialize Seesaw devices properly
}

void print_inputs() {
  Serial.println(F("🔎 Current Inputs:"));
  Serial.print(F("  Encoder 1: Position "));
  Serial.print(encoder1_position);
  Serial.print(F(", Button "));
  Serial.println(encoder1_button_pressed ? F("Pressed") : F("Released"));

  Serial.print(F("  Encoder 2: Position "));
  Serial.print(encoder2_position);
  Serial.print(F(", Button "));
  Serial.println(encoder2_button_pressed ? F("Pressed") : F("Released"));

  Serial.print(F("  NeoKey: Keys pressed bitmap 0x"));
  Serial.println(neokey_pressed, HEX);
}

void update_inputs() {
  // TODO: Poll Seesaw encoder and keypad states here.

  // Dummy simulation for now:
  encoder1_position++;
  encoder2_position--;
  encoder1_button_pressed = (millis() / 1000) % 2;
  encoder2_button_pressed = (millis() / 1500) % 2;
  neokey_pressed = (millis() / 2000) % 0x10;

  // Monitor if inputMonitorEnabled is true
  if (cli_input_monitor_enabled()) {
    bool changed = false;
    if (encoder1_position != last_encoder1_position) {
      logInfo("Encoder 1 position changed: %d", encoder1_position);
      changed = true;
    }
    if (encoder2_position != last_encoder2_position) {
      logInfo("Encoder 2 position changed: %d", encoder2_position);
      changed = true;
    }
    if (encoder1_button_pressed != last_encoder1_button) {
      logInfo("Encoder 1 button %s", encoder1_button_pressed ? "Pressed" : "Released");
      changed = true;
    }
    if (encoder2_button_pressed != last_encoder2_button) {
      logInfo("Encoder 2 button %s", encoder2_button_pressed ? "Pressed" : "Released");
      changed = true;
    }
    if (neokey_pressed != last_neokey_pressed) {
      logInfo("NeoKey bitmap changed: 0x%02X", neokey_pressed);
      changed = true;
    }
    if (changed) {
      pulseLed();  // optional, re-blink on input event
    }
  }

  // Update last states
  last_encoder1_position = encoder1_position;
  last_encoder2_position = encoder2_position;
  last_encoder1_button = encoder1_button_pressed;
  last_encoder2_button = encoder2_button_pressed;
  last_neokey_pressed = neokey_pressed;
}
