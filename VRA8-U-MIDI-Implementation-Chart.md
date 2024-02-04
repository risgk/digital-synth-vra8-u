```
  [United Synthesizer]                                            Date: 2023-08-17                  
  Model: Digital Synth VRA8-U     MIDI Implementation Chart       Version: 2.2.6                    
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
|                           102 | x             | o             | Osc 1 Wave [Saw|-|Tri|Pls|Sqr]   |
|                            19 | x             | o             | Osc 1 Shape $$                   |
|                            20 | x             | o             | Osc 1 Morph $$                   |
|                            23 | x             | o             | Mixer Sub Osc $$$                |
|                               |               |               |                                  |
|                           104 | x             | o             | Osc 2 Wave $ [Saw|-|Tri|Nos|Sqr] |
|                            85 | x             | o             | Osc 2 Coarse $ [-|+]             |
|                            76 | x             | o             | Osc 2 Fine $ [-|+]               |
|                            21 | x             | o             | Mixer Osc Mix $ [1|2]            |
|                               |               |               |                                  |
|                            74 | x             | o             | Filter Cutoff                    |
|                            71 | x             | o             | Filter Resonance                 |
|                            24 | x             | o             | Filter EG Amt [-|+]              |
|                            26 | x             | o             | Filter Key Track $ [0.0|0.5|1.0] |
|                               |               |               |                                  |
|                            73 | x             | o             | EG Attack                        |
|                            75 | x             | o             | EG Decay                         |
|                            53 | x             | o             | EG Sustain                       |
|                            72 | x             | o             | EG Release                       |
|                               |               |               |                                  |
|                            91 | x             | o             | EG Osc Amt [-|+]                 |
|                            89 | x             | o             | EG Osc Dst [P|2P|1S]             |
|                            18 | x             | o             | Voice Mode [Par|-|Mon|Lgt|LP]    |
|                             5 | x             | o             | Portamento                       |
|                               |               |               |                                  |
|                            30 | x             | o             | LFO Wave [T1|T2|Saw|SH|Sqr]      |
|                             3 | x             | o             | LFO Rate                         |
|                            17 | x             | o             | LFO Depth                        |
|                            56 | x             | o             | LFO Fade Time                    |
|                               |               |               |                                  |
|                            13 | x             | o             | LFO Osc Amt [-|+]                |
|                           103 | x             | o             | LFO Osc Dst [P|2P|1S]            |
|                            25 | x             | o             | LFO Filter Amt [-|+]             |
|                            15 | x             | o             | Amp Level                        |
|                               |               |               |                                  |
|                            52 | x             | o             | Amp Attack                       |
|                            92 | x             | o             | Amp Decay                        |
|                            54 | x             | o             | Amp Sustain                      |
|                            90 | x             | o             | Amp Release                      |
|                               |               |               |                                  |
|                            27 | x             | o             | Chorus Mode [Off|M|PS|S|S2]      |
|                            61 | x             | o             | Chorus Rate                      |
|                            60 | x             | o             | Chorus Depth                     |
|                            62 | x             | o             | Chorus Delay Time                |
|                               |               |               |                                  |
|                            57 | x             | o             | Pitch Bend Range                 |
|                            63 | x             | o             | Chorus Bypass [Off|On]           |
|                               |               |               |                                  |
|                            35 | x             | o             | Pitch Bend by CC [-|+]           |
|                       112-119 |               |               | Program Change #8-15 by CC       |
|                           111 | x             | x             | [Reserved]                       |
+-------------------------------+---------------+---------------+----------------------------------+
| Program                       | x             | o             |                                  |
| Change       : True #         | ************* | 0-15          |                                  |
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
|                               | $$ : Disabled in Paraphonic or if Osc 1 Wave is not Pls          |
|                               | $$$ : Disabled in Paraphonic or if Osc 1 Wave is Pls             |
+-------------------------------+------------------------------------------------------------------+
  Mode 1: Omni On,  Poly          Mode 2: Omni On,  Mono          o: Yes                            
  Mode 3: Omni Off, Poly          Mode 4: Omni Off, Mono          x: No                             
```
