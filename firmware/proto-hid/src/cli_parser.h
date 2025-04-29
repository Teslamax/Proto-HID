#pragma once

// Initialize CLI parser
void cli_parser_init();

// Periodically called in main loop to parse serial input
void cli_parser_update();

// Logging functions (respect CDC log level from config.h)
void logInfo(const char* fmt, ...);
void logWarn(const char* fmt, ...);
void logError(const char* fmt, ...);
