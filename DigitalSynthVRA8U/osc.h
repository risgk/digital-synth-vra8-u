#pragma once

#include "common.h"
#include "osc-table.h"
#include "mul-q.h"
#include <math.h>

static const uint8_t OSC_MIX_TABLE_LENGTH   = 31;

static const uint8_t CHORUS_MODE_OFF        = 0;
static const uint8_t CHORUS_MODE_STEREO     = 1;
static const uint8_t CHORUS_MODE_P_STEREO   = 2;
static const uint8_t CHORUS_MODE_MONO       = 3;
static const uint8_t CHORUS_MODE_STEREO_2   = 4;

static const uint8_t PORTAMENTO_COEF_OFF    = 190;

template <uint8_t T>
class Osc {
  static const uint8_t WAVEFORM_SAW           = 0;
  static const uint8_t WAVEFORM_PUL           = 1;

  static const uint8_t LFO_WAVEFORM_TRI_ASYNC = 0;
  static const uint8_t LFO_WAVEFORM_TRI_SYNC  = 1;
  static const uint8_t LFO_WAVEFORM_SAW_DOWN  = 2;
  static const uint8_t LFO_WAVEFORM_RANDOM    = 3;
  static const uint8_t LFO_WAVEFORM_PULSE     = 4;

  static const uint8_t LFO_FADE_COEF_OFF      = 1;
  static const uint8_t LFO_FADE_COEF_ON_MIN   = 2;

  static const uint8_t LFO_FADE_LEVEL_MAX     = 128;

  static uint8_t        m_portamento_coef[4];
  static int8_t         m_pitch_env_amt;
  static int16_t        m_lfo_mod_level;
  static uint16_t       m_lfo_phase;
  static int8_t         m_lfo_wave_level;
  static int16_t        m_lfo_level;
  static uint16_t       m_lfo_rate;
  static uint8_t        m_lfo_depth[2];
  static int8_t         m_pitch_lfo_amt;
  static uint8_t        m_lfo_waveform;
  static uint8_t        m_lfo_sampled;
  static uint8_t        m_lfo_fade_coef;
  static uint8_t        m_lfo_fade_cnt;
  static uint8_t        m_lfo_fade_level;

  static uint8_t        m_chorus_depth_control;
  static uint8_t        m_chorus_rate_control;
  static uint8_t        m_chorus_delay_time_control;
  static uint8_t        m_chorus_mode;
  static uint8_t        m_chorus_depth_control_actual;
  static uint16_t       m_chorus_lfo_phase;
  static int16_t        m_chorus_lfo_wave_level;
  static int16_t        m_chorus_lfo_level;
  static uint16_t       m_chorus_delay_time[2];

  static uint8_t        m_waveform[2];
  static int16_t        m_pitch_bend;
  static uint8_t        m_pitch_bend_range;
  static int16_t        m_pitch_bend_normalized;
  static uint16_t       m_pitch_target[4];
  static uint16_t       m_pitch_current[4];
  static uint16_t       m_pitch_real[4];
  static const uint8_t* m_wave_table[4];
  static const uint8_t* m_wave_table_temp[4];
  static uint16_t       m_freq[4];
  static uint16_t       m_freq_temp[4];
  static uint16_t       m_phase[4];
  static boolean        m_osc_on[4];
  static boolean        m_osc_on_temp[4];
  static uint8_t        m_osc_gain_effective[4];
  static uint8_t        m_osc_gain[4];
  static uint8_t        m_osc_level;

  static boolean        m_mono_mode;
  static uint8_t        m_mono_osc2_mix;
  static uint8_t        m_mono_osc2_pitch;
  static uint8_t        m_mono_osc2_detune;

