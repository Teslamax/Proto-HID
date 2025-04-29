// cli_parser.h - Command line parser for serial input
#pragma once

// Initialize CLI parser
void cli_parser_init();

// Poll and process CLI input
void cli_parser_update();

// Logging functions
void logInfo(const char* fmt, ...);
void logWarn(const char* fmt, ...);
void logError(const char* fmt, ...);
