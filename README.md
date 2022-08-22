# Digital Synth VRA8-U v1.1.0

- 2022-08-21 ISGK Instruments
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

## Change History

- v1.1.1: Reduce noise in Chorus Mode M and S2
- v1.1.0: Add SS (Shaped Saw Wave) to Osc 1 Wave; Add Osc 1 Shape II; Reduce noise when Chorus Delay Time changes; Improve Random Ctrl of VRA-8 CTRL not to change Amp Level; Improve notes for $$ and $$$; Other changes
- v1.0.1: Reduce noise when Osc 1 Shape changes; Fix Parameter List

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

## [Parameter List](/VRA8-U-Parameter-List.md)

## [MIDI Implementation Chart](/VRA8-U-MIDI-Implementation-Chart.txt)
