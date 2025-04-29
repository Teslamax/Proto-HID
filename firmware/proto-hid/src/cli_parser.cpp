// cli_parser.cpp - Handles serial CLI commands (e.g. /i2cscan, /help)
#include <Arduino.h>
#include "cli_parser.h"
#include <Wire.h>
#include "config.h"

static String input_buffer;
static bool at_line_start = true;
static bool echo_enabled = true;

void cli_parser_init() {
  input_buffer.reserve(128);
  Serial.println(F("[cli_parser] Ready. Type /help for commands."));
}

static void handle_command(const String& cmd) {
  String trimmed = cmd;
  trimmed.trim();

  if (trimmed.equalsIgnoreCase("/help")) {
    Serial.println(F("🆘 Available commands:"));
    Serial.println(F("  /help         - Show this help message"));
    Serial.println(F("  /i2cscan      - Scan I2C bus for devices"));
    Serial.println(F("  /version      - Show firmware version"));
    Serial.println(F("  /echo on|off  - Enable or disable input echo"));
  }
  else if (trimmed.equalsIgnoreCase("/version")) {
    Serial.println(F(FIRMWARE_NAME " v" FIRMWARE_VERSION " - " FIRMWARE_DESCRIPTION));
  }
  else if (trimmed.startsWith("/echo ")) {
    if (trimmed.endsWith("on")) {
      echo_enabled = true;
      Serial.println(F("🛠 Echo enabled"));
    } else if (trimmed.endsWith("off")) {
      echo_enabled = false;
      Serial.println(F("🛠 Echo disabled"));
    } else {
      Serial.println(F("⚠️  Usage: /echo on|off"));
    }
  }
  else if (trimmed.equalsIgnoreCase("/i2cscan")) {
    Serial.println(F("🔍 Scanning I2C bus..."));
    for (uint8_t address = 0x08; address <= 0x77; ++address) {
      Wire.beginTransmission(address);
      if (Wire.endTransmission() == 0) {
        Serial.print(F("📟 Found device at 0x"));
        if (address < 0x10) Serial.print('0');
        Serial.println(address, HEX);
      }
    }
    Serial.println(F("✅ I2C scan complete."));
  }
  else {
    Serial.print(F("❓ Unknown command: "));
    Serial.println(trimmed);
  }
}

void cli_parser_update() {
  while (Serial.available()) {
    char c = Serial.read();

    if (at_line_start) {
      input_buffer = "";
      at_line_start = false;
      if (echo_enabled) Serial.print(F("> "));
    }

    if (c == '\r') continue; // ignore carriage return

    if (c == '\n') {
      if (echo_enabled) Serial.println();
      input_buffer.trim();
      handle_command(input_buffer);
      at_line_start = true;
      continue;
    }

    // Backspace or delete
    if (c == 8 || c == 127) {
      if (input_buffer.length() > 0) {
        input_buffer.remove(input_buffer.length() - 1);
        if (echo_enabled) Serial.print(F("\b \b"));
      }
      continue;
    }

    // Printable character
    if (c >= 32 && c <= 126) {
      input_buffer += c;
      if (echo_enabled) Serial.print(c);
    }

    // Limit input length
    if (input_buffer.length() > 127) {
      input_buffer = "";
      at_line_start = true;
      Serial.println(F("\n⚠️  Error: input too long"));
    }
  }
}