  static uint8_t        m_rnd;

public:
  INLINE static void initialize() {
    m_portamento_coef[0] = PORTAMENTO_COEF_OFF;
    m_portamento_coef[1] = PORTAMENTO_COEF_OFF;
    m_portamento_coef[2] = PORTAMENTO_COEF_OFF;
    m_portamento_coef[3] = PORTAMENTO_COEF_OFF;

    m_pitch_env_amt = 0;
    m_lfo_mod_level = 0;
    m_lfo_phase = 0;
    m_lfo_wave_level = 0;
    m_lfo_level = 0;
    m_lfo_rate = 0;
    m_lfo_depth[0] = 0;
    m_lfo_depth[1] = 0;
    m_pitch_lfo_amt = 0;
    m_lfo_waveform = LFO_WAVEFORM_TRI_ASYNC;
    m_lfo_sampled = 64;
    m_lfo_fade_coef = LFO_FADE_COEF_OFF;
    m_lfo_fade_cnt = m_lfo_fade_coef;
    m_lfo_fade_level = LFO_FADE_LEVEL_MAX;

    set_chorus_depth     (32 );
    set_chorus_rate      (32 );
    set_chorus_delay_time(80 );
    set_chorus_mode      (CHORUS_MODE_OFF);
    set_mono_mode        (false);
    set_mono_osc2_mix    (0);
    set_mono_osc2_pitch  (0);
    set_mono_osc2_detune (0);

    m_chorus_depth_control_actual = 64;
    m_chorus_lfo_phase = 0;
    m_chorus_lfo_wave_level = 0;
    m_chorus_lfo_level = 0;
    m_chorus_delay_time[0] = 0;
    m_chorus_delay_time[1] = 0;

    m_waveform[0] = WAVEFORM_SAW;
    m_waveform[1] = WAVEFORM_SAW;
    m_pitch_bend_normalized = 0;
    m_pitch_target[0] = 60 << 8;
    m_pitch_target[1] = 60 << 8;
    m_pitch_target[2] = 60 << 8;
    m_pitch_target[3] = 60 << 8;
    m_pitch_current[0] = m_pitch_target[0];
    m_pitch_current[1] = m_pitch_target[1];
    m_pitch_current[2] = m_pitch_target[2];
    m_pitch_current[3] = m_pitch_target[3];
    m_pitch_real[0] = m_pitch_current[0];
    m_pitch_real[1] = m_pitch_current[1];
    m_pitch_real[2] = m_pitch_current[2];
    m_pitch_real[3] = m_pitch_current[3];
    m_wave_table[0] = g_osc_saw_wave_tables[0];
    m_wave_table[1] = g_osc_saw_wave_tables[0];
    m_wave_table[2] = g_osc_saw_wave_tables[0];
    m_wave_table[3] = g_osc_saw_wave_tables[0];
    m_wave_table_temp[0] = g_osc_saw_wave_tables[0];
    m_wave_table_temp[1] = g_osc_saw_wave_tables[0];
    m_wave_table_temp[2] = g_osc_saw_wave_tables[0];
    m_wave_table_temp[3] = g_osc_saw_wave_tables[0];
    m_freq[0] = g_osc_freq_table[0];
    m_freq[1] = g_osc_freq_table[0];
    m_freq[2] = g_osc_freq_table[0];
    m_freq[3] = g_osc_freq_table[0];
    m_freq_temp[0] = g_osc_freq_table[0];
    m_freq_temp[1] = g_osc_freq_table[0];
    m_freq_temp[2] = g_osc_freq_table[0];
    m_freq_temp[3] = g_osc_freq_table[0];
    m_phase[0] = 0;
    m_phase[1] = 0;
    m_phase[2] = 0;
    m_phase[3] = 0;
    m_osc_on[0] = false;
    m_osc_on[1] = false;
    m_osc_on[2] = false;
    m_osc_on[3] = false;
    m_osc_on_temp[0] = false;
    m_osc_on_temp[1] = false;
    m_osc_on_temp[2] = false;
    m_osc_on_temp[3] = false;
    m_osc_gain_effective[0] = 0;
    m_osc_gain_effective[1] = 0;
    m_osc_gain_effective[2] = 0;
    m_osc_gain_effective[3] = 0;
    m_osc_gain[0] = 0;
    m_osc_gain[1] = 0;
    m_osc_gain[2] = 0;
    m_osc_gain[3] = 0;
    m_osc_level = 48;

    m_rnd = 1;

    set_pitch_bend_range(2);
  }

  template <uint8_t N>
  INLINE static void set_osc_waveform(uint8_t controller_value) {
    if (controller_value < 64) {
      m_waveform[N] = WAVEFORM_SAW;
    } else {
      m_waveform[N] = WAVEFORM_PUL;
    }
  }

