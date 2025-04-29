// input_manager.cpp - Handles I2C rotary encoders and keypad input for Proto-HID
#include <Arduino.h>
#include <Wire.h>
#include "input_manager.h"
#include "config.h"
#include "midi_manager.h"
#include "cli_parser.h"

// Placeholder for I2C device addresses
#define ENCODER1_ADDR  0x36
#define ENCODER2_ADDR  0x37
#define NEOKEY_ADDR    0x30

void init_inputs() {
  Wire.begin();
  logInfo("I2C initialized.");

  // Future: Initialize Seesaw devices (encoders, keypad)
}

void update_inputs() {
  // Future: Poll I2C devices
  // - Read encoder rotation and button states
  // - Send MIDI CC for rotation
  // - Send MIDI Note for button presses
}
