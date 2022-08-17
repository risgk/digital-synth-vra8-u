# Digital Synth VRA8-U v0.0.0

- 2022-08-17 ISGK Instruments
- <https://github.com/risgk/digital-synth-vra8-u>

## Concept

- Monophonic/Paraphonic United Synthesizer for Arduino Uno
    - 4-Voice Paraphonic
    - With built-in Chorus FX
    - Controlled by MIDI (MIDI Sound Module)
- The 8th in the Digital Synth VRA8 series that pushes the limits of the Arduino Uno

## Caution about Arduino

- We *strongly recommend* **Arduino AVR Boards core 1.8.5**
    - If you use other than 1.8.5, the sketch *may not work well*: CPU Busy LED (LED L) *may almost always lit*

## Features

- Serial MIDI In (38.4 kbps)
    - We recommend [Hairless MIDI<->Serial Bridge](https://projectgus.github.io/hairless-midiserial/) to connect PC
    - **NOTE**: A combination of a **MIDI Shield** (or MIDI Breakout) and a **power supply adapter** is *better* to avoiding USB noise
        - To use MIDI Shield (or MIDI Breakout), take `#define SERIAL_SPEED (31250)` (31.25 kbps) in `"DigitalSynthVRA8U.ino"`
        - Even using only the power supply adapter *significantly* reduces USB noise
- PWM Audio Out (Unipolar, Line Level) **L/Mono**: **Pin D5** (or D6), **R**: **Pin D11**
    - Sampling Rate: 31.25 kHz, PWM Rate: 62.5 kHz, Bit Depth: 8 bit
    - We recommend adding RC filter (post LPF) circuits to reduce PWM ripples
        - A 1st-order LPF with a cutoff frequency 7.2 kHz (R = 220 ohm, C = 100 nF) works well
    - We recommend adding AC coupling capacitors to reduce DC components
        - A 10 uF electrolytic capacitor works well
- Files
    - `"DigitalSynthVRA8U.ino"` is a sketch for Arduino Uno Rev3 (ATmega328P)
    - `"make-sample-wav-file.cc"` is for Debugging on PC
        - Requiring GCC (g++) or other
        - `"make-sample-wav-file-cc.bat"` makes a sample WAV file (working on Windows)
    - `"generate-*.rb"` generates source files
        - Requiring a Ruby execution environment

## VRA8-U CTRL

- MIDI Controller (Editor) Application for VRA8-U, HTML App (Web App)
- VRA8-U CTRL converts Program Changes (#0-7 for PRESET, #0-15 for user programs) into Control Changes
- VRA8-U CTRL stores the current control values and the user programs (#8-15) in a Web browser (localStorage)
- We recommend using Google Chrome, which implements Web MIDI API
- We recommend [loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html) (virtual loopback MIDI cable) to connect VRA8-U

## Details of Control Change

- Notes
    - $ : Disabled in Paraphonic Mode
    - $$ : Disabled in Paraphonic Mode or if Osc 1 Wave is Pls
- Osc 1 Wave [Saw|-|Tri|Pls|Sqr]
    - 0 (0-47): Saw Wave
    - 64 (48-79): Triangle Wave
    - 96 (80-111): Pulse Wave (Shape adjustable)
    - 127 (112-127): Square Wave
- Osc 1 Shape $ [-|+]
    - -64 (0): Pulse Width 0% (min)
    - -48 (16): Pulse Width 12.5%
    - -32 (32): Pulse Width 25%
    - +0 (64): Pulse Width 50%
    - +63 (127): Pulse Width 99.2% (max)
- Mixer Sub Osc $$
- Osc 2 Wave $ [Saw|-|Tri|Nos|Sqr]
    - 0 (0-47): Saw Wave
    - 64 (48-79): Triangle Wave
    - 96 (80-111): White Noise
    - 127 (112-127): Square Wave
- Osc 2 Coarse $ [-|+]
    - -24 (0): -24 semitone (min)
    - +24 (127): +24 semitone (max)
- Osc 2 Fine $ [-|+]
    - -64 (0): -100 cent (min)
    - +63 (127): +98.4375 cent (max)
- Filter Cutoff
    - 4: f = 452.9 Hz (min)
    - 64: f = 2561.9 Hz
    - 124: f = 14492.6 Hz (max)
- Filter Resonance
    - 16 (0-23): Q = 0.7 (min)
    - 32 (24-39): Q = 1.0
    - 48 (40-55): Q = 1.4
    - 64 (56-71): Q = 2.0
    - 80 (72-87): Q = 2.8
    - 96 (88-103): Q = 4.0
    - 112 (104-127): Q = 5.6 (max)
- Filter EG Amt [-|+], LFO Filter Amt [-|+]
    - -60 (4): -120 (min)
    - +60 (124): +120 (max)
- Filter Key Track $ [0.0|0.5|1.0]
    - 0 (0-31): 0.0
    - 64 (32-95): 0.5
    - 127 (96-127): 1.0
- EG Decay, Amp Decay
    - 127: No Decay
- EG Osc Amt [-|+], LFO Osc Amt [-|+]
    - Pitch
        - -39 (25): -24 semitone (min)
        - -27 (37): -12 semitone
        - -16 (48): -1 semitone
        - -12 (52): -75 cent
        - -8 (56): -50 cent
        - -4 (60): -25 cent
        - +0 (64): +0 cent
        - +4 (68): +25 cent
        - +8 (72): +50 cent
        - +12 (76): +75 cent
        - +16 (80): +1 semitone
        - +27 (91): +12 semitone
        - +39 (103): +24 semitone (max)
    - Shape
        - -63 (1): -126 (min)
        - +63 (127): +126 (max)
- EG Osc Dst [P|P2|S1], LFO Osc Dst [P|P2|S1]
    - 0 (0-31): Osc 1 & 2 Pitch
    - 64 (32-95): Osc 2 Pitch
    - 127 (96-127): Osc 1 Shape
- Voice Mode [Par|Mon|Lgt]
    - 0 (0-31): Paraphonic (LFO Single Trigger)
    - 64 (32-95): Monophonic (EG & LFO Multi Trigger)
    - 127 (96-127): Legato (Monophonic, EG & LFO Single Trigger, Auto Portamento)
- LFO Wave [T1|T2|Saw|SH|Sqr]
    - 0 (0-15): Triangle Wave (-0.5 to +0.5)
    - 32 (16-47): Triangle Wave 2 (Key Sync, -0.5 to +0.5)
    - 64 (48-79): Saw Wave (Key Sync, 0.0 to 1.0)
    - 96 (80-111): Sample & Hold (Key Sync, 0.0 to 1.0)
    - 127 (112-127): Square Wave (Key Sync, 0.0 to 1.0)
- LFO Rate
    - 0: 0.2 Hz (min)
    - 64: 2 Hz
    - 96: 6.3 Hz
    - 127: 20 Hz (max)
- Chorus Mode [Off|M|PS|S|S2]
    - 0 (0-15): Chorus Off
    - 32 (16-47): Mono Chorus
    - 64 (48-79): Pseudo-Stereo Chorus
    - 96 (80-111): Stereo Chorus
    - 127 (112-127): Stereo 2-phase Chorus
- Chorus Rate
    - 4: LFO Frequency 0.06 Hz (min)
    - 32: LFO Frequency 0.48 Hz
    - 64: LFO Frequency 0.95 Hz
    - 127: LFO Frequency 1.9 Hz (max)
- Chorus Depth
    - 0: Delay Time +/- 0.0 ms (min)
    - 32: Delay Time +/- 2.0 ms
    - 64: Delay Time +/- 4.1 ms
    - 126: Delay Time +/- 8.1 ms (max)
- Chorus Delay Time
    - 0: 0.03 ms (min)
    - 64: 8.2 ms
    - 80: 10.3 ms
    - 127: 16.3 ms (max)
- Pitch Bend Range
    - 0: 0 semitone (min)
    - 24: 24 semitone (max)

## Sample Chorus Settings

- Setting C0 -- Chorus Mode: 127, Chorus Rate: 32, Chorus Depth: 32, Chorus Delay Time: 64
- Setting C1 -- Chorus Mode: 127, Chorus Rate: 16, Chorus Depth: 32, Chorus Delay Time: 64
- Setting C2 -- Chorus Mode: 127, Chorus Rate: 48, Chorus Depth: 32, Chorus Delay Time: 64
- Setting D1 -- Chorus Mode: 127, Chorus Rate: 16, Chorus Depth: 32, Chorus Delay Time: 80
- Setting D2 -- Chorus Mode: 127, Chorus Rate: 16, Chorus Depth: 40, Chorus Delay Time: 60
- Setting D3 -- Chorus Mode: 127, Chorus Rate: 32, Chorus Depth: 24, Chorus Delay Time: 60
- Setting J1 -- Chorus Mode: 127, Chorus Rate: 32, Chorus Depth: 32, Chorus Delay Time: 20
- Setting J2 -- Chorus Mode: 127, Chorus Rate: 48, Chorus Depth: 32, Chorus Delay Time: 20

## MIDI Implementation Chart

      [United Synthesizer]                                            Date: 2022-08-17                  
      Model: Digital Synth VRA8-U     MIDI Implementation Chart       Version: 0.0.0                    
    +-------------------------------+---------------+---------------+----------------------------------+
    | Function...                   | Transmitted   | Recognized    | Remarks                          |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Basic        Default          | x             | 1             |                                  |
    | Channel      Changed          | x             | x             |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Mode         Default          | x             | Mode 3        |                                  |
    |              Messages         | x             | x             |                                  |
    |              Altered          | ************* |               |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Note                          | x             | 0-127         |                                  |
    | Number       : True Voice     | ************* | 12-108        |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Velocity     Note ON          | x             | x             |                                  |
    |              Note OFF         | x             | x             |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | After        Key's            | x             | x             |                                  |
    | Touch        Ch's             | x             | x             |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Pitch Bend                    | x             | o             |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Control                     1 | x             | o             | Modulation                       |
    | Change                     64 | x             | o             | Sustain Pedal [Off|On]           |
    |                               |               |               |                                  |
    |                            24 | x             | o             | Osc 1 Wave [Saw|-|Tri|Pls|Sqr]   |
    |                           102 | x             | o             | Osc 1 Shape $ [-|+]              |
    |                               |               |               |                                  |
    |                            26 | x             | o             | Mixer Sub Osc $$                 |
    |                               |               |               |                                  |
    |                            55 | x             | o             | Osc 2 Wave $ [Saw|-|Tri|Nos|Sqr] |
    |                            20 | x             | o             | Osc 2 Coarse $ [-|+]             |
    |                            21 | x             | o             | Osc 2 Fine $ [-|+]               |
    |                            25 | x             | o             | Mixer Osc Mix $ [1|2]            |
    |                               |               |               |                                  |
    |                            16 | x             | o             | Filter Cutoff                    |
    |                            17 | x             | o             | Filter Resonance                 |
    |                            18 | x             | o             | Filter EG Amt [-|+]              |
    |                            86 | x             | o             | Filter Key Track $ [0.0|0.5|1.0] |
    |                               |               |               |                                  |
    |                            23 | x             | o             | EG Attack                        |
    |                            19 | x             | o             | EG Decay                         |
    |                            27 | x             | o             | EG Sustain                       |
    |                            28 | x             | o             | EG Release                       |
    |                               |               |               |                                  |
    |                           104 | x             | o             | EG Osc Amt [-|+]                 |
    |                           105 | x             | o             | EG Osc Dst [P|P2|S1]             |
    |                            87 | x             | o             | Voice Mode [Par|Mon|Lgt]         |
    |                            22 | x             | o             | Portamento                       |
    |                               |               |               |                                  |
    |                            14 | x             | o             | LFO Wave [T1|T2|Saw|SH|Sqr]      |
    |                            80 | x             | o             | LFO Rate                         |
    |                            81 | x             | o             | LFO Depth                        |
    |                            15 | x             | o             | LFO Fade Time                    |
    |                               |               |               |                                  |
    |                            82 | x             | o             | LFO Osc Amt [-|+]                |
    |                             9 | x             | o             | LFO Osc Dst [P|P2|S1]            |
    |                            83 | x             | o             | LFO Filter Amt [-|+]             |
    |                           110 | x             | o             | Amp Level                        |
    |                               |               |               |                                  |
    |                            56 | x             | o             | Amp Attack                       |
    |                            57 | x             | o             | Amp Decay                        |
    |                            58 | x             | o             | Amp Sustain                      |
    |                            59 | x             | o             | Amp Release                      |
    |                               |               |               |                                  |
    |                            63 | x             | o             | Chorus Mode [Off|M|PS|S|S2]      |
    |                            61 | x             | o             | Chorus Rate                      |
    |                            60 | x             | o             | Chorus Depth                     |
    |                            62 | x             | o             | Chorus Delay Time                |
    |                               |               |               |                                  |
    |                            85 | x             | o             | Pitch Bend Range                 |
    |                               |               |               |                                  |
    |                            35 | x             | o             | Pitch Bend by CC [-|+]           |
    |                       112-119 |               |               | Program Change #0-7 by CC        |
    |                            90 | x             | x             | [Reserved]                       |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Program                       | x             | o             |                                  |
    | Change       : True #         | ************* | 0-7           |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | System Exclusive              | x             | x             |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | System       : Song Pos       | x             | x             |                                  |
    | Common       : Song Sel       | x             | x             |                                  |
    |              : Tune           | x             | x             |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | System       : Clock          | x             | x             |                                  |
    | Real Time    : Commands       | x             | x             |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Aux          : All Sound OFF  | x             | o 120         |                                  |
    | Messages     : Reset All      | x             | o 121         |                                  |
    |                Controllers    |               |               |                                  |
    |              : Local ON/OFF   | x             | x             |                                  |
    |              : All Notes OFF  | x             | o 123-127     |                                  |
    |              : Active Sense   | x             | x             |                                  |
    |              : Reset          | x             | x             |                                  |
    +-------------------------------+---------------+---------------+----------------------------------+
    | Notes                         | $ : Disabled in Paraphonic Mode                                  |
    |                               | $$ : Disabled in Paraphonic Mode or if Osc 1 Wave is Pls         |
    +-------------------------------+------------------------------------------------------------------+
      Mode 1: Omni On,  Poly          Mode 2: Omni On,  Mono          o: Yes                            
      Mode 3: Omni Off, Poly          Mode 4: Omni Off, Mono          x: No                             