  INLINE static void set_osc_level(uint8_t controller_value) {
    if (controller_value < 8) {
      m_osc_level = 4;
    } else {
      m_osc_level = ((controller_value + 1) >> 1);
    }
  }

  INLINE static void set_pitch_env_amt(uint8_t controller_value) {
    if (controller_value < 16) {
      m_pitch_env_amt = -96;
    } else if (controller_value < 112) {
      m_pitch_env_amt = ((controller_value - 64) << 1);
    } else {
      m_pitch_env_amt = 96;
    }
  }

  INLINE static void set_lfo_waveform(uint8_t controller_value) {
    if        (controller_value < 16) {
      m_lfo_waveform = LFO_WAVEFORM_TRI_ASYNC;
    } else if (controller_value < 48) {
      m_lfo_waveform = LFO_WAVEFORM_TRI_SYNC;
    } else if (controller_value < 80) {
      m_lfo_waveform = LFO_WAVEFORM_SAW_DOWN;
    } else if (controller_value < 112) {
      m_lfo_waveform = LFO_WAVEFORM_RANDOM;
    } else {
      m_lfo_waveform = LFO_WAVEFORM_PULSE;
    }
  }

  INLINE static void set_lfo_rate(uint8_t controller_value) {
    m_lfo_rate = g_lfo_rate_table[(controller_value + 1) >> 1];
  }

  template <uint8_t N>
  INLINE static void set_lfo_depth(uint8_t controller_value) {
    m_lfo_depth[N] = (controller_value + 1) >> 1;
  }

  template <uint8_t N>
  INLINE static void set_pitch_lfo_amt(uint8_t controller_value) {
    if (controller_value < 16) {
      m_pitch_lfo_amt = -96;
    } else if (controller_value < 112) {
      m_pitch_lfo_amt = ((controller_value - 64) << 1);
    } else {
      m_pitch_lfo_amt = 96;
    }
  }

  INLINE static void set_lfo_fade_time(uint8_t controller_value) {
    m_lfo_fade_coef = high_byte(controller_value * controller_value) + LFO_FADE_COEF_OFF;
  }

  INLINE static void set_chorus_depth(uint8_t controller_value) {
    if (controller_value < 126) {
      m_chorus_depth_control = controller_value;
    } else {
      m_chorus_depth_control = 126;
    }
  }

  INLINE static void set_chorus_rate(uint8_t controller_value) {
    if (controller_value < 2) {
      m_chorus_rate_control = 1;
    } else {
      m_chorus_rate_control = (controller_value + 2) >> 2;
    }
  }

  INLINE static void set_chorus_delay_time(uint8_t controller_value) {
    m_chorus_delay_time_control = controller_value;
  }

  INLINE static void set_chorus_mode(uint8_t chorus_mode) {
    m_chorus_mode = chorus_mode;
  }

  INLINE static void set_mono_mode(boolean mono_mode) {
    m_mono_mode = mono_mode;
  }

  INLINE static void set_mono_osc2_mix(uint8_t controller_value) {
    m_mono_osc2_mix = controller_value;
  }

  INLINE static void set_mono_osc2_pitch(uint8_t controller_value) {
    if (controller_value > 24) {
      m_mono_osc2_pitch = 24;
    } else {
      m_mono_osc2_pitch = controller_value;
    }
  }

  INLINE static void set_mono_osc2_detune(uint8_t controller_value) {
    m_mono_osc2_detune = ((controller_value + 1) >> 1);
  }

  template <uint8_t N>
  INLINE static void set_portamento(uint8_t controller_value) {
    m_portamento_coef[N] = ((controller_value + 1) >> 1) + PORTAMENTO_COEF_OFF;
  }

  template <uint8_t N>
  INLINE static void note_on(uint8_t note_number) {
    m_pitch_target[N] = note_number << 8;
    m_osc_on[N] = true;
  }

  template <uint8_t N>
  INLINE static void note_off() {
    m_osc_on[N] = false;
  }

  INLINE static void trigger_lfo() {
    if (m_lfo_waveform != LFO_WAVEFORM_TRI_ASYNC) {
      m_lfo_phase = 0xFFFF;
    }

    if (m_lfo_fade_coef >= LFO_FADE_COEF_ON_MIN) {
      m_lfo_fade_level = 0;
    }
  }

