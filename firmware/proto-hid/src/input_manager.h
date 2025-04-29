// input_manager.h - Handles I2C rotary encoders and keypad input for Proto-HID
#pragma once

// Initialize I2C devices (encoders, keypad)
void init_inputs();

// Poll I2C devices and process inputs (rotation, button presses)
void update_inputs();

// Print current input states (for /input CLI command)
void print_inputs();
