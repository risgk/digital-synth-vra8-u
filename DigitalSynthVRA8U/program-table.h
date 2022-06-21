#pragma once

const uint8_t PROGRAM_NUMBER_DEFAULT = 0;

// PRESET                                         #0   #1   #2   #3   #4   #5   #6   #7   
const uint8_t g_preset_table_OSC_1_WAVE     [] = {0  , 0  , 0  , 127, 0  , 0  , 0  , 0  };
const uint8_t g_preset_table_OSC_LEVEL      [] = {96 , 96 , 96 , 96 , 96 , 96 , 96 , 96 };
const uint8_t g_preset_table_OSC_EG_AMT     [] = {64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 };

const uint8_t g_preset_table_FIL_CUTOFF     [] = {112, 4  , 124, 76 , 112, 112, 127, 127};
const uint8_t g_preset_table_FIL_RESONANCE  [] = {64 , 64 , 32 , 64 , 64 , 64 , 0  , 0  };
const uint8_t g_preset_table_FIL_EG_AMT     [] = {64 , 124, 4 ,  88 , 64 , 64 , 64 , 64 };
const uint8_t g_preset_table_AMP_EG         [] = {127, 0  , 0  , 127, 127, 127, 127, 127};

const uint8_t g_preset_table_EG_ATTACK      [] = {0  , 64 , 96 , 0  , 0  , 0  , 0  , 0  };
const uint8_t g_preset_table_EG_DECAY       [] = {127, 96 , 96 , 96 , 127, 127, 127, 127};
const uint8_t g_preset_table_EG_SUSTAIN     [] = {0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  };

const uint8_t g_preset_table_LFO_DEPTH      [] = {8  , 8  , 8  , 8  , 8  , 8  , 8  , 0  };
const uint8_t g_preset_table_LFO_RATE       [] = {96 , 96 , 96 , 96 , 96 , 96 , 96 , 96 };
const uint8_t g_preset_table_LFO_OSC_AMT    [] = {65 , 65 , 65 , 65 , 65 , 65 , 65 , 64 };
const uint8_t g_preset_table_LFO_FIL_AMT    [] = {64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 };

const uint8_t g_preset_table_LFO_WAVE       [] = {0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  };
const uint8_t g_preset_table_LFO_FADE_TIME  [] = {0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  };

const uint8_t g_preset_table_CHORUS_DEPTH   [] = {32 , 32 , 32 , 32 , 32 , 32 , 32 , 32 };
const uint8_t g_preset_table_CHORUS_RATE    [] = {32 , 32 , 32 , 32 , 16 , 48 , 32 , 32 };
const uint8_t g_preset_table_CHORUS_DELAY_T [] = {64 , 64 , 64 , 64 , 80 , 20 , 64 , 64 };
const uint8_t g_preset_table_CHORUS_MODE    [] = {127, 127, 127, 127, 127, 127, 127, 0  };

const uint8_t g_preset_table_P_BEND_RANGE   [] = {2  , 2  , 2  , 2  , 2  , 2  , 2  , 2  };
const uint8_t g_preset_table_V_TO_CUTOFF    [] = {0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  };
const uint8_t g_preset_table_VOICE_MODE     [] = {0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  };
const uint8_t g_preset_table_PORTAMENTO     [] = {0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  };

const uint8_t g_preset_table_MIXER_OSC_MIX  [] = {64 , 64 , 64 , 64 , 64 , 64 , 64 , 0  };
const uint8_t g_preset_table_OSC_2_COARSE   [] = {0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  };
const uint8_t g_preset_table_OSC_2_FINE     [] = {64 , 64 , 64 , 64 , 64 , 64 , 64 , 64 };
