# Digital Synth VRA8-Q v5.1.0

- 2022-04-10 ISGK Instruments
- <https://github.com/risgk/digital-synth-vra8-q>

## Concept

- Quadraphonic (4-voice Paraphonic) Synthesizer (MIDI Sound Module) with Stereo Chorus Effector for Arduino Uno

## Caution about Arduino

- We *strongly recommend* **Arduino AVR Boards core 1.8.3**
    - If you use other than AVR Boards core 1.8.3 (or modified this sketch), the sketch *may not work well*
        - CPU Busy LED (LED L) *may almost always lit*, rather than flashing occasionally

## Change History

- v5.1.0: Fix Portamento in Monophonic Mode; Add MONO OSC2 PITCH Control; Memory last 4 notes in Monophonic and Legato Modes; Improve sound of Monophonic and Legato Modes; Make envelopes smoother (Improve EG); Change the layout of VRA8-Q CTRL; Other changes
- v5.0.1: Fix a bug that OSC LEVEL is not updated in program change
- v5.0.0: Fix wave tables (Reduce noise); Change the range of CUTOFF frequency (min: 452.9 Hz, max: 14.5 kHz); Improve LFO RATE (min: 0.2 Hz, max: 20 Hz); Add EG > PITCH, LFO WAVE, LFO FADE TIME, MONO OSC2 MIX, and MONO OSC2 DETUNE; Add Legato Mode (Monophonic, Single Trigger, Auto Portamento); Change the recommended circuits; Rename PRESET #7 NEUTRAL to INITIAL; Other changes
- v4.0.0: Add PORTAMENTO Time; Remove AC coupling capacitors from the recommended circuit
- v3.2.0: Add Pseudo-Stereo Chorus Mode; Assign free voices in Oscillator index order; Change CPU Busy LED lighting condition; Other changes
- v3.1.0: Fix the problem pitch bend is minimized by Reset All Controllers; Add VOICE Mode (PARA/MONO); Expand the range of CUTOFF frequency (min: 440 Hz, max: 14.08 kHz); Improve VELOCITY > CUTOFF; Fix the instability of the pitch when a note (Gate) is turned on; Change PRESET; Other changes
- v3.0.0: Improve sound quality; Fix Oscillator pitch; Increase the CUTOFF frequency slightly (min: 880 Hz, max: 14.08 kHz); Change the Q range of RESONANCE (min: 0.7, max: 8.0); Increasing RESONANCE decreases the filter gain; Support Velocity > CUTOFF (OFF/ON); Reduce pop noise when turning notes ON and OFF; Enable Short Delay FX; Change PRESET programs; Support All Sound OFF and Reset All Controllers; Other changes
- v2.2.0: Change PRESET; Other changes
- v2.1.0: Improve sound quality; Change PRESET; Other changes
- v2.0.0: Add Mono and Stereo 2-phase Chorus modes; Improve the pitch; Introduce No Decay (DECAY = 127); Improve the recommended circuit; Other changes
- v1.1.2: Change the oscillator drift
- v1.1.1: Modify the PRESET programs
- v1.1.0: Change the behavior of the oscillators
- v1.0.3: Fix the problems with bass or treble note on
- v1.0.2: Fix the oscillator frequency
- v1.0.1: Fix the release date

## Features

