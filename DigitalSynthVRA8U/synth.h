#pragma once

// #define private public  // for tests

#include "common.h"

// associations of units
#define IOsc        Osc
#define IFilter     Filter
#define IAmp        Amp
#define IEG         EG
#define IDelayFx    DelayFx
#define IVoice      Voice
#define ISynthCore  SynthCore

#include "osc.h"
#include "filter.h"
#include "amp.h"
#include "eg.h"
#include "delay-fx.h"
#include "voice.h"
#include "synth-core.h"

template <uint8_t T>
class Synth {
public:
  INLINE static void initialize() {
    ISynthCore<0>::initialize();
    ISynthCore<0>::program_change(PROGRAM_NUMBER_DEFAULT);
  }

  INLINE static void receive_midi_byte(uint8_t b) {
    ISynthCore<0>::receive_midi_byte(b);
  }

#if defined(ENABLE_16_BIT_OUTPUT)
  INLINE static int16_t clock(int16_t& right_level) {
#else
  INLINE static int8_t clock(int8_t& right_level) {
#endif
    return ISynthCore<0>::clock(right_level);
  }
};