  INLINE static void set_pitch_bend_range(uint8_t controller_value) {
    uint8_t range = controller_value;
    if (range > 60) {
      range = 60;
    }
    m_pitch_bend_range = range;
    update_pitch_bend();
  }

  INLINE static void set_pitch_bend(int16_t pitch_bend) {
    m_pitch_bend = pitch_bend;
    update_pitch_bend();
  }

  INLINE static int16_t get_lfo_level() {
    return m_lfo_level;
  }

  template <uint8_t N>
  INLINE static int16_t get_chorus_delay_time() {
    return m_chorus_delay_time[N];
  }

  INLINE static int16_t clock(uint8_t count, uint8_t env_gen_level) {
#if 1
    if ((count & (OSC_CONTROL_INTERVAL - 1)) == 0) {
      //printf("%d Osc\n", count);
      switch (count & (0x1F << OSC_CONTROL_INTERVAL_BITS)) {
      case (0x00 << OSC_CONTROL_INTERVAL_BITS): update_freq_0th<0>();              break;
      case (0x01 << OSC_CONTROL_INTERVAL_BITS): update_freq_1st<0>(env_gen_level); break;
      case (0x02 << OSC_CONTROL_INTERVAL_BITS): update_freq_2nd<0>();              break;
      case (0x03 << OSC_CONTROL_INTERVAL_BITS): update_freq_3rd<0>();              break;
      case (0x04 << OSC_CONTROL_INTERVAL_BITS): update_gate<0>();                  break;
      case (0x05 << OSC_CONTROL_INTERVAL_BITS): update_rnd();                      break;
      case (0x06 << OSC_CONTROL_INTERVAL_BITS): update_lfo_1st();                  break;
      case (0x07 << OSC_CONTROL_INTERVAL_BITS): update_lfo_2nd();                  break;
      case (0x08 << OSC_CONTROL_INTERVAL_BITS): update_freq_0th<1>();              break;
      case (0x09 << OSC_CONTROL_INTERVAL_BITS): update_freq_1st<1>(env_gen_level); break;
      case (0x0A << OSC_CONTROL_INTERVAL_BITS): update_freq_2nd<1>();              break;
      case (0x0B << OSC_CONTROL_INTERVAL_BITS): update_freq_3rd<1>();              break;
      case (0x0C << OSC_CONTROL_INTERVAL_BITS): update_gate<1>();                  break;
      case (0x0D << OSC_CONTROL_INTERVAL_BITS): update_rnd();                      break;
      case (0x0E << OSC_CONTROL_INTERVAL_BITS): update_lfo_3rd();                  break;
      case (0x0F << OSC_CONTROL_INTERVAL_BITS): update_lfo_4th();                  break;
      case (0x10 << OSC_CONTROL_INTERVAL_BITS): update_freq_0th<2>();              break;
      case (0x11 << OSC_CONTROL_INTERVAL_BITS): update_freq_1st<2>(env_gen_level); break;
      case (0x12 << OSC_CONTROL_INTERVAL_BITS): update_freq_2nd<2>();              break;
      case (0x13 << OSC_CONTROL_INTERVAL_BITS): update_freq_3rd<2>();              break;
      case (0x14 << OSC_CONTROL_INTERVAL_BITS): update_gate<2>();                  break;
      case (0x15 << OSC_CONTROL_INTERVAL_BITS): update_rnd();                      break;
      case (0x16 << OSC_CONTROL_INTERVAL_BITS): update_chorus_lfo_0th();           break;
      case (0x17 << OSC_CONTROL_INTERVAL_BITS): update_chorus_lfo_1st();           break;
      case (0x18 << OSC_CONTROL_INTERVAL_BITS): update_freq_0th<3>();              break;
      case (0x19 << OSC_CONTROL_INTERVAL_BITS): update_freq_1st<3>(env_gen_level); break;
      case (0x1A << OSC_CONTROL_INTERVAL_BITS): update_freq_2nd<3>();              break;
      case (0x1B << OSC_CONTROL_INTERVAL_BITS): update_freq_3rd<3>();              break;
      case (0x1C << OSC_CONTROL_INTERVAL_BITS): update_gate<3>();                  break;
      case (0x1D << OSC_CONTROL_INTERVAL_BITS): update_rnd();                      break;
      case (0x1E << OSC_CONTROL_INTERVAL_BITS): update_chorus_lfo_2nd();           break;
      case (0x1F << OSC_CONTROL_INTERVAL_BITS): update_chorus_lfo_3rd();           break;
      }
    }
#endif

#if 1
    m_phase[0] += m_freq[0];
    m_phase[1] += m_freq[1];
    m_phase[2] += m_freq[2];
    m_phase[3] += m_freq[3];

    int8_t wave_0 = get_wave_level(m_wave_table[0], m_phase[0]);
    int8_t wave_1 = get_wave_level(m_wave_table[1], m_phase[1]);
    int8_t wave_2 = get_wave_level(m_wave_table[2], m_phase[2]);
    int8_t wave_3 = get_wave_level(m_wave_table[3], m_phase[3]);

    // amp and mix
    int16_t level_0 = wave_0 * m_osc_gain_effective[0];
    int16_t level_1 = wave_1 * m_osc_gain_effective[1];
    int16_t level_2 = wave_2 * m_osc_gain_effective[2];
    int16_t level_3 = wave_3 * m_osc_gain_effective[3];
    int16_t result  = level_0 + level_1 + level_2 + level_3;
#else
    int16_t result  = 0;
#endif

    return result;
  }

private:
  INLINE static const uint8_t* get_wave_table(uint8_t waveform, uint8_t note_number) {
    const uint8_t* result;
#if defined(MAKE_SAMPLE_WAV_FILE)
    if (waveform == WAVEFORM_SAW) {
      result = g_osc_saw_wave_tables[note_number - NOTE_NUMBER_MIN];
    } else {     // WAVEFORM_PUL
      result = g_osc_pulse_wave_tables[note_number - NOTE_NUMBER_MIN];
    }
#else
    if (waveform == WAVEFORM_SAW) {
      result = pgm_read_word(g_osc_saw_wave_tables + (note_number - NOTE_NUMBER_MIN));
    } else {     // WAVEFORM_PUL
      result = pgm_read_word(g_osc_pulse_wave_tables + (note_number - NOTE_NUMBER_MIN));
    }
#endif
    return result;
  }

