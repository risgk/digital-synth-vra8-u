# Digital Synth VRA8-U v0.0.0

- 2022-04-30 ISGK Instruments
- <https://github.com/risgk/digital-synth-vra8-u>

## Concept

- Monophonic/Paraphonic United Synthesizer for Arduino Uno
    - 4-Voice Paraphonic
    - With built-in Chorus FX
    - Controlled by MIDI (MIDI Sound Module)

## Caution about Arduino

- We *strongly recommend* **Arduino AVR Boards core 1.8.3**
    - If you use other than AVR Boards core 1.8.3 (or modified this sketch), the sketch *may not work well*
        - CPU Busy LED (LED L) *may almost always lit*, rather than flashing occasionally

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

## VRA8-U CTRL

- MIDI Controller (Editor) Application for VRA8-U, HTML App (Web App)
- VRA8-U CTRL converts Program Changes (#0-7 for PRESET) into Control Changes
- VRA8-U CTRL stores the current control values and the user programs (#8-15) in a Web browser (localStorage)
- We recommend using Google Chrome, which implements Web MIDI API
- We recommend [loopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html) (virtual loopback MIDI cable) to connect VRA8-U

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

      [United Synthesizer]                                            Date: 2022-04-30              
      Model: Digital Synth VRA8-U     MIDI Implementation Chart       Version: 0.0.0                
    +-------------------------------+---------------+---------------+------------------------------+
    | Function...                   | Transmitted   | Recognized    | Remarks                      |
    +-------------------------------+---------------+---------------+------------------------------+
    | Basic        Default          | x             | 1             |                              |
    | Channel      Changed          | x             | x             |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | Mode         Default          | x             | Mode 3        |                              |
    |              Messages         | x             | x             |                              |
    |              Altered          | ************* |               |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | Note                          | x             | 0-127         |                              |
    | Number       : True Voice     | ************* | 21-108        |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | Velocity     Note ON          | x             | o (V=1-127)   |                              |
    |              Note OFF         | x             | x             |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | After        Key's            | x             | x             |                              |
    | Touch        Ch's             | x             | x             |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | Pitch Bend                    | x             | o             |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | Control                     1 | x             | o             | Modulation                   | MODULATION             
    | Change                     11 | x             | o             | Expression                   | EXPRESSION             
    |                            64 | x             | o             | Sustain Pedal (Off/On)       | SUSTAIN PEDAL (OFF/ON) 
    |                            46 | x             | o             | Pitch Bend By CC (-/+)       |
    |                               |               |               |                              |
    |                            24 | x             | o             | Osc 1 Wave (Sa/-/Si/-/P)     | OSC WAVE (SAW/PLS)     
    |                            54 | x             | o             | Osc 1 Shape (-/+) *          |
    |                            26 | x             | o             | Osc 1 Sub Level *            |
    |                            22 | x             | o             | Portamento                   | PORTAMENTO             
    |                               |               |               |                              |
    |                            53 | x             | o             | Osc 2 Wave (Sa/-/Si/N/P) *   |
    |                            20 | x             | o             | Osc 2 Coarse (-/+) *         | MONO OSC2 PITCH        
    |                            21 | x             | o             | Osc 2 Fine (-/+) *           | MONO OSC2 DETUNE       
    |                            25 | x             | o             | Osc Mix (1/2) *              | MONO OSC2 MIX (-/HF/FL)
    |                               |               |               |                              |
    |                            16 | x             | o             | Filter Cutoff                | CUTOFF                 
    |                            17 | x             | o             | Filter Resonance             | RESONANCE              
    |                            18 | x             | o             | Filter < EG Amt (-/+)        | EG > CUTOFF (-/+)      
    |                            86 | x             | o             | Filter Key Track (-/Hf/Fl) * |
    |                               |               |               |                              |
    |                            23 | x             | o             | EG Attack                    | ATTACK                 
    |                            19 | x             | o             | EG Decay                     | DECAY                  
    |                            27 | x             | o             | EG Sustain                   | SUSTAIN                
    |                            28 | x             | o             | EG Release *                 |
    |                               |               |               |                              |
    |                           104 | x             | o             | EG > Pitch Amt (-/+)         | EG > PITCH (-/+)       
    |                           105 | x             | o             | EG > Pitch 2 Amt (-/+) *     |
    |                            55 | x             | o             | EG > Shape 1 Amt (-/+) *     |
    |                             3 | x             | o             | EG > LFO Rate Amt (-/+)      |
    |                               |               |               |                              |
    |                            14 | x             | o             | LFO Wave (T1/T2/Sa/S&H/Sq)   | LFO WAVE (T/T2/S/RND/P)
    |                            80 | x             | o             | LFO Rate                     | LFO RATE               
    |                            81 | x             | o             | LFO Depth                    | LFO DEPTH              
    |                            15 | x             | o             | LFO Fade Time                | LFO FADE TIME          
    |                               |               |               |                              |
    |                            82 | x             | o             | LFO > Pitch Amt (-/+)        | LFO > PITCH (-/+)      
    |                             9 | x             | o             | LFO > Pitch 2 Amt *          |
    |                            52 | x             | o             | LFO > Shape 1 Amt (-/+) *    |
    |                            83 | x             | o             | LFO > Filter Amt (-/+)       | LFO > CUTOFF (-/+)     
    |                               |               |               |                              |
    |                            56 | x             | o             | Amp Attack                   |
    |                            57 | x             | o             | Amp Decay                    |
    |                            58 | x             | o             | Amp Sustain                  |
    |                            59 | x             | o             | Amp Release *                |
    |                               |               |               |                              |
    |                            63 | x             | o             | Chorus Mode (-/M/PS/S/S2)    | CHORUS (-/M/PS/S/S2)   
    |                            61 | x             | o             | Chorus Rate                  | CHORUS RATE            
    |                            60 | x             | o             | Chorus Depth                 | CHORUS DEPTH           
    |                            62 | x             | o             | Chorus Delay Time            | CHORUS DELAY TIME      
    |                               |               |               |                              |
    |                            87 | x             | o             | Voice Mode (Lgt/Mono/Para)   | VOICE (PARA/MONO/LGT)  
    |                            85 | x             | o             | Pitch Bend Range             | PITCH BEND RANGE       
    |                            89 | x             | o             | Filter < EG Vel Sens         | VELOCITY > CUTOFF      
    |                            31 | x             | o             | EG > Amp Mod (Off/On)        | AMP EG (OFF/ON)        
    |                               |               |               |                              |
    |                           110 | x             | o             | Amp Level                    |
    |                               |               |               |                              |
    |                   90, 112-119 | x             | x             | (Reserved)                   |
    +-------------------------------+---------------+---------------+------------------------------+
    | Program                       | x             | o             |                              |
    | Change       : True #         | ************* | 0-7           |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | System Exclusive              | x             | x             |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | System       : Song Pos       | x             | x             |                              |
    | Common       : Song Sel       | x             | x             |                              |
    |              : Tune           | x             | x             |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | System       : Clock          | x             | x             |                              |
    | Real Time    : Commands       | x             | x             |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | Aux          : All Sound OFF  | x             | o 120         |                              |
    | Messages     : Reset All      | x             | o 121         |                              |
    |                Controllers    |               |               |                              |
    |              : Local ON/OFF   | x             | x             |                              |
    |              : All Notes OFF  | x             | o 123-127     |                              |
    |              : Active Sense   | x             | x             |                              |
    |              : Reset          | x             | x             |                              |
    +-------------------------------+---------------+---------------+------------------------------+
    | Notes                         | * Invalid in Paraphonic Mode                                 |
    |                               |                                                              |
    +-------------------------------+--------------------------------------------------------------+
      Mode 1: Omni On,  Poly          Mode 2: Omni On,  Mono          o: Yes                        
      Mode 3: Omni Off, Poly          Mode 4: Omni Off, Mono          x: No                         
