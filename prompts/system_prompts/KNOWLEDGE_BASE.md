# Vital Synthesizer Knowledge Base

## 1. Signal Flow

### Voice Path Overview

```
Oscillators 1-3 + Sample Player
        |
        | (each has independent destination routing)
        v
  +--[Filter 1]--+--[Filter 2]--+    "Effects" bus    "Direct Out" bus
  |     parallel / serial        |         |                  |
  +--------- voice sum ---------+-------- add               |
                  |                                           |
          × amplitude (env_1 × velocity × voice_amp)         × amplitude
                  |                                           |
         Effect Chain (9 FX, serial)                          |
                  |                                           |
                  +------------- output sum -----------------+
                                     |
                              Master Volume
                                     |
                                Audio Output
```

### Oscillator Destination Routing

Each oscillator and the sample player independently routes to one of these destinations via `osc_X_destination` / `sample_destination`:

| Value | Destination | Behavior |
|-------|-------------|----------|
| 0 | Filter 1 | Routed to Filter 1 only |
| 1 | Filter 2 | Routed to Filter 2 only |
| 2 | Filter 1+2 | Routed to both filters |
| 3 | Effects | Bypasses filters, goes straight to effects chain |
| 4 | Direct Out | Bypasses both filters and effects chain |

**Default routing:** Osc 1 → Filter 1, Osc 2 → Filter 2, Osc 3 → Filter 1.

**Fallback behavior:** If an oscillator is routed to a filter that is turned off, its audio automatically falls through to the effects bus instead.

### Filter Routing Modes

Filters 1 and 2 can operate in three modes depending on `filter_1_filter_input` and `filter_2_filter_input`:

- **Parallel** (default): Both filters process their inputs independently, outputs are summed.
- **Serial forward** (`filter_2_filter_input = 1`): Filter 1 processes first, its output feeds into Filter 2's input. Only Filter 2's output is used.
- **Serial backward** (`filter_1_filter_input = 1`): Filter 2 processes first, its output feeds into Filter 1's input. Only Filter 1's output is used.

Each filter also has a dry/wet mix (`filter_X_mix`) that crossfades between the unfiltered input and the filter output.

### Amplitude

The voice amplitude is computed as: `envelope_1 × velocity_tracking × voice_amplitude`, then **squared** for perceptual loudness. Envelope 1 is always the amplitude envelope and runs at audio rate.

### Effects Chain

The 9 effects are processed in a **serial chain** with configurable order (`effect_chain_order`):

| Index | Effect | Notes |
|-------|--------|-------|
| 0 | Chorus | |
| 1 | Compressor | |
| 2 | Delay | |
| 3 | Distortion | |
| 4 | EQ | 3-band equalizer |
| 5 | Filter FX | A third filter instance, separate from voice filters 1 and 2 |
| 6 | Flanger | |
| 7 | Phaser | |
| 8 | Reverb | |

Each effect has an on/off toggle (`chorus_on`, etc.). Disabled effects are skipped (passthrough). The chain order is encoded as a factorial permutation number (0 = default order above).

### Oscillator Cross-Modulation

Oscillators can FM or ring-modulate each other via the `osc_X_distortion_type` parameter. Types 7-12 enable cross-modulation:

- **FM Osc A/B**: Frequency modulation from another oscillator
- **RM Osc A/B**: Ring modulation from another oscillator
- **FM/RM Sample**: FM or ring mod from the sample player

For each oscillator, "Osc A" and "Osc B" refer to the other two oscillators in index order. For osc 1: A=osc 2, B=osc 3. For osc 2: A=osc 1, B=osc 3. For osc 3: A=osc 1, B=osc 2.

### Modulation System

Up to **64 simultaneous modulation connections**. Each connection links a source to any parameter with configurable amount, power curve, bipolar/stereo options.

**Modulation Sources:**

| Source | Count | Notes |
|--------|-------|-------|
| Envelopes | 6 | `env_1` is always amplitude (hardwired). `env_2`-`env_6` are free to assign. |
| LFOs | 8 | Wavetable-based, syncable to tempo |
| Random LFOs | 4 | Noise/random modulation sources |
| Per-note | — | `note`, `velocity`, `aftertouch`, `slide`, `lift`, `mod_wheel`, `pitch_wheel` |
| Macros | 4 | User-assignable macro knobs |
| Other | — | `random` (per-note random value), `stereo` (L/R split), `note_in_octave` |

---

## 2. Value Scaling Reference

Many parameters use non-linear scaling. The stored (JSON) value is transformed before being used by the DSP engine. When setting parameters, you must provide the **stored** value, not the actual/perceived value.

### Scaling Formulas

| Scale | Formula | How to set a target value |
|-------|---------|--------------------------|
| Quadratic | `actual = stored²` | `stored = √(target)` |
| Quartic | `actual = stored⁴` | `stored = ⁴√(target)` — i.e. `target^0.25` |
| Exponential | `actual = 2^stored` | `stored = log₂(target)` |
| Square Root | `actual = √(stored) + offset` | `stored = (target - offset)²` |

### Key Non-Linear Parameters

| Parameter | Scale | Stored Range | Actual Range | Example |
|-----------|-------|-------------|--------------|---------|
| `osc_X_level` | Quadratic | 0–1.0 | 0–1.0 | For 50% level: store `√0.5 = 0.707` |
| `osc_X_unison_detune` | Quadratic | 0–10.0 | 0–100% | For 20% detune: store `√20 = 4.472` |
| `sample_level` | Quadratic | 0–1.0 | 0–1.0 | Same as osc level |
| `env_X_attack` | Quartic | 0–2.378 | 0–32 secs | For 1s attack: store `1.0`. For 0.1s: store `0.562` |
| `env_X_decay` | Quartic | 0–2.378 | 0–32 secs | For 1s decay: store `1.0`. For 2s: store `1.189` |
| `env_X_release` | Quartic | 0–2.378 | 0–32 secs | For 0.5s release: store `0.841` |
| `env_X_delay/hold` | Quartic | 0–1.414 | 0–4 secs | For 1s: store `1.0` |
| `lfo_X_frequency` | Exponential | -7 to 9 | 0.008–512 Hz | For 1 Hz: store `0.0`. For 4 Hz: store `2.0` |
| `delay_frequency` | Exponential | -2 to 9 | 0.25–512 Hz | For 2 Hz (0.5s): store `1.0` |
| `reverb_decay_time` | Exponential | -6 to 6 | 0.016–64 secs | For 2s: store `1.0`. For 4s: store `2.0` |
| `portamento_time` | Exponential | -10 to 4 | 0.001–16 secs | For 0.1s: store `-3.32` |
| `volume` | SquareRoot | 0–7399 | -80 to +6 dB | `dB = √stored - 80`. For 0dB: store `6400` |

### Filter Cutoff (Special Case)

Filter cutoff is stored as **MIDI note numbers** (8–136), not Hz. The DSP converts to Hz via standard MIDI-to-frequency: `Hz = 8.176 × 2^(stored/12)`. Middle C (note 60) = 261.6 Hz. A4 (note 69) = 440 Hz. Note 100 ≈ 5274 Hz.