  INLINE static int8_t get_wave_level(const uint8_t* wave_table, uint16_t phase) {
    uint8_t curr_index = high_byte(phase);
    uint8_t next_weight = low_byte(phase);
    uint16_t two_data = pgm_read_word(wave_table + curr_index);
    uint8_t curr_data = low_byte(two_data);
    uint8_t next_data = high_byte(two_data);

    // lerp
    int8_t result = curr_data + high_sbyte(static_cast<int8_t>(next_data - curr_data) * next_weight);

    return result;
  }

  INLINE static int8_t get_lfo_wave_level(uint16_t phase) {
    int8_t level = 0;

    switch (m_lfo_waveform) {
    case LFO_WAVEFORM_TRI_ASYNC:
    case LFO_WAVEFORM_TRI_SYNC:
      level = high_sbyte(phase);
      if (level < -64) {
        level = -64 - (level + 64);
      } else if (level < 64) {
        // do nothing
      } else {
        level = 64 - (level - 64);
      }
      level = -level;
      break;
    case LFO_WAVEFORM_SAW_DOWN:
      {
        uint8_t b = high_byte(phase);
        b >>= 1;
        level = b - 64;
      }
      break;
    case LFO_WAVEFORM_RANDOM:
      if (phase < m_lfo_rate) {
        m_lfo_sampled = (m_rnd >> 1);
      }
      level = m_lfo_sampled - 64;
      break;
    case LFO_WAVEFORM_PULSE:
      level = high_sbyte(phase);
      if (level >= 0) {
        level = -128;
      } else {
        level = 0;
      }
      break;
    }

    return level;
  }

  template <uint8_t N>
  INLINE static void update_freq_0th() {
    m_osc_on_temp[N] = m_osc_on[N];

    if (m_osc_on_temp[N]) {
      if ((m_portamento_coef[N] == PORTAMENTO_COEF_OFF) || (m_pitch_current[N] <= m_pitch_target[N])) {
        m_pitch_current[N] = m_pitch_target[N] - mul_sq16_uq8(m_pitch_target[N]  - m_pitch_current[N], m_portamento_coef[N]);
      } else {
        m_pitch_current[N] = m_pitch_current[N] + mul_sq16_uq8(m_pitch_target[N] - m_pitch_current[N], 256 - m_portamento_coef[N]);
      }
    }
  }

