# Sound Design Guide for Vital Wavetable Synthesizer

## Core Harmonic Principles

Every sound is made of sine waves. The character of a sound — its timbre — is determined by which sine waves (harmonics) are present and at what amplitudes. The lowest harmonic is the fundamental, which determines perceived pitch. All higher harmonics are called overtones, and their frequencies are integer multiples of the fundamental.

### Waveform-to-Timbre Mappings

Sawtooth: Contains all harmonics (even and odd), amplitudes decrease uniformly. Sounds bright and buzzy. Harmonically similar to brass and bowed strings. The richest standard waveform — ideal starting point when you need lots of harmonic content to filter.

Square: Contains only odd harmonics. Sounds hollow and woody. Similar to woodwinds like clarinet. In Vital, square is a pulse wave at 50% width.

Triangle: Contains only odd harmonics but upper harmonics are much weaker than square. Sounds mellow and flute-like. Good for bells, chimes, and sub-bass layers. Also useful for mixing with other waveforms to boost specific odd harmonics without adding too much brightness.

Pulse (variable width): As pulse width narrows from 50% (square) toward 0%, even harmonics appear and the sound becomes brighter and more nasal, approaching sawtooth-like character. Narrow pulses have a crisp, metallic quality with an undulating harmonic pattern similar to acoustic instruments. In Vital, wavetable position on a basic shapes table can sweep pulse width.

Sine: A single harmonic with no overtones. The purest, most fundamental tone. Essential for sub-bass, 808-style bass, and as a modulation source.

### Key Principle: Harmonics Determine Character, Not Waveshape

Two sounds can have very similar harmonics yet look completely different as waveforms. When designing sounds, think in terms of harmonic content (which frequencies are present and how loud), not visual waveform shape. This is why filtering and wavetable position are so powerful — they reshape harmonic content directly.

### The First 5-10 Harmonics Matter Most

When trying to match a target sound, focus on getting the lowest 5-10 harmonics close to their target amplitudes. Higher harmonics contribute brightness and texture but the fundamental character of a sound lives in the lower harmonics.

## Vital's Architecture and How It Maps to Synthesis Principles

### Oscillators (3 + 1 sampler)

Vital uses wavetable oscillators. Wavetable position replaces traditional waveform selection — instead of choosing "sawtooth" or "square," you sweep through a table of waveforms. This is more powerful because:
- A single oscillator can morph between waveform types via wavetable position modulation
- Custom wavetables can contain harmonics impossible with standard analog waveforms
- Wavetable position automation (via LFO or envelope) creates evolving timbres

Each oscillator also has: unison voices (up to 16), unison detune, stereo spread, level, pan, phase randomization, and distortion/spectral warping modes.

Vital's basic shapes wavetable contains standard analog waveforms and is the go-to for classic subtractive-style patches.

### Filters (2)

Vital offers many filter types. Key ones and their uses:

Low-pass (most common): Removes high frequencies, passes low. Makes sounds darker/warmer. Our ears expect this naturally — high frequencies attenuate more in real environments. Available in 12dB and 24dB slopes. 12dB sounds more open/natural, 24dB gives sharper, more dramatic cutoff. Use 24dB for aggressive bass and leads, 12dB for pads and acoustic emulations.

High-pass: Removes low frequencies. Useful for thinning out sounds, creating cymbals/hi-hats, clearing low-end mud. Our brains can perceive the correct pitch even when the fundamental is removed, because overtone spacing still implies it.

Band-pass: Passes only a narrow frequency band. Creates focused, vocal-like, or telephone-like qualities. Useful for creating resonant plucks and formant-like effects.

Notch (band-reject): Removes a narrow band while passing everything else. Useful for phaser-like effects and removing specific problem frequencies.

Comb: Creates metallic, pitched resonances based on delay time. Useful for Karplus-Strong-style plucked strings and metallic textures.

Formant: Shapes sound through vowel-like resonances. Excellent for vocal pads and talking-bass effects.

### Cutoff Frequency

Sets where filtering begins. In Vital, cutoff is normalized 0-127 (MIDI-style). Lower values = more filtering. For a low-pass filter: cutoff at ~30 gives a very dark, subby tone. Cutoff at ~60-80 gives a warm, rounded tone. Cutoff at ~100+ is mostly open/bright. The cutoff is the single most important filter parameter — small changes create large timbral shifts.

### Resonance

