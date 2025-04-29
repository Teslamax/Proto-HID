// input_manager.cpp - Handles I2C rotary encoders and keypad input for Proto-HID
#include <Arduino.h>
#include <Wire.h>
#include "input_manager.h"
#include "config.h"
#include "cli_parser.h"
#include "midi_manager.h"
#include <Adafruit_seesaw.h>

// I2C device addresses
#define ENCODER1_ADDR  0x36
#define ENCODER2_ADDR  0x37
#define NEOKEY_ADDR    0x30

// Seesaw objects
Adafruit_seesaw encoder1;
Adafruit_seesaw encoder2;
Adafruit_seesaw neokey;

// Input states
static int32_t encoder1_position = 0;
static int32_t encoder2_position = 0;
static bool encoder1_button_pressed = false;
static bool encoder2_button_pressed = false;
static uint8_t neokey_pressed = 0; // bitmap for 4 keys

// Last states for change detection
static int32_t last_encoder1_position = 0;
static int32_t last_encoder2_position = 0;
static bool last_encoder1_button = false;
static bool last_encoder2_button = false;
static uint8_t last_neokey_pressed = 0;

void init_inputs() {
  Wire.begin();
  logInfo("I2C initialized for input devices.");

  if (!encoder1.begin(ENCODER1_ADDR)) {
    logError("Failed to find Encoder 1 at 0x%02X", ENCODER1_ADDR);
  } else {
    logInfo("Encoder 1 initialized.");
  }

  if (!encoder2.begin(ENCODER2_ADDR)) {
    logError("Failed to find Encoder 2 at 0x%02X", ENCODER2_ADDR);
  } else {
    logInfo("Encoder 2 initialized.");
  }

  if (!neokey.begin(NEOKEY_ADDR)) {
    logError("Failed to find NeoKey 1x4 at 0x%02X", NEOKEY_ADDR);
  } else {
    logInfo("NeoKey 1x4 initialized.");
  }

  encoder1_position = encoder1.getEncoderPosition();
  encoder2_position = encoder2.getEncoderPosition();
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
  // Read encoders
  int32_t current_encoder1 = encoder1.getEncoderPosition();
  int32_t current_encoder2 = encoder2.getEncoderPosition();
  bool current_encoder1_button = !encoder1.digitalRead(24); // Active LOW
  bool current_encoder2_button = !encoder2.digitalRead(24); // Active LOW

  // Read NeoKey buttons manually
  uint8_t current_neokey = 0;
  for (uint8_t i = 0; i < 4; i++) {
    if (!neokey.digitalRead(i)) { // Active LOW
      current_neokey |= (1 << i);
    }
  }

  encoder1_position = current_encoder1;
  encoder2_position = current_encoder2;
  encoder1_button_pressed = current_encoder1_button;
  encoder2_button_pressed = current_encoder2_button;
  neokey_pressed = current_neokey;

  if (cli_input_monitor_enabled()) {
    bool changed = false;

    if (encoder1_position != last_encoder1_position) {
      logInfo("Encoder 1 position: %d", encoder1_position);
      changed = true;
    }
    if (encoder2_position != last_encoder2_position) {
      logInfo("Encoder 2 position: %d", encoder2_position);
      changed = true;
    }
    if (encoder1_button_pressed != last_encoder1_button) {
      logInfo("Encoder 1 button: %s", encoder1_button_pressed ? "Pressed" : "Released");
      changed = true;
    }
    if (encoder2_button_pressed != last_encoder2_button) {
      logInfo("Encoder 2 button: %s", encoder2_button_pressed ? "Pressed" : "Released");
      changed = true;
    }
    if (neokey_pressed != last_neokey_pressed) {
      logInfo("NeoKey bitmap: 0x%02X", neokey_pressed);
      changed = true;
    }

    if (changed) {
      // Optional: pulse LED on input change
    }
  }

  last_encoder1_position = encoder1_position;
  last_encoder2_position = encoder2_position;
  last_encoder1_button = encoder1_button_pressed;
  last_encoder2_button = encoder2_button_pressed;
  last_neokey_pressed = neokey_pressed;
}
