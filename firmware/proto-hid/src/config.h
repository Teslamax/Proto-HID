#pragma once

// Firmware identity
#define FIRMWARE_NAME        "proto-hid"
#define FIRMWARE_VERSION     "0.1.0"
#define FIRMWARE_DESCRIPTION "CLI + MIDI USB controller (rotary, NeoKey)"

// Boot prompt
#define FIRMWARE_BOOT_MSG    "[proto-hid] USB CLI ready — type /help"

// Echo settings
#define ECHO_USER_INITIAL    true
#define ECHO_USER_PREFIX     "> "

// CDC Logging Levels (future use)
#define CDC_INFO_PREFIX      "ℹ️  "
#define CDC_WARN_PREFIX      "⚠️  "
#define CDC_ERROR_PREFIX     "❌ "
#define CDC_VERBOSE_PREFIX   "🔍 "

// Optional Serial settings for future UARTs
#define UART1_BAUDRATE       115200
#define UART1_PARITY         SERIAL_8N1
#define UART1_TIMEOUT_MS     100
