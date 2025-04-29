// cli_parser.cpp - Handles serial CLI commands (e.g. /i2cscan, /help)
#include <Arduino.h>
#include "cli_parser.h"
#include <Wire.h>

static String input_buffer = "";

void cli_parser_init() {
  Serial.println(F("[cli_parser] Ready. Type /help for commands."));
}

void handle_command(const String& cmd) {
  if (cmd == "/help") {
    Serial.println(F("Available commands:"));
    Serial.println(F("  /help      - Show this help message"));
    Serial.println(F("  /i2cscan   - Scan I2C bus for devices"));
    Serial.println(F("  /version   - Show firmware version"));
  }
  else if (cmd == "/i2cscan") {
    Serial.println(F("Scanning I2C bus..."));
    for (uint8_t address = 0x08; address <= 0x77; ++address) {
      Wire.beginTransmission(address);
      if (Wire.endTransmission() == 0) {
        Serial.print(F("Found device at 0x"));
        if (address < 0x10) Serial.print('0');
        Serial.println(address, HEX);
      }
    }
  }
  else if (cmd == "/version") {
    Serial.println(F("proto-hid 0.1.0 - CLI/MIDI rotary controller"));
  }
  else {
    Serial.print(F("Unknown command: "));
    Serial.println(cmd);
  }
}

void cli_parser_update() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\r') continue; // ignore carriage return
    if (c == '\n') {
      if (input_buffer.length() > 0) {
        handle_command(input_buffer);
        input_buffer = "";
      }
    } else {
      input_buffer += c;
      if (input_buffer.length() > 63) {
        input_buffer = "";
        Serial.println(F("Error: input too long"));
      }
    }
  }
}
// cli_parser.cpp - Handles serial CLI commands (e.g. /i2cscan, /help)
#include <Arduino.h>
#include "cli_parser.h"
#include <Wire.h>

static String input_buffer = "";

void cli_parser_init() {
  Serial.println(F("[cli_parser] Ready. Type /help for commands."));
}

void handle_command(const String& cmd) {
  if (cmd == "/help") {
    Serial.println(F("Available commands:"));
    Serial.println(F("  /help      - Show this help message"));
    Serial.println(F("  /i2cscan   - Scan I2C bus for devices"));
    Serial.println(F("  /version   - Show firmware version"));
  }
  else if (cmd == "/i2cscan") {
    Serial.println(F("Scanning I2C bus..."));
    for (uint8_t address = 0x08; address <= 0x77; ++address) {
      Wire.beginTransmission(address);
      if (Wire.endTransmission() == 0) {
        Serial.print(F("Found device at 0x"));
        if (address < 0x10) Serial.print('0');
        Serial.println(address, HEX);
      }
    }
  }
  else if (cmd == "/version") {
    Serial.println(F("proto-hid 0.1.0 - CLI/MIDI rotary controller"));
  }
  else {
    Serial.print(F("Unknown command: "));
    Serial.println(cmd);
  }
}

void cli_parser_update() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\r') continue; // ignore carriage return
    if (c == '\n') {
      if (input_buffer.length() > 0) {
        handle_command(input_buffer);
        input_buffer = "";
      }
    } else {
      input_buffer += c;
      if (input_buffer.length() > 63) {
        input_buffer = "";
        Serial.println(F("Error: input too long"));
      }
    }
  }
}