  template <uint8_t N>
  INLINE static void update_freq_1st(uint8_t env_gen_level) {
    m_pitch_real[N] =  (64 << 8) + m_pitch_current[N] + m_pitch_bend_normalized + (m_pitch_env_amt * env_gen_level);

    uint8_t coarse = high_byte(m_pitch_real[N]);
    if (coarse < (NOTE_NUMBER_MIN + 64)) {
      m_pitch_real[N] = ((NOTE_NUMBER_MIN + 64) << 8);
    } else if (coarse >= (NOTE_NUMBER_MAX + 64)) {
      m_pitch_real[N] = ((NOTE_NUMBER_MAX + 64) << 8);
    }

    m_pitch_real[N] += m_lfo_mod_level;

    if (N == 2) {
      if (m_mono_mode) {
        m_pitch_real[N] += (m_mono_osc2_pitch << 8);
        m_pitch_real[N] += m_mono_osc2_detune;
      }
    }

    coarse = high_byte(m_pitch_real[N]);
    if (coarse < (NOTE_NUMBER_MIN + 64)) {
      m_pitch_real[N] = NOTE_NUMBER_MIN << 8;
    } else if (coarse >= (NOTE_NUMBER_MAX + 64)) {
      m_pitch_real[N] = NOTE_NUMBER_MAX << 8;
    } else {
      m_pitch_real[N] -= (64 << 8);
    }

    m_pitch_real[N] += 128;  // For g_osc_tune_table[]
  }

  template <uint8_t N>
  INLINE static void update_freq_2nd() {
    uint8_t coarse = high_byte(m_pitch_real[N]);
    m_freq_temp[N] = g_osc_freq_table[coarse - NOTE_NUMBER_MIN];
    m_wave_table_temp[N] = get_wave_table(m_waveform[0], coarse);
  }

  template <uint8_t N>
  INLINE static void update_freq_3rd() {
    uint8_t fine = low_byte(m_pitch_real[N]);
    uint16_t freq_div_2 = (m_freq_temp[N] >> 1);
    uint8_t bit = (m_rnd >= 0xF0);
    uint8_t mono_offset = 0;
    if (N == 2) {
      if (m_mono_mode) {
        if (m_freq_temp[0] == m_freq_temp[2]) {
          mono_offset = 1;
        }
      }
    }
    int8_t freq_offset = high_sbyte(freq_div_2 * g_osc_tune_table[fine >> (8 - OSC_TUNE_TABLE_STEPS_BITS)]) + bit + mono_offset;
    m_freq[N] = m_freq_temp[N] + freq_offset;
    m_wave_table[N] = m_wave_table_temp[N];
  }

  template <uint8_t N>
  INLINE static void update_gate() {
    if (m_osc_on_temp[N] && ((N == 0) || (m_mono_mode == false))) {
      const uint8_t half_level = (m_osc_level >> 1) + 1;

      if (m_osc_gain[N] >= (m_osc_level - half_level)) {
        m_osc_gain[N] = m_osc_level;
      } else {
        m_osc_gain[N] += half_level;
      }
    }
    else {
      const uint8_t one_fourth_level = (m_osc_level >> 2) + 1;

      if (m_osc_gain[N] <= one_fourth_level) {
        m_osc_gain[N] = 0;
      } else {
        m_osc_gain[N] -= one_fourth_level;
      }
    }

    m_osc_gain_effective[0] = m_osc_gain[0];
    m_osc_gain_effective[1] = m_osc_gain[1];
    m_osc_gain_effective[2] = m_osc_gain[2];
    m_osc_gain_effective[3] = m_osc_gain[3];
    if (m_mono_mode) {
      if ((m_osc_gain_effective[1] == 0) && (m_osc_gain_effective[2] == 0) && (m_osc_gain_effective[3] == 0)) {
        uint8_t base_gain = m_osc_gain_effective[0];
        if (m_mono_osc2_mix < 32) {
          m_osc_gain_effective[0] = (base_gain << 1);
        } else if (m_mono_osc2_mix < 96) {
          m_osc_gain_effective[0] = (base_gain << 1) - (base_gain >> 2);
          m_osc_gain_effective[2] = base_gain;
        } else {
          uint8_t base_gain = m_osc_gain_effective[0];
          m_osc_gain_effective[0] = base_gain + (base_gain >> 1);
          m_osc_gain_effective[2] = m_osc_gain_effective[0];
        }
      }
    }
  }

