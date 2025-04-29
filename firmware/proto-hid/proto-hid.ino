// proto-hid.ino - Main sketch for Proto-HID controller
// Hardware: SparkFun Pro Micro (ATmega32U4), Adafruit Seesaw I2C devices
// Function: USB MIDI + CLI control using rotary encoders + NeoKey 1x4

#include "src/input_manager.h"
#include "src/midi_manager.h"
#include "src/cli_parser.h"

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for USB Serial

  cli_parser_init();
  init_inputs();
}

void loop() {
  update_inputs();
  cli_parser_update();
}
