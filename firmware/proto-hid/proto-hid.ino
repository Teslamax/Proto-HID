// proto-hid.ino - Main sketch for Proto-HID controller
// Hardware: SparkFun Qwiic Pro Micro (ATmega32U4, USB-C)
// Function: USB MIDI + CLI control using rotary encoders + NeoKey 1x4 keypad

#include "src/input_manager.h"
#include "src/midi_manager.h"
#include "src/cli_parser.h"
#include "src/config.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); } // Wait for USB Serial

  cli_parser_init();
  init_inputs();
}

void loop() {
  update_inputs();
  cli_parser_update();
}