  INLINE static void update_rnd() {
    m_rnd ^= m_rnd << 1;
    m_rnd ^= m_rnd >> 1;
    m_rnd ^= m_rnd << 2;
  }

  INLINE static void update_lfo_1st() {
    ;
  }

  INLINE static void update_lfo_2nd() {
    --m_lfo_fade_cnt;
    if (m_lfo_fade_cnt == 0) {
      m_lfo_fade_cnt = m_lfo_fade_coef;
      if (m_lfo_fade_level < LFO_FADE_LEVEL_MAX) {
        m_lfo_fade_level += 2;
      }
    }

    m_lfo_phase += m_lfo_rate;
    m_lfo_wave_level = get_lfo_wave_level(m_lfo_phase);
  }

  INLINE static void update_lfo_3rd() {
    uint8_t lfo_depth = high_byte((m_lfo_depth[0] << 1) * m_lfo_fade_level) + m_lfo_depth[1];
    if (lfo_depth > 64) {
      lfo_depth = 64;
    }
    lfo_depth <<= 1;

    m_lfo_level = (lfo_depth * m_lfo_wave_level) << 1;
  }

  INLINE static void update_lfo_4th() {
    m_lfo_mod_level = -mul_sq16_sq8(m_lfo_level, m_pitch_lfo_amt);
  }

  INLINE static void update_chorus_lfo_0th() {
    if (m_chorus_delay_time_control < 64) {
      if (m_chorus_depth_control > (m_chorus_delay_time_control << 1)) {
        m_chorus_depth_control_actual = (m_chorus_delay_time_control << 1);
      } else {
        m_chorus_depth_control_actual = m_chorus_depth_control;
      }
    } else {
      if (m_chorus_depth_control > ((127 - m_chorus_delay_time_control) << 1)) {
        m_chorus_depth_control_actual = ((127 - m_chorus_delay_time_control) << 1);
      } else {
        m_chorus_depth_control_actual = m_chorus_depth_control;
      }
    }

    m_chorus_lfo_phase += m_chorus_rate_control;
  }

  INLINE static void update_chorus_lfo_1st() {
    m_chorus_lfo_wave_level = get_chorus_lfo_wave_level(m_chorus_lfo_phase);
  }

  INLINE static void update_chorus_lfo_2nd() {
    m_chorus_lfo_level = mul_sq16_uq8(m_chorus_lfo_wave_level, m_chorus_depth_control_actual);
  }

  INLINE static void update_chorus_lfo_3rd() {
    switch (m_chorus_mode) {
    case CHORUS_MODE_OFF      :
      {
        m_chorus_delay_time[0] = 0;
        m_chorus_delay_time[1] = 0;
      }
      break;
    case CHORUS_MODE_STEREO   :
    case CHORUS_MODE_P_STEREO :
    case CHORUS_MODE_MONO     :
      {
        uint16_t chorus_delay_time_control_mul_4 = m_chorus_delay_time_control * 4;
        m_chorus_delay_time[0] = chorus_delay_time_control_mul_4 + m_chorus_lfo_level;
        m_chorus_delay_time[1] = m_chorus_delay_time[0];
      }
      break;
    case CHORUS_MODE_STEREO_2 :
      {
        uint16_t chorus_delay_time_control_mul_4 = m_chorus_delay_time_control * 4;
        m_chorus_delay_time[0] = chorus_delay_time_control_mul_4 + m_chorus_lfo_level;
        m_chorus_delay_time[1] = chorus_delay_time_control_mul_4 - m_chorus_lfo_level;
      }
      break;
    }
  }