Amplifies frequencies near the cutoff point. In Vital, 0-1 range. Low resonance (0-0.25) adds subtle presence. Moderate resonance (0.25-0.5) creates a nasal, vocal quality. High resonance (0.5-0.8) creates an aggressive, acidic peak. Maximum resonance can cause self-oscillation where the filter produces a sine tone at the cutoff frequency — usable as an additional sound source.

Important: High resonance reduces surrounding frequencies due to gain compensation. The resonant peak gets louder but the rest of the signal gets quieter.

### Filter Slope

12dB/oct (2-pole): Gentler rolloff. Sounds more natural and open. Better for pads, acoustic emulations, and when you want some brightness to remain. A 12dB low-pass sounds slightly brighter than a 24dB at the same cutoff.

24dB/oct (4-pole): Steeper rolloff. More aggressive filtering. Better for basses, leads, and when you want a clear distinction between filtered and unfiltered content. Classic "analog synth" sound.

### Envelopes (3)

ADSR envelopes control how parameters change over time after a note is played:

Attack: Time for the parameter to rise from zero to maximum after key press. Measured in seconds. 0s = instant. 0.01-0.05s = percussive click. 0.1-0.3s = moderate fade-in. 0.5s+ = slow pad-like swell.

Decay: Time to fall from maximum to the sustain level. 0.05-0.2s = plucky, percussive. 0.5-2s = gradual settling. Longer = slow evolution.

Sustain: Level held while key is pressed (percentage, not time). 0% = sound dies away completely during decay. 50% = settles to half volume. 100% = no decay effect, stays at maximum.

Release: Time to fall from sustain level to zero after key release. 0s = instant stop. 0.1-0.3s = natural stop. 0.5-2s = lingering tail. 3s+ = ambient wash.

### Critical Envelope Insight: Filter Envelope as Amplitude Shaper

Removing frequencies also reduces overall loudness. A filter envelope effectively acts as a secondary amplitude envelope because cutting harmonics cuts power. Best practice: use the filter envelope to shape brightness changes (which also affects perceived volume), then use the amplitude envelope for final volume contour. This produces more natural, complex dynamics than amplitude envelope alone.

For acoustic instrument emulation especially: the filter envelope controls the brightness arc (higher harmonics rise last, fall first), and the amplitude envelope handles the overall volume shape. Woodwinds in particular have envelopes almost entirely dependent on filter behavior — the brightness change IS the volume change.

### LFOs (4)

Low-frequency oscillators create cyclic modulation. They are not heard directly but modulate other parameters.

Common routings and their effects:
- LFO → Pitch: Vibrato. Use sine/triangle, 4-7 Hz, subtle depth (few cents). Natural-sounding pitch wobble.
- LFO → Amplitude: Tremolo. Use sine/triangle, 4-7 Hz, moderate depth.
- LFO → Filter cutoff: Wah/sweep effect. Use sine/triangle for smooth sweeps, square for rhythmic gating.
- LFO → Wavetable position: Timbral morphing. Creates evolving, shifting character unique to wavetable synthesis.
- LFO → Pulse width (or wavetable position on pulse table): PWM. Slow sine/triangle at ~2 Hz with moderate depth creates thick, string-section-like chorus effect. One of the most useful modulations for pads and strings.

Rate ranges: Under 1 Hz = slow evolution, ambient movement. 1-5 Hz = musical modulation (vibrato, tremolo, gentle movement). 5-20 Hz = fast modulation, can create buzzy/rough textures. 20+ Hz = enters audio rate, creates FM-like sidebands and metallic tones.

In Vital, LFOs can be free-running or tempo-synced. Tempo sync is essential for rhythmic gating, sidechain-style pumping, and trance gates.

### Unison

Stacks multiple detuned copies of an oscillator. In Vital, up to 16 voices per oscillator.

Unison voices at 2-4: Subtle thickening, natural doubling effect.
Unison voices at 4-8: Rich, wide, supersaw-style stacks. Classic trance/EDM leads and pads.
Unison voices at 8-16: Massive, wall-of-sound. Can become washy — use with care.

Unison detune controls the pitch spread between voices. Small detune (0.1-0.3) = subtle warmth and movement. Moderate detune (0.3-0.6) = obvious chorusing, wide stereo. High detune (0.6-1.0) = aggressive, almost dissonant spread.

