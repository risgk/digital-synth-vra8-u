///////////////////////////////////////////////////////////////////////////////////////////////
// Digital Synth VRA8-U -- We strongly recommend Arduino AVR Boards version 1.8.5 (or 1.8.3) //
///////////////////////////////////////////////////////////////////////////////////////////////

//#define DEBUG

#define SERIAL_SPEED (38400)            // For Serial MIDI
//#define SERIAL_SPEED (31250)            // For MIDI Shield (MIDI Breakout)

#define L_MONO_AUDIO_OUT_PIN (5)        // Pin D5 (or D6)
#define R_AUDIO_OUT_PIN      (11)       // Pin D11 (Fixed)
#define CPU_BUSY_LED_OUT_PIN (13)       // Pin D13 (Fixed)

//#define ENABLE_16_BIT_OUTPUT            // Operate VRA8-U type-16 (Special Edition with 16-bit Audio Output)
#define L_MONO_LOW_AUDIO_OUT_PIN (6)    // Pin D6 (or D5): L/Mono channel, low 8-bit audio output
#define R_LOW_AUDIO_OUT_PIN      (3)    // Pin D3 (Fixed): R      channel, low 8-bit audio output

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
#if defined(ENABLE_16_BIT_OUTPUT)
    int16_t right_level;
    int16_t left_level = Synth<0>::clock(right_level);
#else
    int8_t right_level;
    int8_t left_level = Synth<0>::clock(right_level);
#endif
    AudioOut<0>::write(left_level, right_level);
  }
}