  INLINE static int16_t get_chorus_lfo_wave_level(uint16_t phase) {
    int16_t triangle_wave_level = 0;
    phase &= 0x1FFC;
    phase = (phase >> 2);

    if (phase < 0x0400) {
      triangle_wave_level = phase - 512;
    } else {
      triangle_wave_level = 1535 - phase;
    }

    return triangle_wave_level;
  }


  INLINE static void update_pitch_bend() {
    int16_t b = m_pitch_bend + 1;
    b >>= 3;
    m_pitch_bend_normalized = (b * m_pitch_bend_range) >> 2;
  }
};

template <uint8_t T> uint8_t         Osc<T>::m_portamento_coef[4];
template <uint8_t T> int8_t          Osc<T>::m_pitch_env_amt;
template <uint8_t T> int16_t         Osc<T>::m_lfo_mod_level;
template <uint8_t T> uint16_t        Osc<T>::m_lfo_phase;
template <uint8_t T> int8_t          Osc<T>::m_lfo_wave_level;
template <uint8_t T> int16_t         Osc<T>::m_lfo_level;
template <uint8_t T> uint16_t        Osc<T>::m_lfo_rate;
template <uint8_t T> uint8_t         Osc<T>::m_lfo_depth[2];
template <uint8_t T> int8_t          Osc<T>::m_pitch_lfo_amt;
template <uint8_t T> uint8_t         Osc<T>::m_lfo_waveform;
template <uint8_t T> uint8_t         Osc<T>::m_lfo_sampled;
template <uint8_t T> uint8_t         Osc<T>::m_lfo_fade_coef;
template <uint8_t T> uint8_t         Osc<T>::m_lfo_fade_cnt;
template <uint8_t T> uint8_t         Osc<T>::m_lfo_fade_level;

template <uint8_t T> uint8_t         Osc<T>::m_chorus_depth_control;
template <uint8_t T> uint8_t         Osc<T>::m_chorus_rate_control;
template <uint8_t T> uint8_t         Osc<T>::m_chorus_delay_time_control;
template <uint8_t T> uint8_t         Osc<T>::m_chorus_mode;
template <uint8_t T> uint8_t         Osc<T>::m_chorus_depth_control_actual;
template <uint8_t T> uint16_t        Osc<T>::m_chorus_lfo_phase;
template <uint8_t T> int16_t         Osc<T>::m_chorus_lfo_wave_level;
template <uint8_t T> int16_t         Osc<T>::m_chorus_lfo_level;
template <uint8_t T> uint16_t        Osc<T>::m_chorus_delay_time[2];

template <uint8_t T> uint8_t         Osc<T>::m_waveform[2];
template <uint8_t T> int16_t         Osc<T>::m_pitch_bend;
template <uint8_t T> uint8_t         Osc<T>::m_pitch_bend_range;
template <uint8_t T> int16_t         Osc<T>::m_pitch_bend_normalized;
template <uint8_t T> uint16_t        Osc<T>::m_pitch_target[4];
template <uint8_t T> uint16_t        Osc<T>::m_pitch_current[4];
template <uint8_t T> uint16_t        Osc<T>::m_pitch_real[4];
template <uint8_t T> const uint8_t*  Osc<T>::m_wave_table[4];
template <uint8_t T> const uint8_t*  Osc<T>::m_wave_table_temp[4];
template <uint8_t T> uint16_t        Osc<T>::m_freq[4];
template <uint8_t T> uint16_t        Osc<T>::m_freq_temp[4];
template <uint8_t T> uint16_t        Osc<T>::m_phase[4];
template <uint8_t T> boolean         Osc<T>::m_osc_on[4];
template <uint8_t T> boolean         Osc<T>::m_osc_on_temp[4];
template <uint8_t T> uint8_t         Osc<T>::m_osc_gain_effective[4];
template <uint8_t T> uint8_t         Osc<T>::m_osc_gain[4];
template <uint8_t T> uint8_t         Osc<T>::m_osc_level;

template <uint8_t T> boolean         Osc<T>::m_mono_mode;
template <uint8_t T> uint8_t         Osc<T>::m_mono_osc2_mix;
template <uint8_t T> uint8_t         Osc<T>::m_mono_osc2_pitch;
template <uint8_t T> uint8_t         Osc<T>::m_mono_osc2_detune;

template <uint8_t T> uint8_t         Osc<T>::m_rnd;
