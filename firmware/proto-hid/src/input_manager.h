#pragma once

// Initialize I2C devices (encoders, keypad)
void init_inputs();

// Poll I2C devices and process inputs (rotation, button presses)
void update_inputs();
