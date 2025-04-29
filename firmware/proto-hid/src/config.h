#pragma once

// ───────────── Firmware Info ─────────────
#define FIRMWARE_NAME        "proto-hid"
#define FIRMWARE_VERSION     "0.1.0"
#define FIRMWARE_DESCRIPTION "CLI + MIDI USB controller (rotary, NeoKey)"
#define FIRMWARE_BOOT_MSG    "[proto-hid] USB CLI ready — type /help"

// ───────────── CLI Behavior ─────────────
#define ECHO_USER_INITIAL    true
#define ECHO_USER_PREFIX     "> "

// ───────────── LED Control ─────────────
#define LED_PIN              17  // or 13 depending on board, confirm!
#define LED_BLINK_ENABLED    true

// ───────────── CDC Log Levels ─────────────
#define CDC_INFO_PREFIX      "ℹ️  "
#define CDC_WARN_PREFIX      "⚠️  "
#define CDC_ERROR_PREFIX     "❌ "
#define CDC_VERBOSE_PREFIX   "🔍 "

// Optional Serial settings for future UARTs
#define UART1_BAUDRATE       115200
#define UART1_PARITY         SERIAL_8N1
#define UART1_TIMEOUT_MS     100

static uint8_t cdcLogLevel = 2;  // 0=errors, 1=warn+error, 2=info+warn+error, 3=all