Unison broadens harmonics similarly to real bowed strings and chorus effects. Unlike PWM, unison preserves the natural undulation of harmonic amplitudes and adds low-level inharmonic content.

### Effects

Vital's effects chain (chorus, compressor, delay, distortion, EQ, filter, flanger, phaser, reverb) shapes the final sound. Key uses:

Chorus: Thickens and widens. Essential for string pads, supersaw leads. 30-50% wet is typical.
Reverb: Adds space and atmosphere. Short (0.3-1s) for room ambience, medium (1-3s) for halls, long (3s+) for ambient/ethereal.
Delay: Rhythmic echoes. Sync to tempo for musical repeats. Use feedback 20-50% typically.
Distortion: Adds harmonics and grit. Soft clip for warmth, hard clip for aggression, bitcrush for lo-fi/8-bit.
Phaser/Flanger: Sweeping comb-filter effects. Useful for movement in pads and leads.
Compressor: Evens dynamics. Useful after heavy modulation to keep levels consistent.
EQ: Surgical frequency adjustment. Cut lows on pads to avoid mud, boost presence (2-5 kHz) on leads.

## Sound Category Recipes

### Strings and Pads

Foundation: Sawtooth or pulse-width wavetable. Two oscillators detuned by small amounts (5-15 cents each direction) creates the essential ensemble thickness.

Filter: Low-pass, cutoff in the warm zone (60-80), low resonance (0-15%). 12dB slope often sounds more natural for strings.

Amplitude envelope: Slow-moderate attack (0.1-0.8s), maximum sustain (100%), moderate-long release (0.5-2s).

Filter envelope: Similar shape to amplitude but can have slightly faster attack so brightness arrives just after volume onset. Set envelope amount moderate (40-70%).

LFO: Route to pitch for vibrato — sine/triangle, 4-6 Hz, very subtle depth. For PWM strings, route LFO to wavetable position on a pulse-width table at ~2 Hz, moderate depth.

Unison: 2-4 voices with subtle detune for acoustic strings, 4-8 voices for synth pads and supersaws.

Effects: Chorus is almost mandatory for strings/pads. Add reverb for space. Slow phaser can add movement.

### Brass

Foundation: Sawtooth wave. Brass instruments have all harmonics present. For richer brass, add a second oscillator one octave up at lower volume (-6 to -14 dB).

Filter: Low-pass, 24dB. Start with cutoff low (~30-50). Use filter envelope with moderate attack (0.05-0.15s) to simulate breath building pressure — this is what makes brass sound like brass. The brightening-on-attack is the defining characteristic. Moderate resonance (10-20%) adds presence.

Amplitude envelope: Near-zero attack, full sustain, moderate release (0.19-0.5s).

Filter envelope: Attack slightly longer than amplitude (0.05-0.15s), high sustain (90-100%), release similar to amplitude. Envelope amount: 60-90%.

LFO: Subtle amplitude tremolo — triangle, 5-7.5 Hz, very low depth (5%).

### Woodwinds

Foundation: Square/pulse waves (odd harmonics dominate in woodwinds). Clarinet = near-square pulse (~49% width). Oboe/bassoon = narrower pulse (5-20%) mixed with a second oscillator.

Filter: Low-pass, cutoff starting very low (~20-40 Hz equivalent). The filter envelope does almost all the work — high envelope amount (60-100%). Woodwinds are the most filter-envelope-dependent sounds. The brightness change IS the sound's dynamic character.

Filter envelope: Attack 0.09-0.16s (simulating breath onset), high sustain (80-100%), release 0.14-0.32s. This is more important than the amplitude envelope for woodwinds.

Amplitude envelope: Can be minimal — let the filter envelope handle perceived dynamics. If needed: near-zero attack, full sustain, short-moderate release.

LFO: Very subtle pitch vibrato — triangle, 5-7.5 Hz, just a few cents depth. Woodwind vibrato is gentle.

### Bass

Foundation: For sub-bass/808: sine wave or triangle, tuned down 1-2 octaves. For synth bass: square or sawtooth, tuned down 1-2 octaves. Two oscillators at different octaves (e.g., -2 oct and -1 oct) create a fuller bass with both sub weight and harmonic presence.

Filter: Low-pass. For deep sub-bass, keep cutoff low (25-50). For growly/aggressive bass, use higher cutoff (50-80) with moderate-high resonance (35-60%). Filter envelope with short decay (0.15-0.5s) creates the classic plucky bass sound.