- Serial MIDI In (38.4 kbps)
    - We recommend [Hairless MIDI<->Serial Bridge](https://projectgus.github.io/hairless-midiserial/) to connect PC
    - **NOTE**: A combination of a **MIDI Shield** (or MIDI Breakout) and a **power supply adapter** is *better* to avoiding USB noise
        - To use MIDI Shield (or MIDI Breakout), take `#define SERIAL_SPEED (31250)` (31.25 kbps) in `"DigitalSynthVRA8Q.ino"`
        - Even using only the power supply adapter *significantly* reduces USB noise
- PWM Audio Out (Unipolar, Line Level) **L/Mono**: **Pin D5** (or D6), **R**: **Pin D11**
    - Sampling Rate: 31.25 kHz, PWM Rate: 62.5 kHz, Bit Depth: 8 bit
    - We recommend adding a RC filter (post LPF) circuit to reduce PWM ripples
        - A 1st-order LPF with a cutoff frequency 7.2 kHz (R = 220 ohm, C = 100 nF) works well
        - A 2nd-order LPF with a cutoff frequency 33.9 kHz (R1 = R2 = 47 ohm, C1 = C2 = 100 nF) works well, too
- Files
    - `"DigitalSynthVRA8Q.ino"` is a sketch for Arduino Uno Rev3 (ATmega328P)
    - `"make-sample-wav-file.cc"` is for Debugging on PC
        - Requiring GCC (g++) or other
        - `"make-sample-wav-file-cc.bat"` makes a sample WAV file (working on Windows)
    - `"generate-*.rb"` generates source files
        - Requiring a Ruby execution environment

## VRA8-Q CTRL

- MIDI Controller (Editor) Application for VRA8-Q, HTML App (Web App)
- VRA8-Q CTRL converts Program Changes (#0-7 for PRESET) into Control Changes
- VRA8-Q CTRL stores the current control values and the user programs (#8-15) in a Web browser (localStorage)
- We recommend using Google Chrome, which implements Web MIDI API
- We recommend [loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html) (virtual loopback MIDI cable) to connect VRA8-Q

## Details of Control Change

- OSC WAVE (SAW/PLS) = Oscillator Waveform
    - 0 (0-63): Saw Wave
    - 127 (64-127): Pulse Wave (Square Wave)
- CUTOFF = Filter Cutoff Frequency
- RESONANCE = Filter Resonance
- AMP EG (OFF/ON)
    - 0 (0-63): Off (Gate)
    - 127 (64-127): On (EG)
- ATTACK = EG Attack Time
- DECAY = EG Decay Time
    - 127: No Decay
- SUSTAIN: EG Sustain Level
- LFO WAVE (T/T2/S/RND/P) = LFO Waveform
    - 0 (0-15): Triangle Wave
    - 32 (16-47): Triangle Wave 2 (Key Sync)
    - 64 (48-79): Saw Wave (Key Sync)
    - 96 (80-111): Random Wave (Key Sync)
    - 127 (112-127): Pulse Wave (Square Wave, Key Sync)
- CHORUS DEPTH
    - 0: Delay Time +/- 0.0 ms (min)
    - 32: Delay Time +/- 2.0 ms
    - 64: Delay Time +/- 4.1 ms
    - 126: Delay Time +/- 8.1 ms (max)
- CHORUS RATE
    - 4: LFO Frequency 0.06 Hz (min)
    - 32: LFO Frequency 0.48 Hz
    - 64: LFO Frequency 0.95 Hz
    - 127: LFO Frequency 1.9 Hz (max)
- CHORUS DELAY TIME
    - 0: 0.03 ms (min)
    - 64: 8.2 ms
    - 80: 10.3 ms
    - 127: 16.3 ms (max)
- CHORUS (-/M/PS/S/S2) = Chorus Mode
    - 0 (0-15): Chorus Off
    - 32 (16-47): Mono Chorus
    - 64 (48-79): Pseudo-Stereo Chorus
    - 96 (80-111): Stereo Chorus
    - 127 (112-127): Stereo 2-phase Chorus
- VOICE (PARA/MONO/LGT) = Voice Mode
    - 0 (0-31): Paraphonic
    - 64 (32-95): Monophonic (Multi Trigger)
    - 127 (96-127): Legato (Monophonic, Single Trigger, Auto Portamento)
- PORTAMENTO = Portament Time
- MONO OSC2 MIX (-/HF/FL) = Oscillator 2 Mixing Level in Monophonic and Legato Modes
    - 0 (0-31): Off, 0% (Oscillator 1: 200%)
    - 64 (32-95): Half, 100% (Oscillator 1: 175%)
    - 127 (96-127): Full, 150% (Oscillator 1: 150%)
- MONO OSC2 PITCH = Oscillator 2 Pitch in Monophonic and Legato Modes
- MONO OSC2 DETUNE = Oscillator 2 Detune amount in Monophonic and Legato Modes

## Sample Chorus Settings

- Setting Q1 -- CHORUS DEPTH: 32, CHORUS RATE: 32, CHORUS DELAY TIME: 80, CHORUS: 127
- Setting D1 -- CHORUS DEPTH: 32, CHORUS RATE: 16, CHORUS DELAY TIME: 80, CHORUS: 127
- Setting D2 -- CHORUS DEPTH: 40, CHORUS RATE: 16, CHORUS DELAY TIME: 60, CHORUS: 127
- Setting D3 -- CHORUS DEPTH: 24, CHORUS RATE: 32, CHORUS DELAY TIME: 60, CHORUS: 127
- Setting U1 -- CHORUS DEPTH: 32, CHORUS RATE: 32, CHORUS DELAY TIME: 20, CHORUS: 127
- Setting U2 -- CHORUS DEPTH: 32, CHORUS RATE: 48, CHORUS DELAY TIME: 20, CHORUS: 127

## MIDI Implementation Chart

      [Quadraphonic Synthesizer]                                      Date: 2022-04-10       
      Model: Digital Synth VRA8-Q     MIDI Implementation Chart       Version: 5.1.0         
    +-------------------------------+---------------+---------------+-------------------------+
    | Function...                   | Transmitted   | Recognized    | Remarks                 |
    +-------------------------------+---------------+---------------+-------------------------+
    | Basic        Default          | x             | 1             |                         |
    | Channel      Changed          | x             | x             |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | Mode         Default          | x             | Mode 3        |                         |
    |              Messages         | x             | x             |                         |
    |              Altered          | ************* |               |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | Note                          | x             | 0-127         |                         |
    | Number       : True Voice     | ************* | 24-96         |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | Velocity     Note ON          | x             | o (V=1-127)   | For VELOCITY > CUTOFF   |
    |              Note OFF         | x             | x             |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | After        Key's            | x             | x             |                         |
    | Touch        Ch's             | x             | x             |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | Pitch Bend                    | x             | o             |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | Control                     1 | x             | o             | MODULATION              |
    | Change                     11 | x             | o             | EXPRESSION              |
    |                            64 | x             | o             | SUSTAIN PEDAL (OFF/ON)  |
    |                               |               |               |                         |
    |                            24 | x             | o             | OSC WAVE (SAW/PLS)      |
    |                           108 | x             | o             | OSC LEVEL               |
    |                           104 | x             | o             | EG > PITCH (-/+)        |
    |                               |               |               |                         |
    |                            16 | x             | o             | CUTOFF                  |
    |                            17 | x             | o             | RESONANCE               |
    |                            18 | x             | o             | EG > CUTOFF (-/+)       |
    |                            31 | x             | o             | AMP EG (OFF/ON)         |
    |                               |               |               |                         |
    |                            23 | x             | o             | ATTACK                  |
    |                            19 | x             | o             | DECAY                   |
    |                            27 | x             | o             | SUSTAIN                 |
    |                               |               |               |                         |
    |                            81 | x             | o             | LFO DEPTH               |
    |                            80 | x             | o             | LFO RATE                |
    |                            82 | x             | o             | LFO > PITCH (-/+)       |
    |                            83 | x             | o             | LFO > CUTOFF (-/+)      |
    |                               |               |               |                         |
    |                            14 | x             | o             | LFO WAVE (T/T2/S/RND/P) |
    |                            15 | x             | o             | LFO FADE TIME           |
    |                               |               |               |                         |
    |                            60 | x             | o             | CHORUS DEPTH            |
    |                            61 | x             | o             | CHORUS RATE             |
    |                            62 | x             | o             | CHORUS DELAY TIME       |
    |                            63 | x             | o             | CHORUS (-/M/PS/S/S2)    |
    |                               |               |               |                         |
    |                            85 | x             | o             | PITCH BEND RANGE        |
    |                            89 | x             | o             | VELOCITY > CUTOFF       |
    |                            87 | x             | o             | VOICE (PARA/MONO/LGT)   |
    |                            22 | x             | o             | PORTAMENTO              |
    |                               |               |               |                         |
    |                            25 | x             | o             | MONO OSC2 MIX (-/HF/FL) |
    |                            20 | x             | o             | MONO OSC2 PITCH         |
    |                            21 | x             | o             | MONO OSC2 DETUNE        |
    |                               |               |               |                         |
    |                   90, 112-119 | x             | x             | (RESERVED)              |
    +-------------------------------+---------------+---------------+-------------------------+
    | Program                       | x             | o             |                         |
    | Change       : True #         | ************* | 0-7           |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | System Exclusive              | x             | x             |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | System       : Song Pos       | x             | x             |                         |
    | Common       : Song Sel       | x             | x             |                         |
    |              : Tune           | x             | x             |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | System       : Clock          | x             | x             |                         |
    | Real Time    : Commands       | x             | x             |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | Aux          : All Sound OFF  | x             | o 120         |                         |
    | Messages     : Reset All      | x             | o 121         |                         |
    |                Controllers    |               |               |                         |
    |              : Local ON/OFF   | x             | x             |                         |
    |              : All Notes OFF  | x             | o 123-127     |                         |
    |              : Active Sense   | x             | x             |                         |
    |              : Reset          | x             | x             |                         |
    +-------------------------------+---------------+---------------+-------------------------+
    | Notes                         |                                                         |
    |                               |                                                         |
    +-------------------------------+---------------------------------------------------------+
      Mode 1: Omni On,  Poly          Mode 2: Omni On,  Mono          o: Yes                 
      Mode 3: Omni Off, Poly          Mode 4: Omni Off, Mono          x: No                  
