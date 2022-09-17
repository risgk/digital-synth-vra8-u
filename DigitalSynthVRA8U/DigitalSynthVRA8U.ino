////////////////////////////////////////////////////////////////////////////////////////////
// Digital Synth VRA8-U -- We strongly recommend Arduino AVR Boards core 1.8.3 (or 1.8.5) //
////////////////////////////////////////////////////////////////////////////////////////////

//#define DEBUG

#define SERIAL_SPEED (38400)            // For Serial MIDI
//#define SERIAL_SPEED (31250)            // For MIDI Shield (MIDI Breakout)

#define L_MONO_AUDIO_OUT_PIN (5)        // Pin D5 (or D6)
#define R_AUDIO_OUT_PIN      (11)       // Pin D11 (Fixed)
#define CPU_BUSY_LED_OUT_PIN (13)       // Pin D13 (Fixed)

#define ENABLE_SPECIAL_PROGRAM_CHANGE   // Program Change by Control Change (112-119)
                                        // Interpret Program Change 8-15 as 0-7



#include "common.h"
#include "audio-out.h"
#include "synth.h"
#include "serial-in.h"

void setup() {
  noInterrupts();
  Synth<0>::initialize();
  SerialIn<0>::open(SERIAL_SPEED);
  AudioOut<0>::open();
}

void loop() {
  while (true) {
    if (SerialIn<0>::available()) {
      uint8_t b = SerialIn<0>::read();
      Synth<0>::receive_midi_byte(b);
    }
    int8_t right_level;
    int8_t left_level = Synth<0>::clock(right_level);
    AudioOut<0>::write(left_level, right_level);
  }
}