Amplitude envelope: Zero attack for punch. For sustained bass: full sustain, short release. For plucky bass: zero sustain, moderate decay (0.3-0.7s).

Voicing: Mono is standard for bass — prevents muddiness from overlapping low notes. Enable glide/portamento (0.01-0.04s) for slides between notes.

For acid bass: sawtooth or square, low cutoff, high resonance (60%+), and manually automate filter cutoff during performance. The resonant peak sweeping through harmonics is the defining acid sound.

### Leads

Foundation: Pulse waves (10-30% width) or sawtooth. Two oscillators slightly detuned (4-10 cents) for thickness. Oscillator sync (slave tuned higher than master) creates screaming, harmonically complex leads — the sync sweep is a classic lead technique.

Filter: Low-pass or band-pass. Leads can range from mellow (low cutoff, ~60) to bright (high cutoff, ~90+). Moderate resonance (25-50%) adds bite and presence.

Envelope: Short attack (0-0.05s) for percussive leads, moderate for flowing leads. Sustain 70-100%. Release 0.3-0.6s.

Glide: Essential for expressive lead playing. 0.02-0.04s for fast slides. Mono voicing.

LFO: PWM for thick, evolving texture. For screaming sync leads: route slow LFO (<1 Hz) to the synced oscillator's pitch while using unison and chorus.

Unison: 2-4 voices for subtle width, more for massive supersaws. For trance leads, 4-7 voices of unison on detuned sawtooths is standard.

### Tuned Percussion (Bells, Mallets, Plucks)

Foundation: Triangle waves are the go-to — their weak upper harmonics suit metallic/bell sounds. Two triangle oscillators at inharmonic intervals (e.g., +5 semitones, or +2 octaves +6 semitones) create bell-like inharmonicity. For marimba: triangle + triangle up 2 octaves at lower amplitude.

Filter: Can be open (no filtering) for bright bells or use moderate low-pass for darker mallets. Filter envelope with short decay adds the initial brightness burst of a mallet strike.

Amplitude envelope: Zero attack (instant transient), moderate-long decay (1-3s), zero sustain, release matching decay. This is the defining envelope shape for percussion.

### Untuned Percussion

Noise is the primary source for snares, hi-hats, cymbals, claps.

Snare: Noise mixed with a low triangle wave (-1 octave). Very short amplitude decay (0.15-0.3s). Filter mostly open.

Hi-hat/Cymbal: Noise only, filtered through high-pass or band-pass. Short decay for closed hat (0.04-0.1s), longer for open hat/cymbal (0.5-1.8s). Resonance adds metallic pitch.

Clap: Noise with a fast square LFO on amplitude (30+ Hz) creating the multiple-strike flutter. Short decay. Band-pass filtering.

Kick/Bass drum: Triangle wave tuned very low (-2 octaves). No noise. Very short decay (0.12s). Can add a pitch envelope that sweeps down quickly for the "punch" transient.

### Vocal/Formant Sounds

Foundation: Sawtooth (rich harmonic content needed for formant shaping) or pulse waves. For choir: two pulse oscillators at different widths (15% and 25%), one detuned down 2 octaves.

Filter: This is where Vital's formant filter shines. Alternatively, use a low-pass with high resonance (50-70%) to create a single formant peak. Cutoff around 55-66% range for vocal character.

Envelope: Slow attack (0.3s), full sustain, moderate-long release (0.9s). Vocals swell in, don't appear instantly.

LFO: Slow pitch vibrato — triangle, 2-2.5 Hz, subtle (20 cents). This is the "singing" quality.

## Reverse Engineering Framework

When trying to recreate a target sound, follow this systematic approach:

Step 1 — Identify harmonic content: What harmonics are present? Are they all harmonics (sawtooth-like) or only odd (square/triangle-like)? Do they decrease uniformly or undulate? Undulating harmonics suggest mixed oscillators at different pitches, pulse width variation, or sync. Broadened upper harmonics suggest unison or chorus. Choose oscillator waveforms, tunings, and levels to match the first 5-10 harmonics.

Step 2 — Shape the frequency envelope: Higher harmonics typically rise last and fall first in natural sounds. Use the filter envelope to replicate this. Set cutoff low, envelope amount high, and adjust attack/decay/release to match how brightness evolves over the note's lifetime.

Step 3 — Match the amplitude envelope: After the filter envelope is handling brightness dynamics, use the amplitude envelope for the overall volume shape. Often less adjustment is needed here than expected because the filter envelope already handles much of the perceived dynamics.

Step 4 — Add modulation and effects: Vibrato (LFO → pitch), tremolo (LFO → amplitude), movement (LFO → filter/wavetable position), and spatial effects (reverb, delay, chorus) add the final layer of realism and interest.

## Key Design Heuristics

These practical rules should guide parameter decisions:

Two detuned oscillators always sound richer than one. Even 4-15 cents of detuning adds life and movement that a single oscillator cannot achieve. This is the single easiest way to improve any patch.

The filter envelope is more important than most users realize. Use it as your primary shaping tool, not just the amplitude envelope. For any sound that changes brightness over time (which is most natural sounds), the filter envelope should be doing heavy lifting.

Cutoff frequency is the most critical parameter to get right. Small changes in filter cutoff create larger perceived differences than similar-magnitude changes to almost any other parameter.

Resonance adds character but costs volume. High resonance makes frequencies near cutoff louder but reduces everything else. Use it deliberately, not by default.

Unison for organic thickness, chorus for stereo width, PWM for evolving density. These three techniques all "thicken" a sound but in different ways. Unison preserves harmonic variation (more natural), PWM tends to even out harmonic levels (smoother), chorus adds stereo movement. They can be combined.

For acoustic emulation, harmonic irregularity is key. Real instruments don't have smoothly decreasing harmonics. Use two oscillators at non-octave intervals, subtle wavetable position offsets, or slight detuning to break up the regularity of synthetic harmonics.

Oscillator sync creates complex harmonics that are hard to achieve otherwise. Slave tuned higher than master: metallic, screaming tones. At exact octave intervals: sync has no effect. Between octaves: maximum harmonic complexity. Great for leads, plucked strings, and evolving textures.

Mono voicing for bass and leads prevents muddiness and enables glide. Poly for pads, chords, and anything that needs to play multiple notes simultaneously.

Short filter envelope decay with high amount creates pluck/transient character. Long filter attack with high amount creates breath/swell character. The filter envelope amount controls how dramatic the brightness change is.

Noise is essential for percussion and texture. It has no pitch or harmonics — it's pure spectral energy shaped entirely by the filter. High-pass filtered noise = hi-hats and cymbals. Band-pass filtered noise with resonance = metallic percussion. Low-pass noise with envelope = snare body.

Start with more harmonics than you need, then subtract. It's easier to filter away unwanted harmonics (subtractive synthesis) than to add missing ones. Choose bright waveforms and sculpt with filters rather than starting too dark.

Wavetable position modulation is Vital's superpower. Unlike traditional analog synths that are stuck with fixed waveforms, modulating wavetable position with an LFO or envelope creates timbral evolution that would require complex setups on hardware. Use it for evolving pads, morphing textures, and sounds that shift character over time.

For genre-specific sounds: EDM/trance leads use 4-8 unison sawtooth voices with moderate detune and chorus. Trap/hip-hop 808s use sine waves with long decay and subtle saturation. Lo-fi sounds use bitcrushing, sample rate reduction, and filtered noise. Ambient pads use slow wavetable modulation, long reverb, and gentle filter movement.

## Vital-Specific Parameter Ranges Reference

Cutoff (0-127 MIDI-style): ~20 = very dark/subby, ~40 = warm/muffled, ~60 = balanced, ~80 = bright/present, ~100+ = mostly open.

Resonance (0-1): 0 = none, 0.15 = subtle, 0.3 = noticeable, 0.5 = strong/nasal, 0.7+ = aggressive/self-oscillating territory.

Envelope times: 0s = instant, 0.01-0.05s = percussive, 0.1-0.3s = moderate, 0.5-1.5s = slow, 2s+ = very slow/ambient.

Unison voices: 1 = mono, 2-3 = subtle thickening, 4-6 = rich/wide, 7-16 = massive/wall-of-sound.

Unison detune (0-1): 0.1-0.2 = subtle, 0.3-0.5 = moderate chorus, 0.6+ = aggressive spread.

LFO rate: 0.1-0.5 Hz = slow evolution, 1-5 Hz = musical modulation, 5-20 Hz = fast texture, 20+ Hz = audio-rate FM.

Effect wet/dry: 20-30% = subtle, 40-60% = prominent, 70%+ = dominant/washy.
