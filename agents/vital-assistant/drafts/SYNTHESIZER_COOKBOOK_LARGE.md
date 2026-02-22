![](_page_0_Picture_0.jpeg)

Harmonics and oscillator waveforms

The most fundamental sound is the sine wave. Every sound whether it is natural or synthetic is made up of sine waves.

![](_page_2_Figure_4.jpeg)

Figure 1. All sounds, natural and synthetic, are made up of sine waves

The sound of a sine wave could be described as extremely mellow and not particularly interesting, but when numerous sine waves of different pitches and amplitudes are mixed together the sonic possibilities become endless.

It is possible to create *any* waveform using nothing but sine waves. Let's begin by creating a sawtooth wave. Each sine wave is going to have a different pitch and as they go higher in pitch they will decrease in amplitude. The first one will have the lowest pitch and it will in fact determine the overall pitch of the sawtooth. This is called the fundamental frequency. For the case of this example we will give it a pitch of 440 Hz corresponding to the A4 key.

![](_page_2_Figure_8.jpeg)

Figure 2. A 440 Hz sine wave and a graph representing its frequency and amplitude

The bottom portion of the figure is what is called a harmonic diagram. The horizontal axis is frequency/pitch and the vertical axis is amplitude. The spike represents the frequency and amplitude of the 440 sine wave. Let's add a second sine wave with a frequency of 880 Hz (440Hz x 2).

![](_page_3_Figure_2.jpeg)

Figure 3. A 440 Hz sine wave added to a 880 Hz sine wave create a new waveform

Notice there is a second spike in the diagram representing the 880 Hz sine wave. Now add a third sine wave at a frequency of 1320 Hz (440 Hz x 3)

![](_page_3_Figure_5.jpeg)

Figure 4. Three sine waves of frequency 440 Hz, 880 Hz, and 1320 Hz added together create a waveform that begins to look like a sawtooth wave.

Already the new waveform is beginning to lean to one side like a sawtooth wave. Keep adding sine waves that are frequency multiples of 440 Hz and eventually a sawtooth wave is produced.

![](_page_4_Figure_2.jpeg)

Figure 5. A sawtooth wave and its harmonic diagram

Each one of the harmonics(spikes) in the diagrams above are called partials. The first partial at the far left, as stated earlier, is known as the fundamental and it determines the pitch of the waveform. The other partials are all frequency multiples of the fundamental and they are known as overtones. Also notice that the fundamental is the loudest sine wave of all the harmonics and that as the overtones get higher in pitch their amplitudes decrease. There is of course nothing preventing us from mixing sine waves that all have the same amplitude it's just that in this particular case it is a requirement of creating a sawtooth that the amplitudes diminish with higher frequency. Just as a point of interest if we were to mix these harmonics all at the same amplitude it would produce something that as successively higher-pitched sine waves are added would at first look like a sawtooth wave with a bad complexion and as more harmonics are added would look nothing like a sawtooth at all. Harmonic amplitudes are important!

p.....

Figure 6. Waveform produced by setting the first 16 harmonics to equal amplitudes.

A square wave can be created using the same process. The difference is that a square wave is only made up of odd-numbered partials.

![](_page_5_Figure_1.jpeg)

Figure 7. A square wave has only odd partials. This square wave was produced by an *actual* oscillator. Notice the slight imperfections in the waveform. No oscillator produces perfect waveforms nor do any two oscillators produce identical waveforms.

Triangle waves are also made up of odd-numbered partials but the higher harmonics are weaker than in a square wave.

![](_page_5_Figure_4.jpeg)

Figure 8. A triangle wave has odd harmonics that are weaker than those of a square wave.

The process of adding sine waves together to create sounds is known as *additive synthesis*. This method is used on a few digital synthesizers and soft synths and has also been used by pipe organs for hundreds of years. In a pipe organ each pipe produces a sine wave of a different pitch and by controlling the amount of air to each pipe it is possible to control the individual amplitudes of each sine wave which in turn makes it possible to produce sounds that are harmonically similar to other instruments. It could be said that pipe organs were the first synthesizers.

Analog synthesizers use a process called *subtractive synthesis* which is simply additive synthesis in reverse. Here's some synth terminonlogy for you: Sounds created by synthesizers are referred to as patches. This goes back to the early days of modular synthesizers when patch cables were used to route signals from module to module to

reate a sound. Patches created using subtractive synthesis start with waveforms that are already rich in harmonics such as sawtooth, square, and triangle waves. These waveforms are then passed to a filter which removes harmonics from the waveforms in order to produce the desired sound. The harmonics are *subtracted* out hence the process is known as subtractive synthesis.

The most common waveforms on analog synthesizers are the sawtooth, square/pulse, and triangle wave. There are three main reasons these are used almost universally rather than other waveforms. First is the fact that they all have lots of harmonics which can be chiseled away by the filter. Secondly they are relatively easy to produce using analog circuits. Thirdly they are each harmonically similar to broad families of acoustic sounds even without any filtering. This almost sounds as if to imply that acoustic imitation is the goal ofsynthesis which it most certainly is not. It is a practical criteria to start with if nothing else. Sawtooth waves are similar to brass and string instruments, square waves are similar to woodwinds, and triangle waves with their diminished higher harmonics are good for mixing together to produce inharmonic sounds (bells, chimes, etc) as well as adding the occasional rogue harmonic to saw and pulse waveforms. This may be surprising but even though these waveforms have similar harmonics and sound similar to certain families of instruments the waveforms of acoustic instruments look nothing like squares/pulses, sawtooths, or triangles. A waveform's usefulness lies with the harmonics that make it up and is NOT inherent to the shape ofthe waveform. Two sounds can have very similar harmonics yet have waveforms that look nothing alike. Adding waveforms together in an attempt to match the waveshape of an acoustic instrument won't produce desirable results most ofthe time.

While some synthesizers only have one oscillator and a few others have many, the majority have two oscillators that can be independently set to different waveforms. Twooscillator configurations are so common because they are cheaper to produce than multioscillator synths yet they are much more capable of producing rich sounds than singleoscillator instruments. They are a good balance of economy and ability. By using two oscillators it is possible to not only create more interesting strings, brass, and woodwinds but it also becomes possible to create vocals, inharmonic sounds such as bells, and countless other acoustic and synthetic sounds. One simple fact is that a single oscillator will have harmonics where each successive partial has less amplitude. While the higher harmonics of acoustic instruments do diminish in amplitude they do not follow this progression so rigidly. Below are harmonic diagrams ofsome acoustic instruments.

![](_page_7_Figure_1.jpeg)

**Figure 9. Violin harmonics**

![](_page_7_Figure_3.jpeg)

**Figure 10. Flute harmonics**

![](_page_7_Figure_5.jpeg)

**Figure 11. Trumpet harmonics**

The noise at the bottom ofthe graphs is from resonance, reverberation, and recording noise,

Notice that while the higher harmonics do die away they do not do so in a uniform fashion like synthetic waveforms. These slight harmonic deviations help separate one acoustic instrument from another in the same family and give what could be considered a "natural" sound. Again, imitation is a possibility ofsynthesis but is not necessarily the goal, however lessons learned from studying and recreating acoustic sounds can help to produce more interesting synthetic patches that have character and life. By detuning oscillators it is possible to come up with much more interesting sounds. To produce the harmonics of a marimba for example take a triangle wave and add a second triangle wave at slightly lower amplitude and tuned up two octaves.

![](_page_8_Figure_3.jpeg)

Figure 12. Using two oscillators to synthesize an instrument such as the marimba allows for a more complex harmonic structure than using single waveforms alone.

By simply mixing two humble triangle waves with different tunings a more harmonically sophisticated sound has been produced than could be done with just a single waveform. The harmonics of a single triangle may die out uniformly but the harmonics oftwo detuned triangles do not. While this sound is literally the sum oftwo triangle waves, to the ear it sounds far richer than the sum of its parts. The important point here is that using two oscillators gives more control over the harmonic make up ofthe final sound. As we shall see there are many other tools at our disposal that will allow us to further fine tune harmonic structure.

![](_page_9_Figure_1.jpeg)

Figure 13. Pulse widths. Narrowing the pulse width creates a brighter, edgier sound similar to a sawtooth.

As a pulse becomes narrower it goes from a square wave with only odd partials to having both even and odd partials and therefore sounding more like a sawtooth wave. Look at the figures above and you'll notice that even though narrow pulses have harmonic spectra that are similar to a sawtooth there are still some important differences. The harmonics do not die out as quickly or with the same uniformity as those of a sawtooth. Narrow pulses have more of a crisp, metallic sound. By narrowing the pulse width it is also possible to give the harmonic s an "undulating" pattern similar to the harmonic behavior of many acoustic instruments. The advantage of a pulse with variable width is that it allows a higher degree of control over the harmonics than using just waveform mixing and filtering alone. Another cool thing about variable-width pulses is that the width can usually be modulated to produce thick string-like patches. More about that in the section on LFOs. Some synths don't provide the ability to change the width ofthe pulse, but these instruments often provide a few pulses that are hardwired to different widths. This is common on ROMpler, sample-based instruments and even a few analog synths.

#### *Syncing*

Another common feature with most dual-oscillator analog synths is the ability to sync one oscillator to the other. This is useful for producing, amongst other things,plucked and hammered strings such as pianos and guitars. Syncing forces the wavecycle of one oscillator to restart when the wavecycle ofthe other oscillator restarts. The oscillator that is being synced is called the slave while the oscillator it is synced to is called the master. Usually, but not always, a synthesizer's second oscillator is the slave while oscillator one is the master. You may want to check your synth's manual to be sure since it's often not clear on the front panel. For syncing to have any effect on the sound the synced oscillator must be tuned *highe r* than the master oscilltator.

When the slave oscillator is tuned higher than the master oscillator its waveform will restart each time the waveform ofthe master restarts. The resulting waveform produced by the slave using a sawtooth would look similar to that shown at the bottom ofthe following figure. When synced, the tuning of the master also controls the *actual* tuning ofthe slave while any changes that are made using the slave's tuning/pitch control will instead change the tonal qualities ofthe oscillator.

![](_page_11_Figure_1.jpeg)

Figure 14. When a slave oscillator is synced its waveform will restart every time the master oscillator . restarts.

Here's an example that you may want to try for yourself. Start by setting the slave oscillator to produce a sawtooth waveform. The waveform used by the master doesn 't matter. Only its pitch matters since it controls the wave cycle time. Tum the volume of the master oscillator all the way down but make sure it is turned on. We want the master to be available for syncing the slave but we don't want to hear the master's output. Set both oscillators to the same pitch. If you now tum syncing on and off you will notice that the output ofthe slave sounds the same either way. This is because the master is making the slave's waveform restart at the same location that it would even ifthe two weren 't synced since the pitch settings are identical.

Next tum syncing on and slowly increase the pitch ofthe slave without going as high as one octave above the pitch set by the master. As it increases the output ofthe slave will take on a thin, brittle timbre , however the overall pitch stays the same.

Tum the slave's pitch control up to the point where it corresponds to exactly one octave higher than the pitch setting ofthe master. Ifwe now tum syncing offwe will hear no change. The brittle timbre is gone and you are now hearing a plain sawtooth only it is an octave higher in pitch. Even though the slave is indeed tuned higher than the master it's pitch is now exactly double that ofthe master and therefore the master is causing the slave to once again restart at a point where it would restart even if it weren 't synced. A further increase ofthe slave's pitch will continue to produce metallic, harmonically-rich sound until the slave is pitched two octaves above the master, and so on. To summarize : The slave must be tuned higher but ifit is tuned at octave intervals syncing will have no effect. Look at the figures below. As the slave's pitch setting is increased the harmonics change, but when the slave's pitch is set to one octave above the master the output simply becomes that of a plain sawtooth (or square) tuned one octave higher in pitch.

![](_page_12_Figure_1.jpeg)

Figure 15. Harmonics of synced sawtooth and square waveforms are much more complex than unsynced waveforms. Detuning the slave from the master by octave intervals negates the syncing effect since the slave is forced to restart at a location where it would restart even if it weren't synced.

#### *Noise*

Subtractive synthesizers generally have two types ofsound sources. One ofthese sources are the oscillators while another is noise. On some models the noise source is actually provided by one ofthe oscillators while on others it is provided seperately. Noise is useful for creating many percussion sounds, creating sound effects such as ocean waves and wind, and driving filter resonance. The most common form is white noise which maintains uniform power across all frequencies. Television static is white noise.

![](_page_13_Figure_3.jpeg)

Figure 16. White noise

There is pink noise which diminishes in power by 3 dB per octave.

![](_page_13_Figure_6.jpeg)

Figure 17. Pink noise

There is also brown noise which diminishes in power by 6 dB per octave. Put simply, white noise sounds brighter than pink noise, and pink noise sounds brighterthan brown.

![](_page_14_Figure_1.jpeg)

Figure 18. Brown noise

\'hat distinguishes noise from a typical waveform is that it has no harmonic partials and 'he sound is spread solidly across the audio spectrum. True noise has no pitch. When noise is used to create percussive patches such as snare drums or cymbals it may use filter resonance or sometimes a triangle wave will be mixed in to impart a sense of pitch.

\\-ith a regular oscillator waveform pitch, pulse width, and syncing can all be controlled to manipulate the sound before it reaches the filter. Noise has none ofthese controls and therefore is highly dependent upon the filter for sculpting. Noise when used along with the filter, and the filter's resonance and envelope is far more useful than it may at first seem.

#### *Keyboard Tracking*<sup>0</sup>

Oscillator keyboard tracking, sometimes called keyboard pitch tracking, allows the user to select whether or not the pitch of an oscillator will change as different keys are played. Turning this off will cause the same pitch to be sounded by every key. This can be particularly useful when creating bagpipes, sitars, and other drone instruments. Bagpipes and sitars are similar in the respect that they both playa set of notes of varying pitch over top a drone of unchanging pitch. Use one oscillator with tracking turned on to play the notes of varying pitch and use a second oscillator with tracking turned offto imitate the drone. The pitch control sets the single pitch that is played on all keys. It is quite common for an untracked oscillator pitch to correspond with the same pitch that would be played by either the C4 or A4 keys iftracking were turned on.

Keyboard tracking is sometimes offered as a control on other parameters as well in addition to pitch. After pitch tracking, the most common is filter cutoff keyboard tracking. This can be used to either gradually increase or decrease the amount of filtering that takes place as keys are played either up or down the keyboard. For example, ifthe high notes in a patch sound too bright keyboard tracking can be used to give them more filtering while letting the lower notes pass through unfiltered. Keyboard tracking is also occasionally used to modify envelope times and amounts. It can be used to give higher notes faster envelope times which can be useful for creating piano patches where high notes decay faster than lower ones.

### *Polyphony*

Polyphony refers to the numbe r of keys that can be played and still produce sound. For example. a synthesizer with five-note polyphon y will produce sound for a maximum of five notes at a time. What would happen if more than five keys were played? This depends on the synthesizer. Some synths will "steal" notes that have been held the longest in order to play newer notes while other synths may steal the lowest-pitched, or highest-pitched notes. Many synths allow the user to choose the method of note stealing that they prefer.

Synthesizers that only allow one note to be played at a time are called *monophonic* while synthesizers that allow multiple notes are *polyphonic.* Most early synthesizers were strictly monophonic. Monophonic playing isn't always a limitation. In fact most modern .synths give the user the option to choose between monophonic and polyphonic playing. Monophonic playing can be particularly useful for some leads and bass patches. It helps to keep a single patch from over-dominating a mix and sounds particularly interesting when used in conjunction with portamento.

### *Portamento*

Portamento, also known as glide, will cause the pitch to change gradually between two consecutively struck keys. This is controlled by a time parameter which determines how long it takes for the pitch to change. There is often a setting that will determine whether glide is only present when the keys are played overlapping (legato) or glide is automatic whether the keys overlap or not.

#### *Unison*

Unison is used to create a chorusing-like effect. Historically this has been achieved by using all of a polyphonic synth 's oscillators to play the same note and would effectively make the instrument monophonic when in unison mode . The fact that true analog oscillators cannot keep *exactly* the same tuning becomes an asset here . Because all ofthe oscillators are slightly detuned from each other over the range of a few cents the sound is very thick. The sound is also somewhat similar to that produced by pulse-width modulation. The graph below shows a sawtooth wave being played in unison. The higher harmonics are broadened similar to the way they would be in pulse-width modulation. Unison unlike PWM, as we will discuss later, doesn 't flatten out the harmonic levels and it also adds some low-amplitude, inharmonic content. Notice how the harmonics are broadened similar to those ofthe violin graph at the top of page 6. Unison is often used to create bowed-string sounds.

![](_page_16_Figure_1.jpeg)

Figure 19. Unison broadens the harmonics of a waveform creating a choruslike effect.

Unison is also particularly good for use with filtered pads as well as beastly, bonecrunching leads. If your synth allows you to set the amount of unison try decreasing it to keep it from becoming too overbearing. Except of course when you want it to sound beastly!

#### *Ring Modulation*

though the synthesizer provided with this book and the included patches do not use ring modulation it is nonetheless common enough that it deserves some explanation. Ring modulation works by multiplying two signals together which produces an output that consists of frequencies that are the sum and difference of all the original harmonic frequencies. For example take two harmonics which each belong to separate signal inputs on a ring modulator. If one has a frequency of 50 hz and the other has a frequency of 150 hz then the signal put out by the ring modulator will have harmonics at 100 hz and 200 hz. This particular example illustrates the process but it may not seem to be particularly useful since we are just taking two harmonics and producing two *different* harmonics. The important point to consider is that in practical usage *evelY* harmonic in one signal gets multiplied with *every* harmonic in the other. Ifthe two signals have tunings where man y oftheir harmonics coincide then the end result will be a harmonic sound with rich overtones.

If the oscillators are set to inharmonic intervals the ring modulator will produce a rich inhann onic sound that is harsh and metallic and is quite similar to inharmoni c sounds produced with FM (frequency modulation). Ring modulation was used quite a bit in old sci-fi flicks and earl y avant garde electronic music. As a point of interest, the Dalek voices on Dr. Who were originally created with a ring modulator by multiplying a 30 Hz sine wave with mid-range boosted speach input.

#### *Filter Types*

The incorporation of filters was the fist great revolution in early electronic music after the oscillator. There are only a few distinct sounds that can be created using unfiltered waveforms. Synthesizers were born with the introduction ofthe filter. Of all the components on a synthesizer it is the most responsible for shaping the sound. Filters are used to change the timbre or tone color ofthese basic waveforms.

The most common type is the low-pass filter. A low-pass filter works by removing or attenuating high frequencie s and passing low frequencies. A signal that has been subjected to low-pass filtering will not sound as bright. This type offilter is the most common because our ears are accustomed to hearing sounds with attenuated high frequencies. As sound travels through air it not only loses amplitude overall but the higher frequencies also diminish more than the low frequencies . Bass frequencies travel further than high frequencies. Higher frequencies also experience more absorption by instrument bodies and obstructions. Figure 21 shows white noise that has been passed through a low-pass filter.

![](_page_17_Figure_5.jpeg)

Figure 20. Unfiltered white noise

![](_page_17_Figure_7.jpeg)

Figure 21. White noise routed through a low-pass filter. Higher frequencies have been attenuated while lower frequencies pass through.

Another common filter type is the high-pass filter. This filter as the name impli es works by attenuating low frequencies and passing the high ones. Some natural sounds have diminished or outright lack lower-pitched harmonics. Isn't this impossible given that the pitch of a note is determined by the frequency ofits lowest harmonic the fundamental? Remember that the frequencies of overtones are related to the frequenc y ofthe fundamental. Ifthe fundamental and some ofthe lower overtones are missing our brains are able to relate the frequencies ofthe existing higher overtones back to the missing fundamental and percei ve the correct pitch. This type of filter can be useful for recreating cymbals, handclaps and other instruments that sometimes lack lower frequencies.

![](_page_18_Figure_2.jpeg)

Figure 22. White noise routed through a high-pass filter. Lower frequencies are attenuated while higher frequencies pass through.

Two other filter types that are related to one another are the band-pass and band-reject filter. A bandpass filter attenuates both high and low frequencies and only lets a narrow *band* offrequencies through.

![](_page_18_Figure_5.jpeg)

Figure 23. A band-pass filter only allows frequencies within a narrow band to pass.

A band-reject filter, or notch filter, is essentially the inverse ofthe bandpass filter. It lets high and low frequencies pass and attenuates frequencies within a narrow band.

![](_page_19_Figure_1.jpeg)

Figure 24. A band reject filter removes frequencies within a narrow band but allows all others to pass.

#### *CutoffFrequency*

The cutofffrequency sets the frequency point where filtering begins to take place. If for example a low-pass filter has its cutofffrequency set to 6 khz then the output will pass all frequencies below 6 khz and all higher frequencies will be diminished. In actuality some filtering actually takes place at frequencies before the cutofffrequency. To be a bit more strict with our definition the cutofffrequency is usually taken to be the point at which the frequencies have been attenuated by -3 db, but this can be slightly different from one instrument to another.

![](_page_19_Figure_5.jpeg)

Figure 25. Here cutoff frequency has been set to 6 kHz (6000 Hz). Notice that frequencies less than 6 kHz are also filtered but to a lesser extent than those above 6 kHz

#### *Filter Slope*

A common misconception with filters is that *all* frequencies beyond the cutofffrequency are removed from the signal. The filtering beyond the cutofffrequency actually takes place gradually. The rate or degree offiltering that takes place beyond the cutoff frequency is determined by the slope ofthe filter. The most common types are 12 db

and 24 db per octave slopes and occasionally 6 db, 36 db and other values are used. A larger decibel value means more attenuation. A 12 db low-pass filter will sound slightly brighter than a 24 db low-pass when set to the same cutofffrequency. What these values mean is that for every octave the frequencies will be attenuated by the given decibel amount. For example let's say we have a 24 db low-pass filter and the cutoff frequency is set to some fairly low value like 1.5 kHz. Let's compare the filtering at 4 kHz and 8 kHz since these values are both in the filtered region . Frequencies at 8 kHz will be 24 db "quieter" than those at 4 kHz since these frequencies are one octave apart.

![](_page_20_Figure_2.jpeg)

Figure 26. Filter response of a 24 dB per octave low-pass filter. Material at 8 kHz is attenuated 24 dB more than material at 4 kHz since these frequencies are one octave apart

Filters are also referred to by their number of "poles." One pole equals 6 dB offiltering. A two-pole filter is the same thing as a 12 db filter. A four-pole filter is the same thing as a 24 db filter.

![](_page_20_Figure_5.jpeg)

Figure 27. Filter slope of a 2-pole, 12 dB per octave filter

![](_page_21_Figure_1.jpeg)

Figure 28. Filter slope of a 4-pole, 24 dB per octave filter

Some synthesizers allow the user to select various filter types; No type is inherently better than another and the most preferable type depends upon the application.

#### *Resonance*

The function ofthe resonance setting on a filter depends upon the filter type. Its purpose is completely different in low and high pass filters than it is in band-pass and band-reject filters. When used with either a low-pass or a high-pass filter, resonance amplifies those frequencies closest to the cutofffrequency. When used with band-pass and band-reject filters the resonance setting acts as a *"Q "* control and sets the width ofthe band.

![](_page_21_Figure_6.jpeg)

Figure 29. Filter resonance at a 4 kHz cutoff frequency

It should be made clear that resonance on a synthesizer is not the equivalent ofresonance of an acoustic instrument nor is it *necessarily* used to replicate the resonance of an acoustic instrument. In situations where a particular frequency or set of nearby frequencies need to be amplified resonance becomes a useful tool.

Most synthesizers 'have gain compensation which will automatically lower the overall output ofthe signal as resonance is increased. This helps to prevent the resonant spike from going through the roof but it comes at the expense oflowering the rest ofthe signal.

![](_page_22_Figure_1.jpeg)

Figure 30. Increasing the resonance results in gain compensation automatically lowering the amplitude of surrounding frequencies

Some filters are self-resonating meaning that when the resonance is turned up high the filter will resonate even if no signal is input into the filter. This effectively turns the filter into a sine-wave oscillator. If keyboard tracking is available on the filter then this sine wave can be played as if it were a waveform from one ofthe oscillators. In cases where a synth does not have a self-resonating filter it is stilI possible to "play" the filter's resonance with keyboard tracking by feeding a noise source into the filter and using this to drive the filter's resonance.

Another way to playa resonant filter directly is through a method employed in acid electronica. The acid genre got its name not as a drug reference but rather from what are known as acid lines or acid tracks. Acid lines in tum got the name due to the way they sound. The acid line is one ofthose great stories in electronic music where a technology, in this case the resonant filter, is used in a fashion not originally intended. More specifically it was born out ofthe Roland TB,·303 in the mid 80s. The "303" was originally marketed as a bass accompaniment for guitarists. It is essentially a sequencer that plays a single oscillator and was never intended to be played in a realtime or improvisational sense. The unexpected thing that happened was that electronic artists learned to use the TB-303 as a realtime instrument by turning up the resonance and alternating the filter cutofffrequency manually in realtime thus changing the pitch ofthe resonance while the unit's onboard sequencer cycled thorough note patterns.

Here's an example ofhow to create a very basic acid line without having to sell vital organs to buy a TEe-303. Program a sequencer to loop through a rhythm that consists of only one note. Most acid tracks don't use just one note but we'll do it here just to better illustrate the process. The synth's oscillators can be set to any waveform but I'd suggest using a sawtooth. Tum the resonance up to about 3/4 of its full position. Now as the sequencer plays the synth alternate the filter cutofffrequency by hand. This will cause the pitch ofthe resonance to change. You may have to confme the extent over which you twiddle the cutofffrequency to the lower part of its range as higher frequencies may be inaudible. Twiddle the cutofffrequency knob in time to the rhythm and there you have an acid line albeit a simple one.

#### ENVELOPES

Envelopes are used to control how various parameters change over time once a key is played. Envelopes can be used to control just about any parameter, but the most obvious use of an envelope is to control the way a patch 's amplitude changes. If we want a patch to start loud and die out slowly like a cymbal or start out quiet and slowly become louder like a violin an envelope could be used to control the amplitude.

The most common type is the ADSR envelope which breaks the time over which a key is struck and held into four distinct periods called stages. ADSRs are hence known as fourstage envelopes. "A" stands for *attack* and it controls the rate ofthe envelope's initial increase. "D" is for *decay* and it controls the rate at which the envelope decreases after the attack. "S" is for *sustain* and this controls the level at which the envelope will remain until the key is released. "R" is for release and it controls the amount oftime that it takes for the envelope to die out after the key is released. Attack, decay, and release all control lengths oftime and settings are commonly given in seconds and milliseconds. Sustain on the other hand sets the level after decay has completed and has no set time associated with it. It begins as the decay ends and will last indefinitely until the key is released. It's sometimes given as a percentage where 100% would be the maximum setting.

![](_page_23_Figure_4.jpeg)

Figure 31. Representation of an ADSR envelope. ADSR envelopes can be applied to many different parameters but are most commonly used to control amplitude and filter cutoff frequency.

The following graph shows the effect that an ADSR envelope can have on amplitude.

![](_page_23_Figure_7.jpeg)

Figure 32. The results of an ADSR envelope controlling amplitude as viewed in the sound editor Audacity

# ENVELOPES

Incidentally, if sustain is set at IOO% then decay really serves no purpose as it will not "decay" down. There are also variations on the ADSR configuration. The original MiniMoog used an ADS envelope where the "Decay" setting also doubled as a release setting. The ARP Odyssey and ARP 2600 had AR envelopes as well as the conventional ADSR type. There are also envelope types that use more than four stages but the ADSR is the most common.

Another use for envelopes is to control the filter's cutofffrequency. If you listen closely to woodwinds or brass instruments you may notice that as the player begins to blow into the instrument that not only does the amplitude increase but the sound also becomes brighter. As pressure builds in the instrument higher frequencies are added to the sound. These higher frequencies are also the first to die out when the player stops blowing. This behavior can be replicated by controlling the filter's cutofffrequency with an envelope.

Here 's a piece of advice to give a patch more character and realism. Use the filter's envelope to create changes in the amplitude and *then* use the amplitude envelope to make any remaining adjustments. Huh? You may be asking why and how the filter envelope can be used to control amplitude. Isn't that what the amplitude envelope is for? Well, it's simple really. Whenever frequencies are removed from a signal they no longer contribute to the overall power ofthe signal. Removing frequencies will result in an overall lower amplitude. A filtered signal isn't as loud as an unfiltered signal. Because ofthis a filter envelope has the effect of behaving somewhat like an amplitude envelope. This approach can be restated as the following. First use the filter envelope to control the amplitude ofthe higher harmonics and after that use the amplitude envelope to control the amplitude ofthe remaining lower harmonics that were untouched by the filter.

The filter envelope has an *amount* setting that is used to determine how much the envelope influences the cutofffrequency. Sometimes it can be a bit tricky deciding whether to adjust the cutofffrequency or the envelope amount. In these situations the best suggestion is to experiment by adjusting both.

To compare the amplitude and filter envelopes try the following. Set the oscillators to produce any waveform that you like. With the filter completely open (i.e. no filtering) raise the attack amount up on the amplitude envelope. You should hear the sound slowly get louder as you hold down a key. Now tum the amplitude attack back down and this time lower the filter cutofffrequency, increase the filter envelope amount, and increase the filter envelope attack time. As you hold down a key notice that the sound gets louder just as before but this time the timbre or tonal quality ofthe sound also changes.

### LFOs

LFO stands for *low-frequency oscillator.* Unlike a synth's main oscillators an LFO is not heard at the output or at least not directly. It is a modulation source meaning that it is used to create changes in other parameters. LFOs are used to create cyclic fluctuations in pitch, amplitude and a variety of other parameters. To add vibrato or tremolo to a patch an LFO would be used to modulate the pitch and amplitude respectively. Another key difference is that the main oscillators produce waveforms with frequencie s in the audible range of 20 Hz - 20 kHz while LFO frequencies are typically less than 20 Hz. If an LFO could be connected directly to the output it would be inaudible because of its low frequency.

LFOs are similar to the main oscillators in that they do use square, triangle, and sawtooth waves and they also commonly use sine waves and sample & hold patterns. These are all referred to as source waveforms. Sine and triangle waves are the most ideal for imitating natural effects such as vibrato and tremolo . The results they produce, when used with an LFO at least, are very similar and for this reason it is not uncommon that a synth provides one and not the other.

LFOs have a frequency or rate setting that changes the speed ofthe cycle. Vibrato, tremolo typically use LFO frequencies under 5 Hz. Higher frequencies can be useful for many synthetic sounds and rhythm effects. The degree to which the LFO modulates a given parameter is controlled by an *amount* setting. Amount settings may either be found in the LFO section itself and sometimes they are located in each section to which they control.

Let's look at what happens when an LFO uses a sine wave to modulate the amplitude of a patch. Here is a waveform of a patch without any LFO modulation.

![](_page_25_Figure_6.jpeg)

Figure 33. A patch without any LFO modulation

Following is the same patch played with the amplitude modulated by the LFO set to use a sine wave at 4.5 Hz. This creates vibrato.

![](_page_26_Figure_1.jpeg)

Figure 34. Patch with LFO modulation using a sine wave source set to a frequency of 4.5 Hz

In the next graph the LFO has the same frequency but uses a triangle wave.

![](_page_26_Figure_4.jpeg)

Figure 35. Patch with LFO modulation using a triangle wave source set to a frequency of 4.5 Hz

The sine wave source and the triangle source produce very dissimilar graphs but if you set your synth up to modulate amplitude and compare the use of a sine versus a triangle you will hear very little difference. When setting up the frequency of an LFO remember that 1 Hz = 1 cycle per second. In the above example the frequency was set to 4.5 Hz thus producing 4.5 cycles each second as can be seen by looking at the graphs.

#### *Pulse-width modulation*

One ofthe coolest uses ofthe LFO is to create pulse-width modulation. Recall that changing the width of a pulse changes its harmonic content. Routing an LFO, using a sine or triangle source, to modulate the pulse width creates an extremely rich sound that could best be described as a thick, string section-like sound.

Below is a graph showing the harmon ics of a pulse-width modulated waveform. Notice that the higher harmonics are broadened . This is very similar to the effect heard by chorusing or unison. Keep in mind though that pulse-width modulation tends to even out the levels ofthe harmonics. For instance a pulse that is set to a width of25% will have harmonics that appear to undulate in amplitude. If a heavy dose of modulation is applied to the pulse width this undulation will disappear and the harmonic amplitudes will take on characteristics similar to that of a sawtooth that has some chorusing or unison.

![](_page_27_Figure_2.jpeg)

Figure 36. Pulse-width modulation causes the upper harmonics to broaden resulting is a chorusing effect. This is very useful for string and pad sounds

The trick to getting good PWM string sounds is to use pulse-width modulation on both oscillators and detune one about 10 cents high and the other about 10 cents low. Set the LFO frequency a bit under 5 Hz and the amount to a bit under 50% which will make it thick while minimizing the beating effect that is characteristic ofPWM. Then apply some light chorus and delay if available.

#### *Beat effects (gating and note switching)*

Because oftheir cyclic nature, LFOs can also be used to create rhythm. This is where the square and sawtooth sources become the most useful. Using either one ofthese sources and routing the LFO to modulate the amplitude or filter cutofffrequency can result in useful gating effects. Using a square wave source will cause the output to have a repeating On/Off pulsing pattern. A sawtooth source will cause the sound to cycle through a "ramp up" or "ramp down" depending on the direction ofthe sawtooth. These effects are particularly useful when the LFO frequency is matched to the beat ofthe song. A common attribute ofLFOs on many modem synthesizers is the ability to sync to a time signature provided either internally or by an external sequencer.

By routing a square wave source LFO to modulate pitch it is possible to create note switching, trill sounds. The key here is to set the LFO depth to something that will produce a musically useful interval such as a fifth (7 semitone difference ) or an octave (12 semitone difference). This can be a useful way to create a simple two-note arpeggio/trill effect that can be useful particularly if your synth lacks an arpeggiator.

### 27 KEYBOARD EXPRESSION

#### *Sample* & *hold*

Without getting into a deep explanation sample & hold is a random pattern that is often available as an LFO source. It's great for creating the computer-type sounds from old sci-fi movies. Set the LFO source up to be sample & hold (or noise) and route it to modulate the oscillator pitch. This should produce a cheesy computer sound. Also try routing the LFO to the filter cutofffrequen cy and tum the filter resonance up.' This produces a different but equally as cheesy computer sound!

#### *Syn c sweep ing*

Here 's a great way to use an LFO to create a screaming, growling lead. Set the slave oscillator to sync to the master oscillator. Keep the master oscillatorturned on but keep its volume all the way down. Tune the slave oscillator higher than the master's pitch. Set the LFO to use a sine or triangle at a really, really low frequenc y « 1 Hz) and use this to modulate the slave's pitch. Apply portamento(glide) and lay on some unison and chorusing. Experiment with different LFO frequencie s and depths. As you increase the LFO amount decrease the LFO frequency.

#### **Keyboard Expression**

#### *Velocity Sensitivity*

If a piano ' s keys are struck hard it will obviously sound much louder than ifthey are struck lightly. Not only that but the timbre of the sound will be much different as well. A hard-struck piano doesn 't simply sound like a louder version of a lightly-struck piano. Both the amplitude *and* harmonic character of the sound depend on how hard the keys are played . This type of behavior can be replicated on synthesizers that have velocity sensitive keyboards. A velocity sensitive keyboard can be used to modify parameter amounts based on how fast the keys are pressed. The two most common uses for velocity sensitivity are to change the amplitude level and the filter-cutoff frequenc y, but it is also sometimes used to modify pitch, envelope times, LFO rates and amounts, and just about anything else. Velocity sensitive keyboards allow for much greater expression and realism. These days most keyboards have velocity sensitivity but not all do particularly inexpensive ones and even pro models produced before the mid 80s. Be sure to check before buying that next synth.

#### *Aftertouch (pressure sensitivity)*

A keyboard with aftertouch or pressure sensitivity allows the user to control parameter amounts based on how much pressure is applied to the keys as they are being held down. This can be quite useful when used with the filter to imitate wind instruments being overblown or routed to pitch for replicating string bending on a violin. Like velocity sensitivity it to can be applied to a wide range of parameters. Aftertouch keyboards come

### 28 KEYBOARD EXPRESSION

in two different flavors. The cheapest to implement and therefore the most common is channel or global aftertouch. A keyboard with channel aftertouch averages the pressure from all the depressed keys to create a single aftertouch message. Polyphonic aftertouch which is much more rare allows each key to transmit its own aftertouch message. While it has become more common, most keyboards do *not* have aftertouch so if this is something that interests you be sure to look for it.

## SYNTHESIS THROUGH HARMONIC ANALYSIS

#### **Synthesis Through Harmonic Analysis and Reverse Engineering**

The use of harmonic analysis in synthesis is nothing new, yet it has not been used much outside of academic research and professional patch programming. There are a few reasons for this. The first is that harmonic analysis requires a fair amount of processing power that until recently was too expensive for most of us. Fortunately home computers are now powerful enough to perform the analysis in real-time while using only a small percentage ofthe computer's processor. The second reason is that it is generally perceived as difficult to use. There is quite a bit ofmathematical theory that goes into computing the Fast-Fourier Transforms (FFT) on which harmonic analysis is based but as far as using harmonic analysis as a tool for synthesis it's rather straightforward. The third reason, somewhat as a result ofthe first two, is that it simply hasn't become part of convention.

This is super powerful stuff and it has the potential to change the way you program sound. Even though this section is centered on analyzing harmonics and reverse engineering musical content it should be noted that it will also improve your ability to create original patches as well. After you use it for a while and you come to understand the spectral makeup of different sounds you will rely less and less on having to look at harmonic diagrams. They'll be in your head. This book is about analog synth programming but it should be mentioned that harmonic analysis also makes FM synth programming infinitely easier to understand. Don't even bother programming FM without it! I digress ...

Before proceeding I recommend that you first get a hold ofsoftware that can perform harmonic analysis/FFT in realtime and play around with it for a bit. Most ofthe more sophisticated sound editors provide the ability to display harmonic diagrams ofsound files albeit usually not in real-time. For real-time analysis I highly recommend the Fre(a)koscope VST plug-in. This plugin was used to create all ofthe harmonic diagrams in this book. It has an excellent interface, is easy to use, and it's free! If you don't have a host that supports VST plugins be sure to visit kvraudio.com where you can find a number of hosts available for free. If you have any questions please email me at synthcookbook@yahoo.com

The analysis/synthesis process can be broken down into three stages for each sound.

- 1. The most important step. Obtain a harmonic diagram ofthe sound that is to be emulated or recreated. Pick the best oscillator waveforms, pitches, and amplitudes to match the diagram.
- 2. High frequency harmonics are generally the last to rise in amplitude and are the first to die back out. While comparing with the harmonic diagram ofthe original source use the synth's filter envelope to match this behavior.
- 3. Using a sound editor, match the synth's envelopes to the original source .

Step one is essential while steps 2 and 3 are not always possible or required. Envelopes may not require any visual analysis since they can be duplicated by ear with good results more easily than harmonics. Note: The lowest-pitched harmonics are the most important. As a general rule ofthumb try to get the first 5-10 harmonics as close to their corresponding levels in the original source.

#### Reverse engineering a patch from another synth:

The easiest sounds to recreate are those from other analog synths. Because analogs have very similar feature sets it makes for easier translation. About ten years ago I had to sell a Sequential Circuits Six-Trak but I made sure to record samples of some of my favorite patches that I'd programmed for it. My favorite was a lead with thick unison and we'll begin by reverse engineering this patch. The sample of this patch can be found on the CD.

Playing the sample through Fre(a)koscope produces the following harmonic diagram,

![](_page_31_Figure_4.jpeg)

Figure 37. Harmonics of a patch originally programmed on a Sequential Circuits Six-Trak

Here Fre(a)koscope has been set to a linear display and a maximum window size with a frequency range of 20 Hz - 20 kHz. The lower harmonics are the most important so let's decrease the maximum frequency of the display so that we can see these in greater detail. Lower the maximum range down to about 6 kHz.

![](_page_31_Figure_7.jpeg)

Figure 38. Six-Trak patch zoomed in to show finer detail in the lower-frequency harmonics. The pitch of the sampled note is at C3 on the keyboard

In Fre(a)koscope it is possible to get decibel value, frequency, and equivalent key number by clicking on a section of the graph. In the graph above the fundamental has been selected and from the inset box at the upper right we see that the sample is tuned to the C3 key. We need to know this so that we know what key to play on the synth that is

### REVERSE ENGINEERING A PATCH

being programmed. There are many important details in the above graph that give us a clue as to where we should start. Notice that both even and odd harmonics are present. This rules out using a single triangle wave or square wave since they have only odd harmonics.

The two remaining options are sawtooths and pulses since they possess both even and odd harmonics. Also notice that the higher harmonics become broad and are not the narrow spikes that we would expect with pure sawtooths or pulses. This indicates that there could be some pulse-width modulation taking place or the oscillators have been set to unison. We will get back to the broad harmonics in a bit but for now look at the way the harmonic amplitudes do not decrease evenly from left to right. A sawtooth that has been synced can produce harmonics that look like this but so can a pulse with variable width. Let's take a look at the synced sawtooth option first. Set your synth up with the slave oscillator synced to the master oscillator and have the slave produce a sawtooth wave while at the same time the master's output is turned all the way down. Increase the pitch ofthe slave while keeping an eye on the synth's harmonic analysis. The closest that we can get to the original harmonics this way is when the slave oscillator is tuned about 8 semitones above the master.

![](_page_32_Figure_4.jpeg)

Figure 39. A synced sawtooth oscillator tuned 8 semitones above the master produces results similar to the original patch but not close enough

What are the notable differences between this graph and that ofthe original Six-Trak sample? Of course the harmonics are all narrow and again we will get to that in a moment but for now we only need to compare their amplitudes to the original patch. The higher harmonics in our patch are slightly louder than those in the original. Notice that they are higher on the graph. This can be remedied by applying some low-pass filtering but there is a bigger discrepancy than this. Notice that the harmonics of our patch do not undulate up and down in quite the same fashion as the original patch . It would however be a good guess that if we find out what is broadening the higher harmonics ofthe original patch and we apply it to our patch as it is right now that the two would nonetheless sound very similar but we are going to try to do better. Remember this was originally produced by another synthesizer so we should be able to get really close and we can probably even nail it.

#### REVERSE ENGINEERING A PATCH

Let's see what we can come up with using a pulse instead of a sawtooth. Again only use one oscillator but this time do not sync it to the other. Set it up to produce a pulse. Begin by setting the pulse width to produce a square wave. Remember that a square wave should only show odd harmonics. Now very slowly begin decreasing the pulse width. Before the width has been decreased much at all you should get harmonics that are identical in amplitude to those of the original patch. This happens to be at a pulse width of about 44%, something not much narrower than a square wave but harmonically different. Now we haven't yet applied any filtering so the harmonics will not diminish quite as rapidly as those in the original patch but the levels of each harmonic relative to their neighbors follows the same pattern as those in the original.

![](_page_33_Figure_3.jpeg)

Figure 40. A pulse width of 44% produces harmonics that are very similar to the original patch

Next experiment with some low-pass filtering until the level of the higher harmonics matches those of the original. A 24 dB filter set to a cutoff frequency of 2.5 kHz produces the following graph.

![](_page_33_Figure_6.jpeg)

Figure 41. Apply some low-pass filtering to match the harmonic amplitudes to those in the Six-Trak patch

There are some differences between this and the original but the amplitudes are pretty darn close. While two synths can produce *practically* the same results they cannot produce *exactly* the same results.

The one last thing that we need to take care of is determining what is causing the higher harmonics to broaden. This could either be due to pulse-width modulation or oscillator

### 33 REVERSE ENGINEERING A PATCH

unison. Try applying some pulse-width modulation. As the pulse-width modulation amount is increased it produces the following results.

![](_page_34_Figure_3.jpeg)

Figure 42. Pulse-width modulation broadens the higher harmonics but it also flattens out the harmonic amplitudes

This has broadened the higher harmonics as we had hoped but it has also managed to decrease the amount of undulation in the harmonics. Pulse-width modulation obviously wasn't used in the original patch.

Get rid ofthe pulse-width modulation and this time turn on unison. The Six-Trak had six oscillators so set your unison mode to six oscillators if applicable. If you're using the SCB synth turn unison mix and intensity all the way up and put speed at about 50%. You should get harmonics similar to those below.

![](_page_34_Figure_7.jpeg)

Figure 43. The harmonics ofthe resynthesized patch in its final form

![](_page_34_Figure_9.jpeg)

Figure 44. The harmonics of the original patch

## REVERSE E1 GINEERING A SOUND IN A SONG

Listen to the resynthesized patch and compare it to the original sample . They are practically indistinguishable. This also sounds far better than trying to stretch a 4 second sample across the whole keyboard using a sampler! Ifwe wanted to do something like decrease the amount of filtering we can do that with the resynthesized patch but would not be able to using the audio sample.

#### *Reverse engineering a soundfrom a song:*

The tricky part to reverse engineering a sound that's in a song is the presence of other interfering material. Here the goal is to find a clip ofthe sound that is as isolated as possible from other competing sounds in the mix.

For an example ofreverse engineering a sound from a song we 'll lift one off of Shape I from the Shape album which can be found on the CD. There's a cool bass that starts at about 2:45 into the song. Use a waveform editor to take a look at the region from 2:45 to 2:50. An audio clip ofthis section can also be found on the CD. For waveform editing, I use Audacity which is an excellent freeware sound editor.

![](_page_35_Figure_6.jpeg)

Figure 45. Audio clip containing the bass sound that is to be duplicated as well as a bass drum and even the tail end of a pad. The bass sound must be isolated from a section of this recording

In this section there are three different sounds. There is the bass sound that we would like to isolate for resynthesis, a bass drum, and at the beginning ofthe section there is the tail end ofthe pad-type sound from earlier in the song. The bass and the bass drum both play ten times in the clip shown above. The bass is the quieter ofthe two. Because ofthe interference ofthe pad at the beginning ofthe clip we will isolate one ofthe bass voicings found after 2:47. Let's take the one from region 2:47.79 to 2:48.04 . Yes that's right, we are going to recreate the patch from a mere 1,4 second ofsound!

## REVERSE ENGINEERING A SOUND IN A SONG

![](_page_36_Figure_2.jpeg)

Figure 46. Audio clip of the bass sound isolated from the region 2:47.79 - 2:48:04

Running this clip through a harmonic analyzer set to a linear view produces the following harmonic diagram. The range has been set to show the lowest harmonics.

![](_page_36_Figure_5.jpeg)

Figure 47. Harmonics of the isolated bass sound. The high noise floor is the left overs of other sounds and effects in the mix

Notice that the noise floor isn't very far below the tops ofthe harmonics. This is most likely the left over garbage from other sounds and effects in the mix. Look at the far left ofthe diagram and at what appears to be the first harmonic. The dark nub just below the -20 dB line. This too is most likely an artifact since its frequency doesn 't relate to any of the other harmonics. Ifthis were a sample of an acoustic instrument this statement might not be true but the one thing we know about this sample is that it came from another synthesizer which most likely used standard waveforms having harmonics at evenlyspaced frequency intervals.

As in the previous example we need to determine the pitch ofthe sample so that we know what key to play on the keyboard. In the case of Fre(a)koscope the cursor indicates that it is pitched to the A2 key. There are some similarities between this diagram and the one of the original Six-Trak patch back in the preceeding example. Like before, the broadening ofthe harmonics at high frequency indicates the presence of oscillator unison so we will want to tum that on. Here we also have undulating harmonics but unlike the previous example there is more of a pattern to the way they go up and down in amplitude. Notice that from about 1000 Hz to just above 2000 Hz that every other harmonic is lower than its neighbor. Also in the earlier example some harmonics were drastically diminished while others were only slightly. Here the change in amplitude is more uniform. These are

## REVERS E ENGINEERING A SOUND IN A SONG

tell-tale signs that we are looking at a sawtooth wave mixed with either a second sawtooth or a square wave and not oscillator syncing or pulse-width modulation. The reason that one ofthese must be a sawtooth is that if we use just square waves or triangle waves, which have only odd harmonics, no matter how they are detuned from one another there will always be some missing harmonics. In the graph above there are *no* missing harmonics. Try playing with just square and triangle waves and detuning one of the oscillators to move its harmonics around. You'll find that no matter how the tuning is changed there are always missing harmonics.

We must now determine what waveform is used by the second oscillator as well as its pitch . Look at the harmonics of a single sawtooth tuned to A2 with unison and compare it to the harmonics ofthe sample.

![](_page_37_Figure_4.jpeg)

Figure 48. Sawtooth wave tuned to A2 with unison

We need to increase the amplitude ofthe even harmonics while leaving the odd harmonics unchanged. A square wave won 't work because it is made of *only* odd harmonics. Ifwe add a square wave to the sawtooth we get undulating harmonics but they are in the wrong order and the sound doesn't have the same bite as the original. Here is a graph ofthat.

![](_page_37_Figure_7.jpeg)

Figure 49. A square wave added with a sawtooth produces undulating harmonics but they are in the wrong order

#### 37 REVERSE ENGINEER! G A SOUND IN A SONG

If we tune the square up an octave its even worse. Now every fourth harmonic is increased starting at harmonic two.

![](_page_38_Figure_2.jpeg)

Figure 50. Ifthe square wave is tuned up an octave the results match even less than before

The square wave doesn 't work so we' ll have to try using a second sawtooth. This second sawtooth must be tuned up one octave. Why? Everytime a sound is tuned up an octave not only does the frequency ofthe fundamental double but more importantl y for this particular situation the frequency distance ofthe overtone harmonics also doubles. Here are the harmonics of a sawtooth pitched to A3

![](_page_38_Figure_5.jpeg)

Figure 51. Harmonics of a sawtooth tuned up an octave to A3. Notice that the distance between harmonics has doubled

Notice that the harmonics are twice as far apart as those in the A2 sawtooth diagram. If we add the A2 sawtooth and the A3 sawtooth we will get the correct undulating harmonics.

## 38 REVERSE ENGINEERING A SOUND IN A SONG

![](_page_39_Figure_1.jpeg)

Figure 52. Two sawtooth waves tuned an octave apart are used to create the final product

Compare this to the original.

![](_page_39_Figure_4.jpeg)

Figure 53. Harmonics of the original sample.

The majority ofthe harmonics are within 5 dB ofthe positions in the original and the undulating pattern is the same. There are slight differences but again these are to be expected since no two synthesizers are *exactly* the same. Set the attack and release times ofthe amplitude envelope to zero for a good bass patch. Compare the sound ofthe original to our new patch and notice they are very similar.

## EMULATING AN ACO USTIC INSTRUMENT

### *Emulating an acoustic instrument's harmonics and envelope: Clarinet*

In this example we will not only imitate the harmonics ofthe instrument but we will also use the filter envelope to recreate the original envelope. Here we will recreate the sound ofthe clarinet taken from a sample provided by the royalty-free online sample library of the University ofIowa Electronic Music Studios

(http://theremin.music.uiowa.edu/MIS.html). This sample can also be found on the CD.

Recreating the harmonics of acoustic instruments is more subjective than recreating patches produced by other analog synths. When recreating a synth patch we are basically trying to determine the settings ofthe synth from which it originally came and the end result is usually quite similar to the original. In the case of acoustic instruments however there are usually multiple ways to achieve harmonics that are similar to the original but with slight differences between the various methods. One method may do an excellent job ofrecreating the very lowest harmonics while another does a good job with higher harmonics. Recreating this clarinet as you will see is no exception.

Acoustic harmonic spectra are usually more complicated than those of analog synths. The goal is to match the synth's output as close as possible to the acoustic instrument while expecting to make sacrifices in one area ofthe audio spectrum to improve quality in other areas. The harmonics with the lowest frequencies are the most important. Take a look at the spectra of the clarinet.

![](_page_40_Figure_7.jpeg)

Figure 54. Harmonics of a clarinet

Here are the major details ofthe graph: The fundamental has a frequency corresponding to C4, harmonics 1, 3, and 5 are dramaticall y louder than the rest, and there are not really any harmonics after 8 kHz. Even though there are both even and odd harmonics such as would be provided by a sawtooth, the first three odd harmonics (1, 3, and 5) stand above the rest. This sound can probably be duplicated by mixing a sawtooth with either a square or triangle since either ofthese have odd harmonics. Because none ofthe odd harmonics above harmonic 5 really seem to stand out would suggest that we try a triangle over a square since the triangle 's harmonics are quieter at higher frequencie s. Here's what you' ll get if you mix a triangle wave at full amplitude with a sawtooth wave -25 dB quieter than the triangle. Both at the same pitch.

#### EMULATING AN ACOUSTIC INSTRUMENT

![](_page_41_Figure_2.jpeg)

Figure 55. A triangle wave mixed with a quieter sawtooth wave produces harmonics that are similar

It sounds close and the harmonics look somewhat similar. There are probably clarinets out there that are nearly identical to this, but if we want to match this *particular* clarinet I think we can do better.

The way the first six harmonics undulate could be duplicated with a single pulse so let's give that a try. Starting with a pulse width of 50% (square wave) and barely decreasing the width much at all (only down to 49%) we get the following harmonic diagram.

![](_page_41_Figure_6.jpeg)

Figure 56. Pulse width set to 49%

There is in fact hardly any difference between this and a square wave. A pulse width of 49% versus a width of 50% may have dissimilar looking harmonic signatures yet they sound practically identical. Sound wise this is really close and we're probably splitting hairs to get closer but it is possible. We'll use the pulse width to help produce the first three loud odd harmonics but now we have to figure out how to produce the rest. If we ignore the first three odd harmonics then harmonics 6 and 7 would be the loudest and all harmonics to the left and to the right of these would fall away getting quieter in both directions. How do we imitate this odd and peculiar behavior? Often the best way to make harmonics do odd and peculiar things in a patch is to use a synced oscillator. Here's what we will do. Turn oscillator sync on and set the slave oscillator to use a square wave. Make sure the master oscillator is on but that its volume is turned all the way down at least to start with. We don't want to hear the master but we do want the slave to be able to sync to it. Now, while looking at the harmonic output of the slave's

#### EMULATING AN ACOUSTIC INSTRUMENT

square wave begin increasing the slave oscillator's pitch up quite high and as you do you should notice that successively higher pitched harmonics become the loudest on the display. Keep increasing the slave's pitch setting until it is 2 octaves and 5 semitones above the master and you should get harmonics similar to the following graph.

![](_page_42_Figure_3.jpeg)

Figure 57. Output from a synced sawtooth tuned 2 octaves and 5 semitones above the master

With the exception of harmonics 1, 3, and 5 this matches the original spectra closely. Now to finish out the sound set the master oscillator to produce a pulse with a width of 49% just like we did a few paragraphs back. Turn the volume of the master all the way up and turn the slave down to where it is rather quiet around -30 dB below the master and what you get should be similar to the following graph.

![](_page_42_Figure_6.jpeg)

Figure 58. The master oscillator mixed with the slave oscillator

This is very close to what we want but the higher harmonics are still a bit loud so apply some low-pass filtering. A 24 dB filter set to a cutoff frequency of 2.5 kHz was used to produce the following result.

![](_page_43_Figure_1.jpeg)

Figure 59. Applying some low-pass filtering to the mixed waveforms creates results that are very similar to the acoustic clarinet

Compare this to the original clarinet.

![](_page_43_Figure_4.jpeg)

Figure 60. Harmonics of the clarinet

Since the first 5-10 harmonics are the most important we can consider our synthetic clarinet to be very similar to the acoustic clarinet. Not bad for old-school analog/subtractive synthesis! Call it good on the harmonics. Now lets move on to the envelopes.

Here is the amplitude envelope of the clarinet in the audio sample.

![](_page_43_Figure_8.jpeg)

Figure 61. Envelope of the clarinet

## EMULATING AN ACOUSTIC INSTRUMENT

We are going to duplicate this using the synthesizer' s filter envelope. Usually when a synth programmer looks at a waveform like the one above the first inclination is to duplicate it using the synth' s amplitude envelope. The above waveform is no doubt the natural amplitude envelope ofthe clarinet, however a more accurate reproduction ofthis envelope will actuall y use the synth's filter envelope. Keep in mind that whereas the amplitude envelope changes the amplitude of *all* harmonics equally the filter envelope changes the amplitude of *select* harmonics. In the case of a low-pass filter, the filter envelope changes the amplitude ofthe higher frequencies more dramati cally. Therefore, the filter envelope is after a fashion a form of amplitude envelope.

Listen to the very beginning ofthe clarinet sample on the CD where the player just begins to blow into the instrument. The most obvious thing that you'll notice is that the amplitude ofthe note increases. Listen a bit more closely and you should also be able to notice that within that first fraction of a second the instrument sound become s not only louder but also brighter. As the player begins to breath low-pitched harmonics amplify first followed by successively higher-pitched harmonics. As more and more high harmonics are added the overall sound become s brighter and louder. At the end ofthe sample when the player stops blowing, the high harmonics are also the first to die out. This is true to varying extents injust about all instruments. Woodwinds in particular have a very strong relation between overall amplitude and amplitude changes of individual high harmoni cs.

Zooming into the beginning ofthe sample we see that the clarinet has an attack of about 0.15 seconds in length.

![](_page_44_Figure_5.jpeg)

Figure 62. The attack portion of the clarinet sample

Zooming into the end we see that the "release" portion takes roughly 0.2 seconds

![](_page_45_Figure_2.jpeg)

Figure 63. The release portion of the clarinet sample

In the synthesizer set the filter's cutofffrequency to its lowest setting, tum the filter envelope amount up to its maximum setting. Set the filter envelope 's attack to 0.15 s, release to 0.2 s, and sustain all the way up to 100%. The decay time doesn't matter since sustain is at 100%. To keep the amplitude envelope from interfering make sure its attack is set to 0, sustain 100%, and release set to maximum. Now playa note on the keyboard. There 's now a gradual attack and release but the sound is way too bright. While holding down a key, reduce the filter envelope's amount setting until the output sounds more like it did before we started messing with the envelope. To be a real stickler for accuracy look at your harmoni c display while reducing the envelope amount until the higherfrequency harmonic s are back where they were originally. Try playing it now and it should sound quite good.

Let's now add a faint hint ofvibrato. Look closely at the original waveform in Figure 61 and notice how there are shallow peaks and valleys. They are hardly pronounced enough to be considered true vibrato. Excuse the jargon but they're more like quasi-periodic fluctuations caused by variations in the player's breath with a period of about 0.05 seconds. Remember frequency is equal to one over the period so: 1/0.05 s = 20 Hz. So set the LFO to around 20 Hz and route it to the amplitude. Set the LFOs modulation amount to where it just barely creates a vibratoeffect. .Around 2% is good ifn ot less.

![](_page_45_Figure_6.jpeg)

Figure 64. LFO used to create vibrato

Compare this with the original.

![](_page_46_Figure_2.jpeg)

Figure 65. Notice how closely the attack and release in fig. 64 match with the original. The LFO was used to mimic the slight amplitude fluctuation in the original clarinet sample

The attack and release are very similar and we were able to use the LFO to somewhat duplicate the amplitude fluctuations. It sound's quite similar and we probably aren't going to get much closer than this. This not only sounds like a clarinet, but it sounds like the *specific* clarinet from the audio sample. Harmonic analysis allows us to get exceedingly close to the original source material. Analyze the harmonics of your own voice and synthesize it. Trust me, it's kind of creepy!

Ok, so the amplitude envelope wasn't used. Why are synthesizers built with amplitude envelopes then? Like I said before, woodwinds like the clarinet have envelopes that are very dependent upon the amplitude changes oftheir higher harmonics. When synthesizing most acoustic instruments both envelopes are usually used. Most instruments do not have such an extreme change in timbre at the attack and release as woodwinds like the clarinet and therefore the amplitude envelope can be given more control on these patches. An amplitude envelope can also be used to change the contour ofthe overall envelope. Look at the attack of our clarinet patch for example. '-" 'J' 5 0.11 ' .15 '3t' ' ..35 0."

![](_page_46_Figure_6.jpeg)

Figure 66. Attack portion of the clarinet patch

#### EMULATING AN ACOUSTIC INSTRUMENT

If we instead set both the filter *and* amplitude attacks to 0.15 seconds the overall attack will take the same amount of time but will come up more abruptly at the end of the attack.

![](_page_47_Figure_3.jpeg)

Figure 67. Setting both the filter and amplitude attack times to 0.15 seconds changes the contour of the attack

The filter attack and amplitude attack have been used together to change the contour of the overall attack. Though we don't need to use this approach on the clarinet, it can be very useful for contouring the releases of percussion and plucked and hammered strings.

#### **Oscillators**

Wave: Waveform choices include sawtooth, square, triangle, and pulse width (PW). Pulse width values are given as a percentage ofthe waveform period. For instance a pulse width of 50% is a square wave and a pulse width of 25% is a pulse with a width that is halfthat of a square and sounds more "brassy." Pulse widths greater than 50% are not included as they are just inverted versions of those between 0% and 50% and therefore sound the same. You will need to know if your synth's pulse-width setting goes from 0%-50% or, more commonl y, 0%- 100%. If you have a synthesizer such as the ImpOscar which uses values of 50%- 100% simply subtract the pulse width values in the book from 100 to get the value you need to use. Ifthe synthesizer lacks the ability to set the pulse width ofthe square wave then substitute pulse-width values 0%-30% with a sawtooth wave and values from 30% - 50% with a square wave. Ifthe synthesizer lacks a triangle wave then use a square wave in it's place when called for along with slightly more low-pa ss filtering. Triangle and square waves sound similar because they are both composed of odd harmonics but the higher harmonics ofthe triangle are less audible.

Tune: Values are listed in octaves, semitones, and cents. This is the value by which one oscillator should be detuned from the other oscillator. For patches where both oscillators have a tunin g value listed it is the amount by which each oscillator is to be detuned from a common pitch. Ifthe tracking for oscillator 2 is turned offthis field will list the specific pitch for which oscillator 2 is to be tuned.

Mix: This is the amplitude ofthe oscillator. Values are given in decibels where the maximum amplitude is 0 dB and quieter amplitudes are given as negative values. Some synthesizers display amplitudes wherethe maximum amplitude is not 0 dB. It may for instance be some positive value . In these cases just subtract the value listed in this book from the maximum value displayed by the synthesizer. For example ifthe synthesizer displays a maximum value of 13 dB

for the volume of one ofthe oscillators and the setting called for in this book is - 7 dB then the oscillator should be set to a value of 6 dB. It's not that big of a deal just as long as you make sure the oscillators are separated by the same amount. The percentage to the right ofthe decibel value is the percentage ofthe maximum setting ofthe oscillator amplitude. This can be used for synthesizers that do not display values in decibels. Since oscillators on different synths have amplitude adjusters with different responses this percentage is a ballpark approximation and may require some adjustment by ear. For more accuracy it is best to calibrate the synths mix settings as explained in the last section ofthis book.

Oscillator 2 tracking: This is either on or off. When on the pitch of oscillator 2 will track the keyboard. When off oscillator 2 will play the same pitch on all keys.

Oscillator 2 sync: When on it syncs oscillator 2 to oscillator 1. You may need to check your synthesizer's documentation to be sure which ofits oscillators syncs to the other when syncing is turned on.

#### **Noise**

Noise: White noise source set to either on or off.

Mix: Amplitude ofthe noise source given in decibels. The statements made above in the section on oscillator mix apply here as well.

#### **LFO**

Routing: Sets the destination ofthe LFO. Destinations include amplitude, pitch, filter cutoff, and pulse width.

Wave: Waveform used by the LFO as a modulation source. Waves used are sine, triangle, and square.

Frequency, Sets the rate ofthe LFO. Values are given in Hertz (Hz). Qualitative suggestions are given in italics.

Depth: Sets the amount by which the destination is modulated by the LFO. This is given as a percent ofthe settings range when modulating amplitude, filter cutoff, and pulse width. The knob/slider that controls depth would be turned half way for a depth of 50%. When pitch is set as the destination the depth is given in terms ofthe amount of pitch that a played note will vary.

Glide: Also known as portamento. Set to either on or off

Time: Glide time. The amount oftime that it takes for the pitch to change from one struck note to the next.

Unison: Set to on or off. Your synthesizer may allow you to control the number of oscillators that are used. Usually 4 to 6 oscillators sound good.

Voices: The polyphony ofthe patch. Either set to a specific number, mono, or multi. Multi means there is no restriction on the amount of polyphony.

#### **Low-Pass Filter**

Cutoff: Values are given for 24 dB filters and 12 dB filters. Values are given in hertz and kilohertz and go from 20 Hz to 20KHz. If your synthesizer uses something other than a 24 dB or 12 dB filter you can figure out the required setting by extrapolating from the given values for 24 and 12 dB filters. Generally, the smaller the amount of attenuation (the decibel number) the lower the cutoff frequency should be. With a greater amount of attenuation set the cutoffto a higher frequency. For example, ifthe listing for a 12 dB filter calls for a cutoff of 200 Hz then a 6 dB filter would be set to a frequency less than 200 Hz. A 36 dB filter would be set to a cutoff frequency higher than what is listed for the 24 dB filter value, etc.

To the right of each cutoff frequency is listed the percentage ofthe full dial

position. Of course each synthesizer's filter cutoff will follow a different response curve so this value is provided as a rough estimate. It is based on the average taken from ten different synthesizers. Actual values can vary drastical1y. *Following these percentages will require at least some adjustment* by *ear.* If you patch a sound and it doesn 't sound right then most likely it is due to a discrepancy between the filter-cutoff setting percentages and the actual filter cutoff ofthe synth. As a simple test I would recommend patching the Angels patch on pg 33. If it sounds more like a brass instrument than a vocal then the listed percentages are higher than what your synth produces. Set the cutofffor each patch below the listed percentage value. Ifthe angels sound like they are being smothered then the listed percentages are too low. Set the cutofffor each patch above the listed percentage value. To achieve higher accurac y on synthesizers that do not display cutoffin hertz it is recommended to follow the calibration instructions at the end ofthe book. This calibration procedure for the filter while not critical is HIGHLY reconunended! If you only calibrate one parameter it should be the filter cutoff.

Resonance: The amount ofresonance applied to the filter. Values are given as a percentage where 0% applies no resonance and 100% applies the maximum amount.

Envelope: Sets the amount by which the filter envelope controls the amount of filtering. On some synths this is called the Initial Level setting. Again 0% is the minimum value and 100% is the maximum.

ADSR: Attack, Decay, and Release are given in terms oftime with values in seconds. Sustain is given as a percentage of its maximum amount.

#### **Amplifier**

ADSR: The same as the envelope for the filter. Attack, Decay, and Release are given in terms oftime with values in seconds. Sustain is given as a percentage of its maximum amount.

#### **Alternate Patch** Settings

Some ofthe patches in the book have alternate patch settings which are intended to be used ifthe synth does not have the feature listed in the primary patch. For instance let's say that you are programming the cello patch which calls for oscillator I to use a pulse with a width of 10% but your synth doesn 't have the ability to produce a pulse. Use the alternate setting which calls for a sawtooth wave instead.

*Note about times: Some synthesizers list times in seconds (s) and others list times in milliseconds (ms). This book uses seconds but the conversion is straightforward. Simply move the decimal three places. The relation is:*

*1 s* <sup>=</sup> *1000 ms*

*0.1 s= 100 ms*

*O. 01 s* = 1*Oms*

*0.001 s* = 1 *ms*

*So for example 0.08 s is the same thing as 80 ms, 0.28 s is also 280 ms, and* 1.35 *s is 1350 ms, etc.*

# **STRINGS**

**Banjo**

| cillator 1  |            | LFO         |              | Low-pass filter |            |            |       |
|-------------|------------|-------------|--------------|-----------------|------------|------------|-------|
| Wave:       | PW=<br>20% | Routing:    | Ampl itude   |                 | 24db       | 12db       |       |
| Tune:       | -          | Wave :      | Triang le    | Cutoff:         | 2.9khz 72% | 1.5khz 63% |       |
|             |            | Frequency : | 10hz<br>fast | Resonance:      | 0%         |            |       |
| Mix:        | Odb 100%   | Depth:      | 10%          | Envelope:       | 75%        |            |       |
| cillator 2  |            | Glide:      | -            | A               | D          | S          | R     |
| Wave:       | PW=<br>10% | time:       | -            | Os              | 0.19s      | 0%         | 0.19s |
| Tune:       | +5 semi    | Unison:     | off          | Amplifier       |            |            |       |
|             |            | Voices :    | 5            | A               | D          | S          | R     |
| Mix:        | -7.6db 80% |             |              | Os              | 0.67s      | 0%         | 0.67s |
| 2 Track:    | on         |             |              |                 |            |            |       |
| Osc 2 Sync: | on         |             |              |                 |            |            |       |
| Noise:      | off        |             |              |                 |            |            |       |
| Mix:        | -          |             |              |                 |            |            |       |

| cillator 1 |            | LFO         |              | Low-pass filter |            |            |       |
|------------|------------|-------------|--------------|-----------------|------------|------------|-------|
| Wave:      | PW=<br>20% | Routing:    | Ampl itude   |                 | 24db       | 12db       |       |
| Tune:      | -          | Wave :      | Triang le    | Cutoff:         | 2.9khz 72% | 1.5khz 63% |       |
|            |            | Frequency : | 10hz<br>fast | Resonance:      | 0%         |            |       |
| Mix:       | Odb 100%   | Depth:      | 10%          | Envelope:       | 75%        |            |       |
| cillator 2 |            | Glide:      | -            | A               | D          | S          | R     |
| Wave:      | PW=<br>10% | time:       | -            | Os              | 0.19s      | 0%         | 0.19s |
| Tune:      | +5 semi    | Unison:     | off          | Amplifier       |            |            |       |
|            |            | Voices :    | 5            | A               | D          | S          | R     |
| Mix:       | -7.6db 80% |             |              | Os              | 0.67s      | 0%         | 0.67s |

## **Cello**

Noise: off Mix: -

| Oscillator 1 |            | LFO        |                | Low-pass filter |          |          |       |
|--------------|------------|------------|----------------|-----------------|----------|----------|-------|
| Wave:        | PW=<br>10% | Routing:   | Amp litude     |                 | 24db     | 12db     |       |
| Tune:        | -          | Wave :     | Sine           | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |            | Frequency: | 7.5hz moderate | Resonance:      | 0%       |          |       |
| Mix:         | Odb 100%   | Depth:     | 5%             | Envelop e:      | 90%      |          |       |
| illator 2    |            | Glide:     | off            | A               | D        | S        | R     |
| Wave:        | Square     | time:      | -              | Os              | 3.29s    | 78%      | max   |
| Tune:        | -          | Unison:    | off            | Amplifier       |          |          |       |
|              |            | Voices:    | multi          | A               | D        | S        | R     |
| Mix:         | Odb 100% ' |            |                | 0.06s           | max      | 100%     | 0.30s |
| 2 Track :    | on         |            |                |                 |          |          |       |
|              |            |            |                |                 |          |          |       |

Osc 2 Sync: off Alternate: Osc 1: sawtooth

## **Double Bass**

| Oscillator 1 |           | LFO        |                | Low-pass filter |            |           |       |
|--------------|-----------|------------|----------------|-----------------|------------|-----------|-------|
| Wave:        | PW=45%    | Routing:   | Pitch          |                 | 24db       | 12db      |       |
| Tune:        | -1 octave | Wave:      | Triangle       | Cutoff:         | 1.6khz 63% | 750hz 52% |       |
|              |           | Frequency: | 5hz moderate   | Resonance:      | 0%         |           |       |
| Mix:         | Odb 100%  | Depth :    | 11 cents light | Envelope:       | 0%         |           |       |
| Oscillator 2 |           | Glide:     | Off            | A               | D          | S         | R     |
| Wave:        | Square    | time:      | -              | -               | -          | -         | -     |
| Tune:        | -         | Unison:    | Off            | Amplifier       |            |           |       |
|              |           | Voices:    | Multi          | A               | D          | S         | R     |
| Mix:         | -17db 60% |            |                | 0.35s           | max        | 100%      | 0.19s |
| Osc 2 Track: | on        |            |                |                 |            |           |       |
| Osc 2 Sync:  | off       |            |                |                 |            |           |       |
| Noise:       | off       |            |                |                 |            |           |       |
| Mix:         | -         |            |                |                 |            |           |       |

## **Dulcimer**

| Oscillator 1 |            | LFO        |                 | Low-pass filter |           |           |       |
|--------------|------------|------------|-----------------|-----------------|-----------|-----------|-------|
| Wave:        | PW=25%     | Routing:   | Amplitude       |                 | 24db      | 12db      |       |
| Tune:        | -7 semi    | Wave:      | Triangle        | Cutoff:         | 600hz 49% | 200hz 33% |       |
|              |            | Frequency: | 1.5hz very slow | Resonance:      | 0%        |           |       |
| Mix:         | -7.6db 80% | Depth:     | 22%             | Envelope:       | 50%       |           |       |
| Oscillator 2 |            | Glide:     | off             | A               | D         | 5         | R     |
| Wave:        | PW=5%      | time:      | -               | Os              | 1.69s     | 0%        | 1.78s |
| Tune:        | -          | Unison:    | off             | Amplifier       |           |           |       |
|              |            | Voices:    | multi           | A               | D         | 5         | R     |
| Mix:         | Odb 100%   |            |                 | Os              | 4.00s     | 0%        | 4.00s |
| Osc 2 Track: | on         |            |                 |                 |           |           |       |
| Osc 2 Sync:  | off        |            |                 |                 |           |           |       |
| Noise:       | off        |            |                 |                 |           |           |       |
| Mix:         | -          |            |                 |                 |           |           |       |

## **Guitar Acoustic**

| Oscillator 1 |          | LFO        |       | Low-pass filter |             |             |       |
|--------------|----------|------------|-------|-----------------|-------------|-------------|-------|
| Wave:        | PW =25%  | Routing:   | -     |                 | <u>24db</u> | <u>12db</u> |       |
| Tune:        | -        | Wave:      | -     | Cutoff:         | 3.1khz 73%  | 2.0khz 67%  |       |
|              |          | Frequency: | -     | Resonance:      | 0%          |             |       |
| Mix:         | 0db 100% | Depth:     | -     | Envelope:       | 70%         |             |       |
| Oscillator 2 |          | Glide:     | off   | Α               | D           | S           | R     |
| Wave:        | PW=10%   | time:      | - "   | 0s              | 0.35s       | 0%          | 0.29s |
| Tune:        | +10 semi | Unison:    | off   | Amplifier       |             |             |       |
|              |          | Voices:    | multi | Α               | D           | s           | R     |
| Mix:         | -4db 90% | *          |       | 0s              | 1.70s       | 0%          | 1.70s |
| Osc 2 Track: | on       |            |       |                 |             |             |       |
| Osc 2 Sync:  | on       |            |       |                 |             |             |       |
| Noise:       | off      | ]          |       |                 |             |             |       |
| Mix:         | -        |            |       |                 |             |             |       |

## **Guitar Electric**

| Oscillator 1 |             | LFO        |       | Low-pass filte | r          |             |       |
|--------------|-------------|------------|-------|----------------|------------|-------------|-------|
| Wave:        | PW =20%     | Routing:   | -     |                | 24db       | <u>12db</u> |       |
| Tune:        | -           | Wave:      | -     | Cutoff:        | 20khz 100% | 20khz 100%  |       |
|              | v.          | Frequency: | -     | Resonance:     | 0%         |             |       |
| Mix:         | -13.4db 65% | Depth:     | -     | Envelope:      | 0%         |             |       |
| Oscillator 2 |             | Glide:     | off   | Α              | D          | S           | R     |
| Wave:        | PW=15%      | time:      | -     | 7 4            | -          | -           | -     |
| Tune:        | +10semi     | Unison:    | off   | Amplifier      |            |             |       |
|              |             | Voices:    | multi | Α              | D          | s           | R     |
| Mix:         | 0db 100%    |            |       | 0s             | 1.70s      | 0%          | 1.70s |
| Osc 2 Track: | on          |            |       |                |            |             |       |
| Osc 2 Sync:  | on          |            |       |                |            |             |       |
| Noise:       | off         | }          |       |                |            |             |       |

Harp

| Oscillator 1 |              | LFO            |                     | Low-pass filte    | r              |               |       |
|--------------|--------------|----------------|---------------------|-------------------|----------------|---------------|-------|
| Wave:        | Any waveform | Routing:       | Amplitude           | 1                 | 24db           | <u>12db</u>   |       |
| Tune:        | -            | Wave:          | Triangle            | Cutoff:           | 40hz 10%       | 40hz 10%      |       |
|              | 4            | Frequency:     | 7.5hz moderate      | Resonance:        | 5%             |               |       |
| Mix:         | -40db 0%     | Depth:         | 6%                  | Envelope:         | 60%            |               |       |
| Oscillator 2 |              | Glide:         | off                 | A                 | D              | S             | R     |
| Wave:        | Square       | time:          | -                   | 0s                | 0.37s          | 78%           | 0.94s |
| Tune:        | +6 semi      | Unison:        | off                 | Amplifier         |                |               |       |
|              |              | Voices:        | multi               | A                 | D              | s             | R     |
| Mix:         | 0db 100%     |                | 1                   | 0s                | 1.30s          | 0%            | 3.30s |
| Osc 2 Track: | on           |                |                     |                   |                |               |       |
| Osc 2 Sync:  | on           | Alternate: Osc | c 1: sawtooth, 0 db | 100%, Osc 2: tria | angle, tune to | same pitch as | osc 1 |

sync off

**Hurdy Gurdy** 

Noise: off Mix: -

| Tiuluy C     | Juluy      |            |                  |                |          |             |       |
|--------------|------------|------------|------------------|----------------|----------|-------------|-------|
| Oscillator 1 |            | LFO        |                  | Low-pass filte | r        |             |       |
| Wave:        | PW = 15%   | Routing:   | -                |                | 24db     | <u>12db</u> |       |
| Tune:        | -          | Wave:      | -                | Cutoff:        | 40hz 10% | 40hz 10%    |       |
|              |            | Frequency: | -                | Resonance:     | 0%       |             |       |
| Mix:         | -4.1db 90% | Depth:     | -                | Envelope:      | 100%     |             |       |
| Oscillator 2 |            | Glide:     | on               | A              | D        | S           | R     |
| Wave:        | Square     | time:      | 0.04s very short | 0.04s          | max      | 100%        | 0.23s |
| Tune:        | D3         | Unison:    | off              | Amplifier      |          |             |       |
|              |            | Voices:    | mono             | Α              | D        | S           | R     |
| Mix:         | 0db 100%   |            |                  | 0s             | max      | 100%        | 0.85s |
| Osc 2 Track: | off        | 1          |                  |                |          |             |       |
| Osc 2 Sync:  | off        | 1          |                  |                |          |             |       |
| Noise:       | off        | i .        |                  |                |          |             |       |
| Mix:         | -          | ,          |                  |                |          |             |       |

## 57 STRlNGS

## **ora**

| illator 1       |           | LFO        |               | Low-pass filter |            |            |       |
|-----------------|-----------|------------|---------------|-----------------|------------|------------|-------|
| Wave:           | Triangle  | Routing:   | Pitch         |                 | 24db       | 12db       |       |
| Tune:           | -         | Wave:      | Triangle      | Cutoff:         | 20khz 100% | 20khz 100% |       |
|                 |           | Frequency: | fast<br>8hz   | Resonance:      | 0%         |            |       |
| Mix:            | Odb 100%  | Depth:     | 8 cents liabt | Envelope:       | 0%         |            |       |
| illator 2       |           | Glide:     | off           | A               | 0          | S          | R     |
| Wave:           | Triangle  | time :     | -             | -               | -          | -          | -     |
| Tune:           | +1 octave | Unison:    | off           | Amplifier       |            |            |       |
|                 |           | Voices:    | multi         | A               | 0          | S          | R     |
| Mix:            | Odb 100%  |            |               | Os              | 2.33s      | 0%         | 2.33s |
| :sc<br>2 Track: | on        |            |               |                 |            |            |       |
| J'SC 2 Sync:    | off       |            |               |                 |            |            |       |
| Noise:          | off       |            |               |                 |            |            |       |
| Mix:            | -         |            |               |                 |            |            |       |

## **ute**

| cillator 1      |           | LFO        |                                             | Low-pass filter |                    |            |       |
|-----------------|-----------|------------|---------------------------------------------|-----------------|--------------------|------------|-------|
| Wave:           | Sawtooth  | Routing:   | Pitch                                       |                 | 24db               | 12db       |       |
| Tune:           | +1 octave | Wave:      | Triangle                                    | Cutoff:         | 20khz 100%         | 20khz 100% |       |
|                 |           | Frequency: | 5hz moderate                                | Resonance:      | 0%                 |            |       |
| Mix :           | Odb 100%  | Depth :    | 47 cents medium                             | Envelope:       | 0%                 |            |       |
| cillator 2      |           | Glide:     | off                                         | A               | 0                  | S          | R     |
| Wave:           | Triangle  | time :     | -                                           | -               | -                  | -          | -     |
| Tune:           | -         | Unison:    | off                                         | Amplifier       |                    |            |       |
|                 |           | Voices:    | multi                                       | A               | 0                  | S          | R     |
| Mix:            | -7db 85%  |            |                                             | Os              | 0.665              | 0%         | 0.66s |
| Jsc<br>2 Track: | on        |            |                                             |                 |                    |            |       |
| Osc 2 Sync:     | off       |            |                                             |                 |                    |            |       |
| Noise:          | off       |            |                                             |                 |                    |            |       |
| Mix:            | -         | note:      | The vibrato caused by the LFO should have a |                 | "warbling" quality |            |       |

## **Mandocello**

| Oscillator 1  |          | LFO         |           | Low-pass filter |           |           |       |
|---------------|----------|-------------|-----------|-----------------|-----------|-----------|-------|
| Wave :        | PW=25%   | Routing:    | Amplitude |                 | 24db      | 12db      |       |
| Tune:         | -        | Wave:       | Triangle  | Cutoff:         | 12khz 92% | 12khz 92% |       |
|               |          | Frequency : | 3hz slow  | Resonance:      | 30%       |           |       |
| Mix:          | Odb 100% | Depth:      | 20%       | Envelope:       | 35%       |           |       |
| Oscillator 2  |          | Glide:      | off       | A               | D         | S         | R     |
| Wave:         | PW=15%   | time:       | -         | Os              | 1.78s     | 0%        | Os    |
| Tune :        | +4 cents | Unison :    | off       | Amplifier       |           |           |       |
|               |          | Voices:     | multi     | A               | D         | S         | R     |
| Mix:          | Odb 100% |             |           | Os              | 1.50s     | 0%        | 1.505 |
| Osc 2 Track : | on       |             |           |                 |           |           |       |
| Osc 2 Sync:   | -        |             |           |                 |           |           |       |
| Noise:        | off      |             |           |                 |           |           |       |
| Mix:          | -        |             |           |                 |           |           |       |

## **·Mandolin**

| Oscillator 1 |            | LFO        |            | Low-pass filter |          |          |       |
|--------------|------------|------------|------------|-----------------|----------|----------|-------|
| Wave :       | PW=25%     | Routing:   | Ampl itude |                 | 24db     | 12db     |       |
| Tune :       | -          | Wave:      | Triangle   | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |            | Frequency: | 2hz slow   | Resonance:      | 0%       |          |       |
| Mix:         | Odb 100%   | Depth :    | 9%         | Envelope:       | 100%     |          |       |
| Oscillator 2 |            | Glide:     | off        | A               | D        | S        | R     |
| Wave :       | PW=15%     | time:      | -          | Os              | 2.07s    | 0%       | 2.135 |
| Tune:        | +1 octave  | Unison:    | off        | Amplifier       |          |          |       |
|              |            | Voices:    | multi      | A               | D        | S        | R     |
| Mix:         | -9.6db 75% |            |            | Os              | 0.09s    | 20%      | 2.335 |
| Osc 2 Track: | on         |            |            |                 |          |          |       |
| Osc 2 Sync:  | off        |            |            |                 |          |          |       |
| Noise:       | off        |            |            |                 |          |          |       |
| Mix:         | -          |            |            |                 |          |          |       |

## Riti

| Oscillator 1 |                  | LFO        |                  | Low-pass filte | r          |             |    |
|--------------|------------------|------------|------------------|----------------|------------|-------------|----|
| Wave:        | Square           | Routing:   | Pitch            |                | 24db       | <u>12db</u> |    |
| Tune:        | -                | Wave:      | Triangle         | Cutoff:        | 7.9khz 86% | 6.5khz 84%  |    |
|              |                  | Frequency: | 6hz moderate     | Resonance:     | 100%       |             |    |
| Mix:         | 0db 100%         | Depth:     | 10 cents shallow | Envelope:      | 85%        |             |    |
| Oscillator 2 |                  | Glide:     | on               | Α              | D          | S           | R  |
| Wave:        | PW = 40%         | time:      | 0.02s            | 0s             | 1.19s      | 0%          | 0s |
| Tune:        | -                | Unison:    | off              | Amplifier      |            |             |    |
|              |                  | Voices:    | multi            | Α              | D          | S           | R  |
| Mix:         | 0db <i>100</i> % |            |                  | 0s             | 0.09s      | 0%          | 0s |
| Osc 2 Track: | on               |            |                  |                |            |             |    |
| Osc 2 Sync:  | off              |            |                  |                |            |             |    |
| Noise:       | off ,            |            |                  |                |            |             |    |
| Mix:         | -                |            |                  |                |            |             |    |

# Sitar

Mix:

| Oscillator 1 |          | LFO        |                 | Low-pass filte | r           |             |       |
|--------------|----------|------------|-----------------|----------------|-------------|-------------|-------|
| Wave:        | PW = 10% | Routing:   | Pitch           |                | <u>24db</u> | <u>12db</u> |       |
| Tune:        | -        | Wave:      | Triangle        | Cutoff:        | 20khz 100%  | 20khz 100%  |       |
|              |          | Frequency: | 6.5hz moderate  | Resonance:     | 0%          |             |       |
| Mix:         | 0db 100% | Depth:     | 40 cents medium | Envelope:      | 0%          |             |       |
| Oscillator 2 |          | Glide:     | off             | Α              | D           | S           | R     |
| Wave:        | PW=35%   | time:      | -               | -              | - 1         | -           | -     |
| Tune:        | C3       | Unison:    | off             | Amplifier      |             |             | -     |
|              |          | Voices:    | multi           | Α              | D           | S           | R     |
| Mix:         | 0db 100% |            |                 | 0s             | 0.93s       | 0%          | 0.93s |
| Osc 2 Track: | off      |            |                 |                |             |             |       |
| Osc 2 Sync:  | off      |            |                 |                |             |             |       |
| Noise.       | off      | 1          |                 |                |             |             |       |

**Standup Bass**

| Oscillator<br>1 |           | LFO        |              | Low-pass fi Iter |           |           |       |
|-----------------|-----------|------------|--------------|------------------|-----------|-----------|-------|
| Wave :          | PW=25%    | Routing:   | Amplitude    |                  | 24db      | 12db      |       |
| Tune:           | -1 octave | Wave:      | Triangle     | Cutoff:          | 40 hz 10% | 40 hz 10% |       |
|                 |           | Frequency: | 15hz<br>fast | Resonance:       | 0%        |           |       |
| Mix:            | Odb 100%  | Depth:     | 10%          | Envelope:        | 75%       |           |       |
| Oscillator<br>2 |           | Glide:     | off          | A                | D         | S         | R     |
| Wave :          | Triangle  | time :     | -            | Os               | 2.33s     | 60%       | 2.335 |
| Tune :          | -1 octave | Unison:    | off          | Amplifier        |           |           |       |
|                 |           | Voices:    | multi        | A                | 0         | S         | R     |
| Mix:            | Odb 100%  |            |              | Os               | 1.28s     | 0%        | 1.385 |
| Osc 2 Track:    | on        |            |              |                  |           |           |       |
| Osc 2 Sync:     | off       |            |              |                  |           |           |       |
| Noise:          | off       |            |              |                  |           |           |       |
| Mix:            | -         |            |              |                  |           |           |       |

## **Viola**

Mix: -

| Oscillator<br>1 |             | LFO        |                 | Low-pass filter |            |            |       |
|-----------------|-------------|------------|-----------------|-----------------|------------|------------|-------|
| Wave :          | Sawtooth    | Routing :  | Pitch osc 2     |                 | 24db       | 12db       |       |
| Tune :          | -           | Wave:      | Triangle        | Cutoff:         | 4.9khz 80% | 2.3khz 69% |       |
|                 |             | Frequency: | 4hz<br>moderate | Resonance:      | 0%         |            |       |
| Mix:            | -11.6db 70% | Depth :    | 80 cents        | Envelope:       | 0%         |            |       |
| Oscillator<br>2 |             | Glide:     | off             | A               | 0          | S          | R     |
| Wave :          | PW=25%      | time:      | -               | -               | -          | -          | -     |
| Tune:           | +7 semi     | Unison :   | off             | Amplifier       |            |            |       |
|                 |             | Voices:    | multi           | A               | D          | S          | R     |
| Mix:            | Odb 100%    |            |                 | 0.81s           | max        | 100%       | 0.73s |
| Osc 2 Track:    | on          |            |                 |                 |            |            |       |

Osc 2 Sync: on Alternate: Osc 2: triangle, tune to same pitch as osc 1, sync off, LFO: routing-Noise : off amplitude, frequency 5 hz (moderate), depth 8%, Filter, 24 db and 12 db - 20khz(100o/c

## 61 STRINGS

## **iolin**

| cillator 1   |              | LFO        |                                                                                                 | Low-pass filter |            |            |       |
|--------------|--------------|------------|-------------------------------------------------------------------------------------------------|-----------------|------------|------------|-------|
| Wave:        | Any waveform | Routing:   | Pitch osc 2                                                                                     |                 | 24db       | 12db       |       |
| Tune:        | -            | Wave:      | Triangle                                                                                        | Cutoff:         | 3.2khz 73% | 1.9khz 66% |       |
|              |              | Frequency: | 5hz<br>moderate                                                                                 | Resonance :     | 0%         |            |       |
| Mix:         | -40db 0%     | Depth:     | 88 cents                                                                                        | Envelope :      | 0%         |            |       |
| ci llator 2  |              | Glide:     | off                                                                                             | A               | D          | S          | R     |
| Wave:        | Sawtooth     | time:      | -                                                                                               | -               | -          | -          | -     |
| Tune:        | +6 semi      | Unison:    | off                                                                                             | Amplifier       |            |            |       |
|              |              | Voices :   | multi                                                                                           | A               | D          | S          | R     |
| Mix:         | Odb 100%     |            |                                                                                                 | 0.03s           | max        | 100%       | 0.35s |
| Csc 2 Track: | on           |            | Alternate: Osc 1: PW=25%, Odb (100%), Osc 2: Square, tune same as osc 1,sync off LFO: route     |                 |            |            |       |
| Jose 2 Sync: | on           |            | amplitude, frequency 3.5 hz(slow), depth 10%, Filter: 24db and 12db - 9.8khz(90 %)              |                 |            |            |       |
| Noise:       | off          |            | Note: Use any waveform for osc 1 and make sure it is on and level is all the way down. Osc 2 is |                 |            |            |       |

Mix: - the only sound source but must sync to osc 1

**Bagpipes**

| scillator 1      |           | LFO        |       | Low-pass filter |            |            |       |
|------------------|-----------|------------|-------|-----------------|------------|------------|-------|
| Wave :           | Sawtooth  | Routing:   | -     |                 | 24db       | 12db       |       |
| Tune:            | -         | Wave:      | -     | Cutoff:         | 20khz 100% | 20khz 100% |       |
|                  |           | Frequency: | -     | Resonance:      | 0%         |            |       |
| Mix:             | Odb 100%  | Depth:     | -     | Envelope:       | 0%         |            |       |
| I<br>iIIator 2   |           | Glide:     | on    | A               | 0          | S          | R     |
| Wave:            | Square    | time:      | 0.04s | -               | -          | -          | -     |
| Tune:            | C3        | Unison:    | off   | Amplifier       |            |            |       |
|                  |           | Voices :   | multi | A               | 0          | S          | R     |
| Mix:             | -11db 75% |            |       | 0.02s           | max        | 100%       | 0.85s |
| :sc<br>2 Track : | off       |            |       |                 |            |            |       |
| :sc<br>2 Sync:   | off       |            |       |                 |            |            |       |
| Noise:           | off       |            |       |                 |            |            |       |
| Mix:             | -         |            |       |                 |            |            |       |

## **ass Clarinet**

Mix: -

Noise: off envelope 75%

| illator 1    |          | LFO        |                                                                                   | Low-pass filter |          |          |       |
|--------------|----------|------------|-----------------------------------------------------------------------------------|-----------------|----------|----------|-------|
| Wave:        | Square   | Routing:   | Pitch                                                                             |                 | 24db     | 12db     |       |
| Tune:        | -        | Wave:      | Triangle                                                                          | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |          | Frequency: | 7.5hz<br>moderate                                                                 | Resonance :     | 0%       |          |       |
| Mix:         | Odb 100% | Depth:     | 5 cents very light                                                                | Envelope:       | 65%      |          |       |
| illator 2    |          | Glide:     | off                                                                               | A               | 0        | S        | R     |
| Wave:        | PW=5%    | time:      | -                                                                                 | 0.09s           | max      | 100%     | 0.23s |
| Tune:        | -        | Unison:    | off                                                                               | Amplifier       |          |          |       |
|              |          | Voices:    | multi                                                                             | A               | 0        | S        | R     |
| Mix:         | Odb 100% |            |                                                                                   | Os              | max      | 100%     | 0.23s |
| sc 2 Track : | on       |            |                                                                                   |                 |          |          |       |
| Osc 2 Sync:  | off      |            | Alternate: Osc 1: -3.6db (85%), Osc 2: sawtooth, -1 octave, -14 db (60%), Filter: |                 |          |          |       |
|              |          |            |                                                                                   |                 |          |          |       |

## **Bassoon**

| Oscillator 1  |            | LFO               |                               | Low-pass filter |          |          |       |
|---------------|------------|-------------------|-------------------------------|-----------------|----------|----------|-------|
| Wave:         | PW=<br>10% | Routing:          | Amplitude                     |                 | 24db     | 12db     |       |
| Tune:         | -          | Wave:             | Triangle                      | Cutoff:         | 40hz 10% | 40hz 10% |       |
|               |            | Frequency:        | 7.5hz<br>moderate             | Resonance:      | 0%       |          |       |
| Mix:          | Odb 100%   | Depth:            | 5%                            | Envelope:       | 60%      |          |       |
| Oscillator 2  |            | Glide:            | off                           | A               | D        | S        | R     |
| Wave:         | Square     | time:             | -                             | 0.16s           | 1.13s    | 83%      | 0.285 |
| Tune :        | +1 octave  | Unison:           | off                           | Amplifier       |          |          |       |
|               |            | Voices:           | multi                         | A               | D        | S        | R     |
| Mix:          | Odb 100%   |                   |                               | Os              | max      | 100%     | max   |
| Osc 2 Track : | on         |                   |                               |                 |          |          |       |
| Osc 2 Sync:   | off        | Alternate: Osc 1: | Square, Filter: envelope: 75% |                 |          |          |       |
| Noise:        | off        |                   |                               |                 |          |          |       |

## **Clarinet**

Noise: off Mix: -

| R     |
|-------|
| max   |
|       |
| R     |
| 0.325 |
|       |
|       |
|       |

## **Conch Shell**

| cillator 1    |             | LFO        |             | Low-pass filter |          |           |       |
|---------------|-------------|------------|-------------|-----------------|----------|-----------|-------|
| Wave:         | Triangle    | Routing:   | Amplitude   |                 | 24db     | 12db      |       |
| Tune:         | -           | Wave:      | Triangle    | Cutoff:         | 1khz 56% | 400hz 43% |       |
|               |             | Frequency: | 2hz<br>slow | Resonance:      | 0%       |           |       |
| Mix:          | Odb 100%    | Depth:     | 5%          | Envelope:       | 55%      |           |       |
| cillator 2    |             | Glide:     | on          | A               | D        | S         | R     |
| Wave:         | Sawtooth    | time:      | 0.0125 fast | 0.115           | 0.075    | 80%       | 0.135 |
| Tune:         | -           | Unison:    | off         | Amplifier       |          |           |       |
|               |             | Voices:    | mono        | A               | D        | S         | R     |
| Mix:          | -14.1db 65% |            |             | 0.115           | max      | 100%      | 0.135 |
| J'Sc 2 Track: | on          |            |             |                 |          |           |       |
| J sc 2 Sync:  | off         |            |             |                 |          |           |       |
| Noise:        | off         |            |             |                 |          |           |       |
| Mix:          | -           |            |             |                 |          |           |       |

## **ontrabassoon**

Noise: off Mix: -

| illator 1    |            | LFO        |                | Low-pass filter |          |          |       |
|--------------|------------|------------|----------------|-----------------|----------|----------|-------|
| Wave:        | PW=<br>10% | Routing:   | Amplitude      |                 | 24db     | 12db     |       |
| Tune:        | -1 octave  | Wave:      | Triangle       | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |            | Frequency: | 7.5hz moderate | Resonance:      | 0%       |          |       |
| Mix :        | Odb 100%   | Depth:     | 5%             | Envelope:       | 60%      |          |       |
| illator 2    |            | Glide:     | off            | A               | D        | S        | R     |
| Wave:        | Triangle   | time:      | -              | 0.095           | 1.135    | 83%      | 0.285 |
| Tune:        | +1 octave  | Unison:    | off            | Amplifier       |          |          |       |
|              |            | Voices:    | multi          | A               | D        | S        | R     |
| Mix:         | Odb 100%   |            |                | Os              | max      | 100%     | 0.295 |
| 'SC 2 Track: | on         |            |                |                 |          |          |       |

J'Sc 2 Sync: off Alternate: Osc 1: square, Osc 2: square, Filter: envelope: 75%

**Didgeridoo**

| Oscillator 1 |            | LFO                           |               | Low-pass filter         |            |           |   |
|--------------|------------|-------------------------------|---------------|-------------------------|------------|-----------|---|
| Wave:        | Square     | Routing:                      | Filter cutoff |                         | 24db       | 12db      |   |
| Tune:        | -1 octave  | Wave:                         | Triangle      | Cutoff:                 | 1.5khz 62% | 800hz 53% |   |
|              |            | Frequency :                   | 1hz slow      | Resonance:              | 80%        |           |   |
| Mix:         | Odb 100%   | Depth:                        | 10% shallow   | Envelope:               | 0%         |           |   |
| Oscillator 2 |            | Glide:                        | on            | A                       | 0          | S         | R |
| Wave:        | PW=<br>25% | time:                         | moderate      | -                       | -          | -         | - |
| Tune:        | +9 semi    | Unison:                       | off           | Amplifier               |            |           |   |
|              |            | Voices:                       | mono          | A                       | 0          | S         | R |
| Mix:         | Odb 100%   |                               |               | 0.03s                   | max        | 100%      |   |
| Osc 2 Track: | on         |                               |               |                         |            |           |   |
| Osc 2 Sync:  | on         |                               |               |                         |            |           |   |
| Noise:       | off        |                               |               |                         |            |           |   |
| Mix:         | -          | notes: Play in lower octaves. | Try           | unison using 2-3 voices |            |           |   |

<sup>A</sup> . ) <sup>E</sup>**ngl5**u h H**orn or ng (C** ars

Noise: off Mix: -

| Oscillator 1 |             | LFO         |                                                                       | Low-pass filter |          |          |       |
|--------------|-------------|-------------|-----------------------------------------------------------------------|-----------------|----------|----------|-------|
| Wave:        | PW=<br>15%  | Routing:    | Pitch                                                                 |                 | 24db     | 12db     |       |
| Tune:        | -           | Wave:       | Triangle                                                              | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |             | Frequency : | 7.5hz<br>moderate                                                     | Resonance:      | 0%       |          |       |
| Mix:         | Odb 100%    | Depth:      | 3 cents shallow                                                       | Envelope:       | 60%      |          |       |
| Oscillator 2 |             | Glide:      | -                                                                     | A               | 0        | S        | R     |
| Wave:        | Triangle    | time:       | -                                                                     | 0.07s           | max      | 100%     | max   |
| Tune:        | +1 octaves  | Unison:     | off                                                                   | Amplifier       |          |          |       |
|              |             | Voices :    | multi                                                                 | A               | 0        | S        | R     |
| Mix:         | -28.6db 30% |             |                                                                       | Os              | max      | 100%     | 0.375 |
| Osc 2 Track: | on          |             |                                                                       |                 |          |          |       |
| Osc 2 Sync:  | off         |             | Alternate: Osc 1: triangle, Osc 2: +2 octaves, Filter: envelope : 95% |                 |          |          |       |
|              |             |             |                                                                       |                 |          |          |       |

## **lute**

| iIIator 1      |            | LFO               |                | Low-pass filter |          |          |       |
|----------------|------------|-------------------|----------------|-----------------|----------|----------|-------|
| Wave:          | PW=<br>25% | Routing:          | Amplitude      |                 | 24db     | 12db     |       |
| Tune:          | -          | Wave:             | Triangle       | Cutoff:         | 40hz 10% | 40hz 10% |       |
|                |            | Frequency:        | 3.5hz moderate | Resonance:      | 0%       |          |       |
| Mix :          | Odb 100%   | Depth:            | 7%             | Envelope:       | 60%      |          |       |
| iIIator 2      |            | Glide:            | on             | A               | 0        | S        | R     |
| Wave:          | -          | time:             | 0.015s         | 0.11s           | max      | 100%     | 0.28s |
| Tune:          | -          | Unison:           | off            | Amplifier       |          |          |       |
|                |            | Voices:           | mult i         | A               | 0        | S        | R     |
| Mix :          | -          |                   |                | 0.11s           | max      | 100%     | 0.28s |
| Csc 2 Track:   | -          |                   |                |                 |          |          |       |
| Osc<br>2 Sync: | -          |                   |                |                 |          |          |       |
| Noise :        | off        | Alternate: Osc 1: | sawtooth       |                 |          |          |       |

## **boe**

Mix: -

Mix: -

| dilator 1        |            | LFO        |                    | Low-pass filter |          |          |       |
|------------------|------------|------------|--------------------|-----------------|----------|----------|-------|
| Wave:            | PW=<br>20% | Routing:   | Pitch              |                 | 24db     | 12db     |       |
| Tune:            | -          | Wave:      | Sine               | Cutoff:         | 40hz 10% | 40hz 10% |       |
|                  |            | Frequency: | 7.5hz<br>moderate  | Resonance:      | 25%      |          |       |
| Mix:             | Odb 100%   | Depth:     | 1 cents very light | Envelope:       | 60%      |          |       |
| cillator 2       |            | Glide:     | off                | A               | 0        | S        | R     |
| Wave:            | PW=5%      | time:      | -                  | 0.15s           | max      | 100%     | max   |
| Tune:            | -          | Unison:    | off                | Amplifier       |          |          |       |
|                  |            | Vo ices:   | multi              | A               | 0        | S        | R     |
| Mix:             | Odb 100%   |            |                    | Os              | max      | 100%     | 0.14s |
| :-sc<br>2 Track: | on         |            |                    |                 |          |          |       |
|                  |            |            |                    |                 |          |          |       |

Osc 2 Sync: off Alternate: Osc 1: sawtooth , -3.6db (85%), Osc 2: triangle, +2 octaves, -24.9 db (40%), Noise : off Filter resonance 20%, Envelope 80%

## **Piccolo**

| Oscillator 1 |           | LFO           |                                                                                     | Low-pass filter |          |          |       |
|--------------|-----------|---------------|-------------------------------------------------------------------------------------|-----------------|----------|----------|-------|
| Wave:        | Sawtooth  | Routing:      | Amplitude                                                                           |                 | 24db     | 12db     |       |
| Tune:        | -         | Wave:         | Triangle                                                                            | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |           | Frequency:    | 5hz moderate                                                                        | Resonance:      | 50%      |          |       |
| Mix:         | -9db 80%  | Depth :       | 5%                                                                                  | Envelope:       | 60%      |          |       |
| Oscillator 2 |           | Glide:        | on                                                                                  | A               | D        | S        | R     |
| Wave:        | Triangle  | time:         | O.01s                                                                               | 0.11s           | max      | 100%     | 0.285 |
| Tune :       | +1 octave | Unison:       | off                                                                                 | Amplifier       |          |          |       |
|              |           | Voices:       | multi                                                                               | A               | D        | S        | R     |
| Mix:         | Odb 100%  |               |                                                                                     | O.11s           | max      | 100%     | 0.285 |
| Osc 2 Track: | on        |               |                                                                                     |                 |          |          |       |
| Osc 2 Sync:  | off       |               | Alternate: Osc 1: square, +1 octave, -25db (40%), Osc 2: +1 octave, -18db (55%), Fi |                 |          |          |       |
| Noise:       | off       | envelope 100% |                                                                                     |                 |          |          |       |

# **BRASS**

## French Horn

| Oscillator 1 |          | LFO            |                    | Low-pass filte     | r               |             |       |
|--------------|----------|----------------|--------------------|--------------------|-----------------|-------------|-------|
| Wave:        | PW = 10% | Routing:       | -                  |                    | 24db            | <u>12db</u> |       |
| Tune:        | -        | Wave:          | -                  | Cutoff:            | 40hz 10%        | 40hz 10%    |       |
|              |          | Frequency:     | -                  | Resonance:         | 20%             |             |       |
| Mix:         | 0db 100% | Depth:         | -                  | Envelope:          | 45%             |             |       |
| Oscillator 2 |          | Glide:         | off                | Α                  | D               | S           | R     |
| Wave:        | - /      | time:          | -                  | 0.05s              | 5.76s           | 94%         | 0.39s |
| Tune:        | -        | Unison:        | off                | Amplifier          |                 |             |       |
|              |          | Voices:        | multi              | Α                  | D               | S           | R     |
| Mix:         | -        |                |                    | 0s                 | 3.9s            | 96%         | 0.93s |
| Osc 2 Track: | -        | l              |                    |                    |                 |             |       |
| Osc 2 Sync:  | -        | Alternate: Osc | c 1: sawtooth, Osc | 2: trianale. +2 oc | taves. Fiter: e | nvelope 55% |       |

Noise: off Mix: -

## Harmonica

| Oscillator 1 |           | LFO        |            | Low-pass filte | r          |             | ·     |
|--------------|-----------|------------|------------|----------------|------------|-------------|-------|
| Wave:        | PW=2%     | Routing:   | PW osc 1   |                | 24db       | <u>12db</u> |       |
| Tune:        | -         | Wave:      | Triangle   | Cutoff:        | 1.9khz 66% | 1.2khz 59%  |       |
|              |           | Frequency: | 1.6hz slow | Resonance:     | 0%         |             |       |
| Mix:         | -11db 75% | Depth:     | 85% deep   | Envelope:      | 65%        |             |       |
| Oscillator 2 |           | Glide:     | off        | Α              | D          | S           | R     |
| Wave:        | PW=15%    | time:      | -          | 0.16s          | max        | 100%        | 0.16s |
| Tune:        | +8 semi   | Unison:    | off        | Amplifier      |            |             |       |
|              | +7 cents  | Voices:    | multi      | Α              | D          | S           | R     |
| Mix:         | 0db 100%  |            | 7          | 0.13s          | 0.33s      | 50%         | 0.14s |
| Osc 2 Track: | on        |            |            |                |            |             |       |
| Osc 2 Sync:  | on        |            |            |                |            |             |       |
| Noise:       | off       | ]          |            |                |            |             |       |

**Penny Whistle**

| Oscillator 1 |            | LFO        |              | Low-pass filter |            |            |       |
|--------------|------------|------------|--------------|-----------------|------------|------------|-------|
| Wave:        | Square     | Routing:   | Amplitude    |                 | 24db       | 12db       |       |
| Tune:        | -          | Wave:      | Triangle     | Cutoff:         | 1.1khz 58% | 800 hz 53% |       |
|              |            | Frequency: | 90hz extreme | Resonance:      | 80%        |            |       |
| Mix:         | Odb 100%   | Depth:     | 5% shallow   | Envelope:       | 77%        |            |       |
| Oscillator 2 |            | Glide:     | on           | A               | 0          | S          | R     |
| Wave:        | Triangle   | time:      | 0.04s        | 0.11s           | max        | 100%       | max   |
| Tune:        | +2 octaves | Unison:    | off          | Amplifier       |            |            |       |
|              |            | Voices:    | multi        | A               | 0          | S          | R     |
| Mix:         | -7db 85%   |            |              | 0.11 s          | max        | 100%       | 0.575 |
| Osc 2 Track: | on         |            |              |                 |            |            |       |
| Osc 2 Sync : | off        |            |              |                 |            |            |       |
| Noise:       | off        |            |              |                 |            |            |       |
| Mix:         | -          |            |              |                 |            |            |       |

**Saxophone**

| Oscillator 1 |            | LFO        |                   | Low-pass filter |          |          |       |
|--------------|------------|------------|-------------------|-----------------|----------|----------|-------|
| Wave:        | PW=30%     | Routing:   | Pitch osc1 , osc2 |                 | 24db     | 12db     |       |
| Tune:        | -          | Wave:      | Sine              | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |            | Frequency: | moderate<br>7.5hz | Resonance:      | 0%       |          |       |
| Mix :        | Odb 100%   | Depth:     | 10 cnts (shallow) | Envelope:       | 90%      |          |       |
| Oscillator 2 |            | Glide:     | off               | A               | 0        | S        | R     |
| Wave:        | PW=45%     | time:      | -                 | 0.14s           | 0.37s    | 78%      | max   |
| Tune:        | +8 semi    | Unison:    | off               | Amplifier       |          |          |       |
|              |            | Voices:    | multi             | A               | 0        | S        | R     |
| Mix:         | -9.6db 75% |            |                   | Os              | max      | 100%     | 0.305 |
| Osc 2 Track: | on         |            |                   |                 |          |          |       |

Osc2 Sync: . **on** Alternate: Osc 1: sawtooth, -3.6db (85%), Osc 2: sawtooth, +1 octave, sync off, LFO: Noise: off route amplitude, depth 6%

## **Trombone**

| illator 1      |           | LFO        |                 | Low-pass filter |           |           |       |
|----------------|-----------|------------|-----------------|-----------------|-----------|-----------|-------|
| Wave:          | Sawtooth  | Routing:   | Amplitude       |                 | 24db      | 12db      |       |
| Tune:          | -         | Wave:      | Triangle        | Cutoff:         | 900hz 55% | 200hz 33% |       |
|                |           | Frequency: | moderate<br>5hz | Resonance:      | 0%        |           |       |
| Mix:           | Odb 100%  | Depth:     | 5%              | Envelope:       | 30%       |           |       |
| ill ato r 2    |           | Giioe:     | off             | A               | D         | S         | R     |
| Wave:          | Triangle  | time:      | -               | 0. 11s          | max       | 100%      | 0.18s |
| Tune:          | +1 octave | Unison:    | off             | Ampl ifier      |           |           |       |
|                |           | Voices:    | mul ti          | A               | 0         | S         | R     |
| Mix:           | Odb 100%  |            |                 | 0.06s           | max       | 100%      | 0.50s |
| sc 2 Track:    | on        |            |                 |                 |           |           |       |
| Osc<br>2 Sync: | off       |            |                 |                 |           |           |       |
| Noise :        | off       |            |                 |                 |           |           |       |
| Mix:           | -         |            |                 |                 |           |           |       |

**Trumpet**

Noise: off Mix: -

| illator 1      |             | LFO        |                   | Low-pass fi Iter |          |          |       |
|----------------|-------------|------------|-------------------|------------------|----------|----------|-------|
| Wave:          | Sawtooth    | Routing:   | Amplitude         |                  | 24db     | 12db     |       |
| Tune:          | -           | Wave:      | Triangle          | Cutoff:          | 50hz 13% | 40hz 10% |       |
|                |             | Frequency: | moderate<br>7.5hz | Resonance:       | 15%      |          |       |
| Mix :          | Odb 100%    | Depth:     | 5%                | Envelope:        | 75%      |          |       |
| illato r 2     |             | Glide:     | off               | A                | 0        | S        | R     |
| Wave:          | Sawtooth    | time :     | -                 | 0.08s            | max      | 100%     | 0.19s |
| Tu ne:         | +1 octave   | Unison:    | off               | Amplifier        |          |          |       |
|                |             | Vo ices :  | mu lti            | A                | 0        | S        | R     |
| Mix:           | -14.4db 65% |            |                   | Os               | max      | 100%     | 0.195 |
| sc 2 Track:    | on          |            |                   |                  |          |          |       |
| Osc<br>2 Sync: | off         |            |                   |                  |          |          |       |
|                |             |            |                   |                  |          |          |       |

## **Tuba**

Noise: off Mix: -

| Oscillator 1 |           | LFO        |            | Low-pass filter |          |          |       |
|--------------|-----------|------------|------------|-----------------|----------|----------|-------|
| Wave :       | Sawtooth  | Routing:   | Amplit ude |                 | 24db     | 12db     |       |
| Tune :       | -         | Wave :     | Triangle   | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |           | Frequency: | 204hz slow | Resonance:      | -        |          |       |
| Mix:         | -6db 85%  | Depth:     | 5%         | Envelope:       | 60%      |          |       |
| Oscillator 2 |           | Glide:     | off        | A               | 0        | S        | R     |
| Wave :       | Sawtooth  | time:      | -          | 0.7s            | max      | 100%     | 0.11s |
| Tune :       | -1 octave | Unison:    | off        | Amplifier       |          |          |       |
|              |           | Voices:    | multi      | A               | 0        | S        | R     |
| Mix:         | Odb 100%  |            |            | 0.03s           | max      | 100%     | 0.115 |
| Osc 2 Track: | on        |            |            |                 |          |          |       |
| Osc 2 Sync:  | off       |            |            |                 |          |          |       |

## Accordion

| Oscillator 1 |           | LFO        |           |   | Low-pass filte | r          |             |       |
|--------------|-----------|------------|-----------|---|----------------|------------|-------------|-------|
| Wave:        | PW=10%    | Routing:   | Amplitude |   | •              | 24db       | <u>12db</u> |       |
| Tune:        | -         | Wave:      | Triangle  |   | Cutoff:        | 8.2khz 87% | 6.0khz 82%  |       |
|              |           | Frequency: | 13hz fast |   | Resonance:     | 0%         |             |       |
| Mix:         | 0db 100%  | Depth:     | 5%        |   | Envelope:      | 0%         |             |       |
| Oscillator 2 |           | Glide:     | off       | 9 | Α              | D          | S           | R     |
| Wave:        | PW=10%    | time:      | -         |   | -              | -          | -           | -     |
| Tune:        | +15 cents | Unison:    | off       |   | Amplifier      |            |             |       |
|              |           | Voices:    | multi     |   | Α              | D          | s           | R     |
| Mix:         | 0db 100%  |            |           |   | 0.18s          | max        | 100%        | 0.18s |
| Osc 2 Track: | on        |            |           |   |                |            |             |       |
| Osc 2 Sync:  | off       |            |           |   |                |            |             |       |
| Noise:       | off       |            |           |   |                |            |             |       |
| Mix:         | _         |            |           |   |                |            |             |       |

## Celeste

Noise: off

Mix:

| Oscillator 1 |          | LFO        |       |   | Low-pass filte | r          | _         |       |
|--------------|----------|------------|-------|---|----------------|------------|-----------|-------|
| Wave:        | Triangle | Routing:   | -     |   | -              | 24db       | 12db      |       |
| Tune:        | -        | Wave:      | -     |   | Cutoff:        | 1.2khz 59% | 500hz 46% |       |
|              | v        | Frequency: | -     |   | Resonance:     | -          |           |       |
| Mix:         | 0db 100% | Depth:     | ÷     |   | Envelope:      | 100%       |           |       |
| Oscillator 2 |          | Glide:     | -     |   | Α              | D          | s         | R     |
| Wave:        | -        | time:      | -     |   | 0s             | 0.07s      | 45%       | 2.10s |
| Tune:        | -        | Unison:    | off   |   | Amplifier      |            |           |       |
|              |          | Voices:    | all · |   | Α.             | D          | s         | R     |
| Mix:         | -        |            |       |   | 0s             | 2.10s      | 0%        | 2.10s |
| Osc 2 Track: | -        |            |       | , |                |            |           |       |
| Osc 2 Sync:  | -        |            |       |   |                |            |           |       |

note: If using a square wave instead of a triangle wave for oscillator 1 then reduce the filter frequency by half

## Clavichord

| Oscillator 1 |           | LFO        |                         | Low-pass filt | er          |             |      |
|--------------|-----------|------------|-------------------------|---------------|-------------|-------------|------|
| Wave:        | Sawtooth  | Routing:   | Pitch                   |               | <u>24db</u> | <u>12db</u> |      |
| Tune:        | -         | Wave:      | Triangle                | Cutoff:       | 1.8khz 65%  | 1khz 57%    |      |
|              |           | Frequency: | 1hz very slow           | Resonance:    | 0%          |             |      |
| Mix:         | 0db 100%  | Depth:     | 15 cent shallow vibrato | Envelope:     | 70%         |             |      |
| Oscillator 2 |           | Glide:     | -                       | Α             | D           | S           | R    |
| Wave:        | Sawtooth  | time:      | -                       | 0s            | 0.10s       | 65%         | man  |
| Tune:        | +1 octave | Unison:    | off                     | Amplifier     |             |             |      |
|              | +4 semi   | Voices:    | multi                   | Α             | D           | s           | R    |
| Mix:         | 0db 100%  |            |                         | 0s            | 1.9s        | 0%          | 0.35 |
| Osc 2        |           |            |                         |               |             |             |      |
| Track:       | on        |            |                         |               |             |             |      |
| Osc 2 Sync:  | on        | 1          |                         |               |             |             |      |
| Noise:       | off       |            |                         |               |             |             |      |
| Mix:         | -         |            |                         |               |             |             |      |

## **Electric Piano**

| LICOLIN      | o i idilo  |            |       |                |           |             |      |
|--------------|------------|------------|-------|----------------|-----------|-------------|------|
| Oscillator 1 |            | LFO        |       | Low-pass filte | er        |             |      |
| Wave:        | Sawtooth   | Routing:   | -     |                | 24db      | <u>12db</u> |      |
| Tune:        | -          | Wave:      | -     | Cutoff:        | 630hz 50% | 275hz 38%   |      |
|              |            | Frequency: | -     | Resonance:     | 0%        |             |      |
| Mix:         | 0db 100%   | Depth:     | -     | Envelope:      | 50%       |             |      |
| Oscillator 2 |            | Glide:     | off   | A              | D         | S           | R    |
| Wave:        | PW=5%      | time:      | -     | 0s             | 0.33s     | 50%         | max  |
| Tune:        | +2 octaves | Unison:    | off   | Amplifier      |           |             |      |
|              | +9 semi    | Voices:    | multi | Α              | D         | s           | R    |
| Mix:         | 0db 100%   |            |       | 0s             | 5.14s     | 0%          | 0.66 |
| Osc 2        |            |            |       |                |           |             |      |
| Track:       | on         |            |       |                |           |             |      |
| Osc 2 Sync:  | on         | ]          |       |                |           |             |      |
| Noise:       | off        | 1          |       |                |           |             |      |

**Harpsichord** 

| Scillator 1  |          | LFO        |       | Low-pass filte | r           |             |       |
|--------------|----------|------------|-------|----------------|-------------|-------------|-------|
| Wave:        | PW=25%   | Routing:   | -     |                | <u>24db</u> | <u>12db</u> |       |
| Tune:        | - ',     | Wave:      | -     | Cutoff:        | 2.4khz 69%  | 2.4khz 69%  |       |
|              |          | Frequency: | -     | Resonance:     | 0%          |             |       |
| Mix:         | -3db 95% | Depth:     | -     | Envelope:      | 100%        |             |       |
| ©scillator 2 |          | Glide:     | off   | Α              | D           | s           | R     |
| Wave:        | PW=5%    | time:      | -     | 0s             | 0.23s       | 65%         | max   |
| Tune:        | +9 semi  | Unison:    | off   | Amplifier      | ,           |             |       |
|              |          | Voices:    | multi | Α              | D           | s           | R     |
| Mix:         | 0db 100% |            |       | 0s             | 2s          | 0%          | 0.35s |
| Osc 2 Track: | on       | 8          |       |                |             |             |       |
| Osc 2 Sync:  | on       |            |       |                |             |             |       |
| Noise:       | off      |            |       |                |             |             |       |
| Mix.         | _        | l          |       |                |             |             |       |

**Organ** 

| <u> </u>     |            |            | 20 00 00 |                |             | 2.1         |       |
|--------------|------------|------------|----------|----------------|-------------|-------------|-------|
| Oscillator 1 |            | LFO        |          | Low-pass filte | r           |             |       |
| Wave:        | Triangle   | Routing:   | -        |                | <u>24db</u> | <u>12db</u> |       |
| Tune:        | -          | Wave:      | -        | Cutoff:        | 20khz 100%  | 20khz 100%  |       |
|              |            | Frequency: | -        | Resonance:     | 0%          |             |       |
| Mix:         | 0db 100%   | Depth:     | -        | Envelope:      | 0%          |             |       |
| Oscillator 2 |            | Glide:     | off      | Α              | D           | S           | R     |
| Wave:        | Triangle   | time:      |          |                | -           | -           | -     |
| Tune:        | -2 octaves | Unison:    | off      | Amplifier      |             |             |       |
|              |            | Voices:    | multi    | Α              | D           | S           | R     |
| Mix:         | 0db 100%   | HI .       |          | 0.6s           | max         | 100%        | 0.40s |
| Osc 2 Track: | on         |            |          |                |             |             |       |
| Osc 2 Sync:  | off        |            |          |                |             |             |       |
| Noise:       | off        |            |          |                |             |             |       |

## **Piano**

Mix: -

| Oscillator 1 |             | LFO        |       | Low-pass filter |          |          |       |
|--------------|-------------|------------|-------|-----------------|----------|----------|-------|
| Wave :       | Sawtooth    | Routing:   | -     |                 | 24db     | 12db     |       |
| Tune:        | -           | Wave :     | -     | Cutoff:         | 40hz 10% | 40hz 10% |       |
|              |             | Frequency: | -     | Resonance:      | 0%       |          |       |
| Mix:         | -10.4db 75% | Depth:     | -     | Envelope:       | 75%      |          |       |
| Oscillator 2 |             | Glide:     | off   | A               | 0        | S        | R     |
| Wave :       | PW=15%      | time:      | -     | Os              | 5.22s    | 0%       | max   |
| Tune:        | +1 octave   | Unison:    | off   | Amplifier       |          |          |       |
|              | +2 semi     | Voices:    | multi | A               | 0        | S        | R     |
| Mix:         | Odb 100%    |            |       | Os              | 0.67s    | 25%      | 0.50s |
| Osc 2 Track: | on          |            |       |                 |          |          |       |
| Osc 2 Sync:  | on          |            |       |                 |          |          |       |

Noise: off Alternate: Osc 1: Odb (100%), Osc 2: sawtooth, +1 octave, Odb (100%), sync off

# **VOCALS**

A**nge s**

| Oscillator 1 |          | LFO            |                         | Low-pass filter |           |           |       |
|--------------|----------|----------------|-------------------------|-----------------|-----------|-----------|-------|
| Wave:        | Sawtooth | Routing:       | Pitch                   |                 | 24db      | 12db      |       |
| Tune:        | -        | Wave:          | Triangle                | Cutoff:         | 900hz 55% | 900hz 55% |       |
|              |          | Frequency:     | 2.4hz<br>slow           | Resonance:      | 70%       |           |       |
| Mix:         | Odb 100% | Depth:         | 20 cent shallow         | Envelope:       | 0%        |           |       |
| Oscillator 2 |          | Glide:         | off                     | A               | D         | S         | R     |
| Wave:        | -        | time:          | -                       | -               | -         | -         | -     |
| Tune:        | -        | Unison:        | off                     | Amplifier       |           |           |       |
|              |          | Voices:        | multi                   | A               | D         | S         | R     |
| Mix:         | -        |                |                         | 0.32s           | max       | 100%      | 0.93s |
| Osc 2 Track: | -        |                |                         |                 |           |           |       |
| Osc 2 Sync:  | -        |                |                         |                 |           |           |       |
| Noise:<br>I  | off      |                |                         |                 |           |           |       |
| Mix:<br>I    | -        | note's: C4-C6, | 24 dB filter works best |                 |           |           |       |

## **Choir**

Noise: off Mix:

| IOscillator<br>1 |            |             |               |                 |            |            |       |
|------------------|------------|-------------|---------------|-----------------|------------|------------|-------|
|                  |            | LFO         |               | Low-pass filter |            |            |       |
| Wave:            | PW=15%     | Routing:    | Pitch         |                 | 24db       | 12db       |       |
| Tune:            | -2 octaves | Wave:       | Triangle      | Cutoff:         | 1.7khz 64% | 1.0khz 56% |       |
|                  |            | Frequency:  | 2.4hz<br>slow | Resonance:      | 0%         |            |       |
| Mix:             | Odb 100%   | Depth: ' 20 | cent shallow  | Envelope:       | 0%         |            |       |
| Oscillator 2     |            | Glide:      | off           | A               | D          | S          | R     |
| Wave:            | PW=25%     | time:       | -             | -               | -          | -          | -     |
| Tune:            | -          | Unison:     | off           | Amplifier       |            |            |       |
|                  |            | Voices:     | multi         | A               | D          | S          | R     |
| Mix:             | Odb 100%   |             |               | 0.32s           | max        | 100%       | 0.93s |
| Osc 2 Track:     | on         |             |               |                 |            |            |       |
| Osc 2 Sync:      | off        |             |               |                 |            |            |       |
|                  |            |             |               |                 |            |            |       |

## **Vocal Female**

| Oscillator 1 |             | LFO             |                                  | Low-pass filter |            |            |       |
|--------------|-------------|-----------------|----------------------------------|-----------------|------------|------------|-------|
| Wave:        | PW=5%       | Routing:        | Pitch                            |                 | 24db       | 12db       |       |
| Tune:        | -           | Wave:           | Triangle                         | Cutoff:         | 1.2khz 59% | 1.2khz 59% |       |
|              |             | Frequency:      | 204hz<br>slow                    | Resonance:      | 50%        |            |       |
| Mix:         | Odb 100%    | Depth :         | 20 cent shallow                  | Envelope:       | 0%         |            |       |
| Oscillator 2 |             | Glide:          | off                              | A               | D          | S          | R     |
| Wave:        | PW=25%      | time:           | -                                | -               | -          | -          | -     |
| Tune:        | -           | Unison :        | off                              | Amplifier       |            |            |       |
|              |             | Voices:         | multi                            | A               | D          | S          | R     |
| Mix:         | -13.9db 65% |                 |                                  | 0.32s           | max        | 100%       | 0.935 |
| Osc 2 Track: | on          |                 |                                  |                 |            |            |       |
| Osc 2 Sync:  | off         |                 |                                  |                 |            |            |       |
| Noise:       | off         |                 |                                  |                 |            |            |       |
| Mix:         | -           | notes: 1. C4-C6 | 2.<br>24db filter is best to use |                 |            |            |       |

## **Vocal Male**

| Oscillator 1 |            | LFO               |                                              | Low-pass filter |            |                                    |       |
|--------------|------------|-------------------|----------------------------------------------|-----------------|------------|------------------------------------|-------|
| Wave:        | PW=15%     | Routing:          | Pitch                                        |                 | 24db       | 12db                               |       |
| Tune:        | -1 octave  | Wave:             | Triangle                                     | Cutoff:         | 2.0khz 67% | 1.2khz 59%                         |       |
|              |            | Frequency:        | 204hz<br>slow                                | Resonance:      | 0%         |                                    |       |
| Mix:         | -Odb 100%  | Depth:            | 20 cent shallow                              | Envelope:       | 0%         |                                    |       |
| Oscillator 2 |            | Glide:            | off                                          | A               | D          | S                                  | R     |
| Wave:        | PW=25%     | time:             | -                                            | -               | -          | -                                  | -     |
| Tune:        | -          | Unison:           | off                                          | Amplifier       |            |                                    |       |
|              |            | Voices:           | multi                                        | A               | D          | S                                  | R     |
| Mix:         | -4.3db 90% |                   |                                              | 0.32s           | max        | 100%                               | 0.935 |
| Osc 2 Track: | on         |                   |                                              |                 |            |                                    |       |
| Osc 2 Sync : | off        | Alternate: Osc 1: | sawtooth, Odb (100%), Osc 2:                 |                 |            | sawtooth, Odb (100%), Filter: 24db |       |
| Noise:       | off        |                   | 900hz (55%), 12db 600hz (49%), resonance 70% |                 |            |                                    |       |

Mix: - note: 12 dB filter works best

Whistling

Osc 2 Sync:

Noise:

Mix:

off

| Oscillator 1 |            | LFO        |                  | Low-pass filte | r         |             |       |
|--------------|------------|------------|------------------|----------------|-----------|-------------|-------|
| Wave:        | Triangle   | Routing:   | Pitch            |                | 24db      | <u>12db</u> |       |
| Tune:        | +2 octaves | Wave:      | Triangle         | Cutoff:        | 500hz 46% | 200hz 33%   |       |
|              |            | Frequency: | 7hz moderate     | Resonance:     | 0%        |             |       |
| Mix:         | 0db 100%   | Depth:     | 12 cents shallow | Envelope:      | 40%       |             |       |
| Oscillator 2 |            | Glide:     | off              | Α              | D         | S           | R     |
| Wave:        | - '        | time:      | -                | 0.04s          | max       | 100%        | max   |
| Tune:        | -          | Unison:    | off              | Amplifier      |           |             |       |
|              |            | Voices:    | 2                | Α              | D         | s           | R     |
| Mix:         | -          |            |                  | 0.03s          | max       | 100%        | 0.35s |
| Osc 2 Track: | _          |            |                  |                |           | •           |       |

notes: 1. Lower the cutoff frequency when playing lower pitches to avoid woodwind characteristics 2. When using a square wave instead of a triangle wave for oscillator 1 lower the filter cutoff frequency to 24db; 0.3khz or 12db;0.1khz

# **TUNED PERCUSSION**

## **Bell**

| Oscillator 1 |           | LFO                   |                | Low-pass filter |            |           |       |
|--------------|-----------|-----------------------|----------------|-----------------|------------|-----------|-------|
| Wave:        | Triangle  | Routing:<br>Amplitude |                |                 | 24db       | 12db      |       |
| Tune:        | -         | Wave:                 | Triangle       | Cutoff:         | 20khz 100% | 20hz 100% |       |
|              |           | Frequency:            | 7.5hz moderate | Resonance:      | 0%         |           |       |
| Mix:         | Odb 100%  | Depth:                | 5%             | Envelope:       | 0%         |           |       |
| Oscillator 2 |           | Glide:                | off            | A               | 0          | S         | R     |
| Wave:        | Square    | time:                 | -              | -               | -          | -         | -     |
| Tune:        | +5 semi   | Unison:               | off            | Amplifier       |            |           |       |
|              |           | Voices:               | multi          | A               | 0          | S         | R     |
| Mix:         | -14db 65% |                       |                | Os              | 1.30s      | 0%        | 3.30s |
| Osc 2 Track: | on        |                       |                |                 |            |           |       |
| Osc 2 Sync:  | off       |                       |                |                 |            |           |       |
| Noise:       | off       |                       |                |                 |            |           |       |
| Mix:         | -         |                       |                |                 |            |           |       |

**Bongos**

Mix: - notes: G2-G4

| losctttator<br>1  |              | LFO        |     | Low-pass filter |           |           |       |
|-------------------|--------------|------------|-----|-----------------|-----------|-----------|-------|
| Wave:             | Triangle     | Routing:   | -   |                 | 24db      | 12db      |       |
| Tune:             | -            | Wave:      | -   | Cutoff:         | 600hz 49% | 400hz 43% |       |
|                   |              | Frequency: | -   | Resonance:      | 0%        |           |       |
| Mix:              | Odb 100%     | Depth :    | -   | Envelope:       | 60%       |           |       |
| Oscillator 2      |              | Glide:     | -   | A               | 0         | S         | R     |
| Wave:             | Square       | time:      | -   | Os              | 0.11s     | 0%        | 0.11s |
| Tune:             | -            | Unison:    | off | Amplifier       |           |           |       |
|                   |              | Voices:    | 2   | A               | 0         | S         | R     |
| Mix:              | -13 .9db 65% |            |     | Os              | 0.22s     | 0%        | 0.22s |
| I<br>Osc 2 Track: | on           |            |     |                 |           |           |       |
| Osc 2 Sync:       | off          |            |     |                 |           |           |       |
| Noise:            | off          |            |     |                 |           |           |       |

**Conga**

| Oscillator 1  |            | LFO        |      | Low-pass fiIter |           |              |       |
|---------------|------------|------------|------|-----------------|-----------|--------------|-------|
| Wave :        | Square     | Routing :  | -    |                 | 24db      | 12db         |       |
| Tune :        | -          | . Wave :   | -    | Cutoff:         | 300hz 39% | 150hz<br>29% |       |
|               |            | Frequency: | -    | Resonance:      | 40%       |              |       |
| Mix:          | Odb 100%   | Depth:     | -    | Envelope:       | 50%       |              |       |
| Oscillator 2  |            | Glide:     | off  | A               | D         | S            | R     |
| Wave :        | Square     | time:      | -    | Os              | 0.02s     | 80%          | max   |
| Tune :        | +1 octave  | Unison:    | off  | Amplifier       |           |              |       |
|               | +2 semi    | Voices:    | mono | A               | D         | S            | R     |
| Mix:          | -6.5db 85% |            |      | Os              | 0.15s     | 0%           | 0.155 |
| Osc 2 Track : | on         |            |      |                 |           |              |       |
| Osc 2 Sync:   | off        |            |      |                 |           |              |       |
| Noise:        | off        |            |      |                 |           |              |       |
| Mix:          | -          |            |      |                 |           |              |       |

**Glockenspiel**

| Oscillator 1 |           | LFO                 |     | Low-pass filter |            |            |       |
|--------------|-----------|---------------------|-----|-----------------|------------|------------|-------|
| Wave:        | Triangle  | Routing:            | -   |                 | 24db       | 12db       |       |
| Tune:        | -         | Wave:               | -   | Cutoff:         | 3.8khz 76% | 1.9khz 66% |       |
|              |           | Frequency:          | -   | Resonance:      | -          |            |       |
| Mix:         | Odb 100%  | Depth:              | -   | Envelope:       | 75%        |            |       |
| Oscillator 2 |           | Glide:              | -   | A               | D          | S          | R     |
| Wave :       | Triangle  | time:               | -   | Os              | 0.10s      | 25%        | 0.105 |
| Tune :       | +2 octave | Unison:             | off | Amplifie r      |            |            |       |
|              | +6 semi   | Voices:             | all | A               | D          | S          | R     |
| Mix:         | Odb 100%  |                     |     | Os              | 1.20s      | 0%         | 1.205 |
| Osc 2 Track: | on        |                     |     |                 |            |            |       |
| Osc 2 Sync:  | off       |                     |     |                 |            |            |       |
| Noise:       | off       |                     |     |                 |            |            |       |
| Mix:         | -         | note: Play above G5 |     |                 |            |            |       |

## Marimba

| Oscillator 1 |            | LFO        |           | Low-pass filte | r          |             |       |
|--------------|------------|------------|-----------|----------------|------------|-------------|-------|
| Wave:        | Triangle   | Routing:   | Amplitude |                | 24db       | <u>12db</u> |       |
| Tune:        | -          | Wave:      | Triangle  | Cutoff:        | 2.9khz 72% | 1.9khz 66%  |       |
|              |            | Frequency: | 8hz fast  | Resonance:     | 0%         |             |       |
| Mix:         | 0db 100%   | Depth:     | 11%       | Envelope:      | 0%         |             |       |
| Oscillator 2 |            | Glide:     | off       | Α              | D          | S           | R     |
| Wave:        | Triangle   | time:      | # ×       | -              | -          | =           | -     |
| Tune:        | +2 octaves | Unison:    | off       | Amplifier      |            |             |       |
|              |            | Voices:    | multi     | Α              | D          | S           | R     |
| Mix:         | -9.6db 75% |            |           | 0s             | 1.66s      | 20%         | 1.66s |
| Osc 2 Track: | on         |            |           |                | 8          |             |       |
| Osc 2 Sync:  | off        |            |           |                |            |             |       |
| Noise:       | off        | 1          |           |                |            |             |       |
| Mix:         | -          |            |           | *              |            |             |       |

Timpani

| ·····pui     |             |            |       |                 |             |             |       |
|--------------|-------------|------------|-------|-----------------|-------------|-------------|-------|
| Oscillator 1 |             | LFO        |       | Low-pass filter | •           |             |       |
| Wave:        | Square      | Routing:   | -     |                 | <u>24db</u> | <u>12db</u> |       |
| Tune:        | -1 octave   | Wave:      |       | Cutoff:         | 800hz 53%   | 500hz 46%   |       |
|              |             | Frequency: | -     | Resonance:      | 45%         |             |       |
| Mix:         | 0db 100%    | Depth:     | -     | Envelope:       | 35%         |             |       |
| Dscillator 2 |             | Glide:     | off   | Α               | D           | S           | R     |
| Wave:        | Square      | time:      | -     | 0               | 0.35s       | 0%          | 0.38s |
| Tune:        | -1 octave   | Unison:    | off   | Amplifier       |             |             |       |
|              | -10 semi    | Voices:    | multi | Α               | D ,         | s           | R     |
| Mix:         | -15.3db 60% |            |       | 0s              | 2.89s       | 0%          | 1.90s |
| Osc 2 Track: | on          |            |       |                 |             |             |       |
| Osc 2 Sync:  | off         |            |       |                 |             |             |       |
| Noise:       | off         |            |       |                 |             |             |       |

**Xylophone**

| Oscillator 1 |           | LFO        |                   | Low-pass.fiIter |           |           |       |
|--------------|-----------|------------|-------------------|-----------------|-----------|-----------|-------|
| Wave:        | Triangle  | Routing:   | Ampl itude        |                 | 24db      | 12db      |       |
| Tune:        | +1 octave | Wave :     | Triangle          | Cutoff:         | 300hz 39% | 100hz 23% |       |
|              | +10 semi  | Frequency: | 7.5hz<br>moderate | Resonance:      | -         |           |       |
| Mix:         | Odb 100%  | Depth:     | 5%                | Envelope:       | 60%       |           |       |
| Oscillator 2 |           | Glide:     | off               | A               | 0         | S         | R     |
| Wave:        | Triangle  | time :     | -                 | Os              | 0.53s     | 45%       | 0.50s |
| Tune :       | -         | Unison:    | off               | Amplifier       |           |           |       |
|              |           | Voices:    | multi             | A               | 0         | S         | R     |
| Mix:         | Odb 100%  |            |                   | Os              | 1.88s     | 0%        | 1.78s |
| Osc 2 Track: | on        |            |                   |                 |           |           |       |
| Osc 2 Sync:  | off       |            |                   |                 |           |           |       |
| Noise:       | off       |            |                   |                 |           |           |       |
| Mix:         | -         |            |                   |                 |           |           |       |

# UNTUNED PERCUSSION

## **Bass Drum**

| Oscillator 1 |          | LFO        |       | Low-pass filte | r          |             |       |
|--------------|----------|------------|-------|----------------|------------|-------------|-------|
| Wave:        | Triangle | Routing:   | -     |                | 24db       | <u>12db</u> |       |
| Tune:        | -2 oct   | Wave:      | -     | Cutoff:        | 20khz 100% | 20khz 100%  |       |
|              |          | Frequency: | -     | Resonance:     | 0%         |             |       |
| Mix:         | 0db 100% | Depth:     | -     | Envelope:      | 0%         |             |       |
| Oscillator 2 |          | Glide:     | off   | Α              | D          | s           | R     |
| Wave:        | Triangle | time:      | -     | -              |            |             | -     |
| Tune:        | -2 oct   | Unison:    | off   | Amplifier      |            |             |       |
|              |          | Voices:    | multi | A              | D          | S           | R     |
| Mix:         | 0db 100% |            |       | 0s             | 0.12s      | 0%          | 0.12s |
| Osc 2 Track: | on       |            |       |                |            |             |       |
| Osc 2 Sync:  | off      |            |       |                |            |             |       |
| Noise:       | off      |            |       |                |            |             |       |
| Mix:         |          | I          |       |                |            |             |       |

## **Castanets**

0db 100%

Mix:

| Oscillator 1 |     | LFO        |     | Low-pass filte | r          |            |       |
|--------------|-----|------------|-----|----------------|------------|------------|-------|
| Wave:        | -   | Routing:   | -   |                | 24db       | 12db       |       |
| Tune:        | .=  | Wave:      | -   | Cutoff:        | 7.6khz 86% | 7.6khz 86% |       |
|              |     | Frequency: | -   | Resonance:     | 100%       |            |       |
| Mix:         | -   | Depth:     | -   | Envelope:      | -          |            |       |
| Oscillator 2 |     | Glide:     | -   | Α              | D          | S          | R     |
| Wave:        | -   | time:      | -   | -              | <u> </u>   | -          | -     |
| Tune:        | -   | Unison:    | off | Amplifier      |            |            |       |
|              |     | Voices:    | 1   | Α              | D          | s          | R     |
| Mix:         | -   |            |     | 0s             | 0.04s      | 0%         | 0.04s |
| Osc 2 Track: | -   |            |     |                |            |            |       |
| Osc 2 Sync:  | off |            |     |                |            |            |       |
| Noise:       | on  | ,          |     |                |            |            |       |

Clap

| Oscillator 1 |            | LFO        |                | Low-pass filte | r           |             |       |
|--------------|------------|------------|----------------|----------------|-------------|-------------|-------|
| Wave:        | -          | Routing:   | Amplitude      |                | <u>24db</u> | <u>12db</u> |       |
| Tune:        | -          | Wave:      | Square         | Cutoff:        | 1.6khz 63%  | 1.1khz 58%  |       |
| ž.           |            | Frequency: | 32hz very fast | Resonance:     | 30%         |             |       |
| Mix:         | -          | Depth:     | 45%            | Envelope:      | 50%         |             |       |
| Oscillator 2 |            | Glide:     | off            | Α              | D           | s           | R     |
| Wave:        | , <b>-</b> | time:      | -              | 0s             | 0.15s       | 0%          | 0.15  |
| Tune:        | -          | Unison:    | off            | Amplifier      |             |             |       |
|              |            | Voices:    | multi          | Α              | D           | s           | R     |
| Mix:         | -          |            | _              | 0s             | 0.11s       | 0%          | 0.11s |
| Osc 2 Track: | -          |            |                |                |             |             |       |

notes:1. 12 db filter works best 2. Set LFO to retrigger. If LFO can't retrigger then it may be best not to use since it will cause each hit to have a different amplitude

## **Claves**

Noise:

Mix:

on

0db 100%

Osc 2 Sync:

Noise:

Mix:

on

0db 100%

| Olaves       |     |            |      |   |                |            |             |       |
|--------------|-----|------------|------|---|----------------|------------|-------------|-------|
| Oscillator 1 |     | LFO        |      |   | Low-pass filte | er         |             |       |
| Wave:        | -   | Routing:   | -    |   |                | 24db       | <u>12db</u> |       |
| Tune:        | -   | Wave:      | -    |   | Cutoff:        | 2.1khz 67% | 2.1khz 67%  |       |
|              |     | Frequency: | -    |   | Resonance:     | 100%       |             |       |
| Mix:         | -   | Depth:     | -    |   | Envelope:      | 0%         |             |       |
| Oscillator 2 |     | Glide:     | -    |   | Α              | D          | s           | R     |
| Wave:        | · - | time:      | -    |   |                | -          |             | -     |
| Tune:        | -   | Unison:    | off  | 4 | Amplifier      |            | , ,=        |       |
|              |     | Voices:    | mono |   | Α              | D          | S           | R     |
| Mix:         | -   |            |      |   | 0s             | 0.14s      | 0%          | 0.14s |
| Osc 2 Track: | -   |            |      |   |                |            |             |       |
| Osc 2 Sync:  | off |            |      |   |                |            |             |       |
|              |     | <br>1      |      |   |                |            |             |       |

note: 1. Change filter cutoff amount to alter pitch. 2. Using 12db filter allows full resonance to be added without significant reduction of higher frequencies.

## **Cowbell**

| cillator 1     |           | LFO        |                                    | Low-pass filter |            |            |       |
|----------------|-----------|------------|------------------------------------|-----------------|------------|------------|-------|
| Wave:          | Square    | Routing:   | -                                  |                 | 24db       | 12db       |       |
| Tune:          | -         | Wave:      | -                                  | Cutoff:         | 8.8khz 88% | 8.8khz 88% |       |
|                |           | Frequency: | -                                  | Resonance:      | 55%        |            |       |
| Mix:           | Odb 100%  | Depth:     | -                                  | Envelope:       | 65%        |            |       |
| I Oscillator 2 |           | Glide:     | off                                | A               | D          | 5          | R     |
| Wave:          | PW=35%    | time:      | -                                  | Os              | 0.02s      | 65%        | max   |
| Tune:          | +1 octave | Unison:    | off                                | Amplifier       |            |            |       |
|                | +2 semi   | Voices:    | mono                               | A               | D          | 5          | R     |
| Mix:           | Odb 100%  |            |                                    | Os              | 0.15s      | 0%         | 0.15s |
| sc 2 Track :   | on        |            |                                    |                 |            |            |       |
| Osc 2 Sync :   | off       |            |                                    |                 |            |            |       |
| Noise:         | off       |            |                                    |                 |            |            |       |
| Mix:           | -         |            | note: Play around the fifth octave |                 |            |            |       |

**Cowbell (analog drum machine)**

Mix: - note: Play around the fifth octave

| Oscillator 1 |            | LFO        |      | Low-pass filter |            |            |       |
|--------------|------------|------------|------|-----------------|------------|------------|-------|
| Wave:        | PW = 10%   | Routing:   | -    |                 | 24db       | 12db       |       |
| Tune:        | -          | Wave:      | -    | Cutoff:         | 8.1khz 87% | 304khz 74% |       |
|              |            | Frequency: | -    | Resonance:      | 0%         |            |       |
| Mix:         | Odb 100%   | Depth :    | -    | Envelope:       | 65%        |            |       |
| Oscillator 2 |            | Glide:     | off  | A               | D          | 5          | R     |
| Wave:        | PW=<br>35% | time:      | -    | Os              | 0.02s      | 65%        | max   |
| Tune:        | +5 semi    | Unison :   | off  | Amplifier       |            |            |       |
|              |            | Voices:    | mono | A               | D          | 5          | R     |
| Mix:         | Odb 100%   |            |      | Os              | 0.15s      | 0%         | 0.15s |
| Osc 2 Track: | on         |            |      |                 |            |            |       |
| Osc 2 Sync : | off        |            |      |                 |            |            |       |
| Noise:       | off        |            |      |                 |            |            |       |

Cymbal

| Oscillator 1 |          | LFO                                     |                                                                                                                                                                                                                                                                   | Low-pass filte                          | r                     |                      |              |  |  |  |
|--------------|----------|-----------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------|-----------------------|----------------------|--------------|--|--|--|
| Wave:        | -        | Routing:                                | -                                                                                                                                                                                                                                                                 | • ************************************* | 24db                  | 12db                 |              |  |  |  |
| Tune:        | -        | Wave:                                   | -                                                                                                                                                                                                                                                                 | Cutoff:                                 | 9.4khz 89%            | 9.4khz 89%           |              |  |  |  |
|              |          | Frequency:                              | -                                                                                                                                                                                                                                                                 | Resonance:                              | 50%                   |                      |              |  |  |  |
| Mix:         | -        | Depth:                                  | -                                                                                                                                                                                                                                                                 | Envelope:                               | 70%                   |                      |              |  |  |  |
| Oscillator 2 |          | Glide:                                  | -                                                                                                                                                                                                                                                                 | Α                                       | D                     | S                    | R            |  |  |  |
| Wave:        | -        | time:                                   | -                                                                                                                                                                                                                                                                 | 0s                                      | 0.14s                 | 0%                   | 1.80s        |  |  |  |
| Tune:        | -        | Unison:                                 | off                                                                                                                                                                                                                                                               | Amplifier                               |                       |                      |              |  |  |  |
|              |          | Voices:                                 | mono                                                                                                                                                                                                                                                              | Α                                       | D                     | s                    | R            |  |  |  |
| Mix:         | -        |                                         |                                                                                                                                                                                                                                                                   | 0s                                      | 1.10s                 | 0%                   | 1.00s        |  |  |  |
| Osc 2 Track: | -        |                                         | igh-pass filtger to remove i                                                                                                                                                                                                                                      |                                         |                       |                      |              |  |  |  |
| Osc 2 Sync:  | -        | At any rate it can fill                 | instrument to synthesize. This patch took the longest of any in the book to create (~ 4 hours) and yet is still the least realistic.  At any rate it can fill the role of a cymbal or at least provide a good laugh and is included for completeness. I challenge |                                         |                       |                      |              |  |  |  |
| Noise:       | on       | enharmonically, detu                    | anyone to do better using two oscillators, noise, and a single low-pass filter! To produce a cymbal, the TR-808 used six enharmonically, detuned square wave oscillators, split by three band-pass filters. Each band was sent to its own enveloped               |                                         |                       |                      |              |  |  |  |
| Mix:         | 0db 100% | VCA before being se<br>this complexity. | ent to high-pass filters oh                                                                                                                                                                                                                                       | hell, you get the idea! I               | As early as the TR-90 | 09 the cymbal was sa | ampled due 🏗 |  |  |  |

## Side Stick

| Oscillator 1 |          | LFO        |      | Low-pass filte | r          |             |    |
|--------------|----------|------------|------|----------------|------------|-------------|----|
| Wave:        | -        | Routing:   | -    |                | 24db       | <u>12db</u> |    |
| Tune:        | -        | Wave:      | -    | Cutoff:        | 2.7khz 71% | 2.7khz 71%  |    |
|              |          | Frequency: | -    | Resonance:     | 100%       |             |    |
| Mix:         | -        | Depth:     | -    | Envelope:      | 85%        |             |    |
| Oscillator 2 |          | Glide:     | off  | Α              | D          | s           | R  |
| Wave:        | -        | time:      | -    | 0s             | 1.19s      | 0%          | 0s |
| Tune:        | -        | Unison:    | off  | Amplifier      |            |             |    |
|              |          | Voices:    | mono | Α              | D          | s           | R  |
| Mix:         | -        |            |      | 0s             | 0.09s      | 0%          | 0s |
| Osc 2 Track: | -        |            |      |                |            | ,           |    |
| Osc 2 Sync:  | -        |            |      |                |            |             |    |
| Noise:       | on       |            |      |                |            |             |    |
| Mix:         | 0db 100% |            |      |                |            |             |    |

## **Snare Drum**

| Oscillator 1 |             | LFO        |       | Low-pass filte | r          |             |       |
|--------------|-------------|------------|-------|----------------|------------|-------------|-------|
| Wave:        | Triangle    | Routing:   | -     |                | 24db       | <u>12db</u> |       |
| Tune:        | -1 octave   | Wave:      | -     | Cutoff:        | 20khz 100% | 20khz 100%  |       |
|              |             | Frequency: | -     | Resonance:     | -          |             |       |
| Mix:         | 0db 100%    | Depth:     | -     | Envelope:      | 0%         |             |       |
| Oscillator 2 |             | Glide:     | off   | Α              | D          | s           | R     |
| Wave:        | -           | time:      | -     | -              | -          | _           | -     |
| Tune:        | -           | Unison:    | off   | Amplifier      |            |             |       |
|              |             | Voices:    | multi | Α              | D          | s           | R     |
| Mix:         | <b>L</b>    |            |       | 0s             | 0.27s      | 0%          | 0.27s |
| Osc 2 Track: | -           |            |       |                |            |             |       |
| Osc 2 Sync:  | -           |            |       |                |            |             |       |
| Noise:       | on          |            |       |                |            |             |       |
| Mix:         | -31.4db 20% |            |       |                |            |             |       |

## **Tambourine**

Noise:

Mix:

0db 100%

| Oscillator 1 |   | LFO        |      | Low-pass filte | er          |             |       |
|--------------|---|------------|------|----------------|-------------|-------------|-------|
| Wave:        | - | Routing:   | -    | *              | <u>24db</u> | <u>12db</u> |       |
| Tune:        | - | Wave:      | -    | Cutoff:        | 5.3khz 81%  | 5.3khz 81%  |       |
|              |   | Frequency: | =    | Resonance:     | 100%        |             |       |
| Mix:         | - | Depth:     | -    | Envelope:      | 0%          |             |       |
| Oscillator 2 |   | Glide:     | -    | - A            | D           | S           | R     |
| Wave:        |   | time:      | -    | -              | -           | -           | -     |
| Tune:        | - | Unison:    | off  | Amplifier      |             |             |       |
|              |   | Voices:    | mono | A              | D           | s           | R     |
| Mix:         | - |            |      | 0s             | 0.34s       | 0%          | 0.34s |
| Osc 2 Track: | - |            |      |                |             |             |       |
| 0 2 0        |   |            |      |                |             |             |       |

note: Make sure that if the synthesizer's filter has keyboard tracking that it is turned off.

## Wheels of Steel

| Oscillator 1 |          | LFO        |      | Low-pass filte | r        |             |       |
|--------------|----------|------------|------|----------------|----------|-------------|-------|
| Wave:        | -        | Routing:   | -    |                | 24db     | <u>12db</u> |       |
| Tune:        | -        | Wave:      | -    | Cutoff:        | 40hz 10% | 40hz 10%    |       |
|              |          | Frequency: | -    | Resonance:     | 40%      |             |       |
| Mix:         | -        | Depth:     | -    | Envelope:      | 100%     |             |       |
| Oscillator 2 |          | Glide:     | -    | Α              | D        | S           | R     |
| Wave:        | *        | time:      | -    | 0.02s          | 0.09s    | 0%          | 0.09s |
| Tune:        | -        | Unison:    | off  | Amplifier      |          |             |       |
|              |          | Voices:    | mono | Α              | D        | s           | R     |
| Mix:         | -        |            |      | 0s             | 1.65s    | 0%          | 0.05₅ |
| Osc 2 Track: | -        |            |      |                |          |             |       |
| Osc 2 Sync:  | -        |            |      |                |          |             |       |
| Noise:       | on       |            |      |                |          |             |       |
| Mix:         | 0db 100% |            |      |                |          |             |       |

# **LEADS**

## **rass Section**

| Elscillator 1 |           | LFO        |                 | Low-pass filter |          |          |       |
|---------------|-----------|------------|-----------------|-----------------|----------|----------|-------|
| Wave:         | Square    | Routing:   | PW osc1 , osc 2 |                 | 24db     | 12db     |       |
| Tune:         | -10 cents | Wave:      | Triangle / Sine | Cutoff:         | 40hz 10% | 40hz 10% |       |
|               |           | Frequency: | 5.5 Hz          | Resonance:      | 0%       |          |       |
| Mix :         | Odb 100%  | Depth :    | 45%             | Envelope:       | 100%     |          |       |
| cillator 2    |           | Glide:     | off             | A               | 0        | S        | R     |
| Wave:         | PW =20%   | time :     | -               | 0.03s           | max      | 100%     | 0.60s |
| Tune:         | +1 oct    | Unison :   | off             | Amplifier       |          |          |       |
|               | +10 cents | Voices:    | multi           | A               | 0        | S        | R     |
| Mix:          | Odb 100%  |            |                 | Os              | max      | 100%     | 0.35s |
| Osc 2 Track:  | on        |            |                 |                 |          |          |       |
| Osc 2 Sync:   | off       |            |                 |                 |          |          |       |
| Noise:        | off       |            |                 |                 |          |          |       |
| Mix :         | -         |            |                 |                 |          |          |       |

## **Mellow 70's Lead**

| Oscillator 1 |           | LFO        |       | Low-pass filter |            |            |       |
|--------------|-----------|------------|-------|-----------------|------------|------------|-------|
| Wave:        | Square    | Routing:   | -     |                 | 24db       | 12db       |       |
| Tune:        | -10 cents | Wave:      | -     | Cutoff:         | 20khz 100% | 20khz 100% |       |
|              |           | Frequency: | -     | Resonance:      | 0%         |            |       |
| Mix:         | Odb 100%  | Depth:     | -     | Envelope:       | 0%         |            |       |
| Oscillator 2 |           | Glide:     | on    | A               | 0          | S          | R     |
| Wave:        | Square    | time :     | 0.02s | -               | -          | -          | -     |
| Tune:        | +10 cents | Unison :   | off   | Amplifier       |            |            |       |
|              |           | Voices:    | mono  | A               | 0          | S          | R     |
| Mix :        | Odb 100%  |            |       | Os              | max        | 100%       | 0.35s |
| Osc 2 Track: | on        |            |       |                 |            |            |       |
| Osc 2 Sync:  | off       |            |       |                 |            |            |       |
| Noise:       | off       |            |       |                 |            |            |       |

## **Mono Solo**

| Oscillator 1 |          | LFO        |                   | Low-pass filter |          |          |  |
|--------------|----------|------------|-------------------|-----------------|----------|----------|--|
| Wave:        | PW =30%  | Routing:   | Pitch osc1, osc2  |                 | 24db     | 12db     |  |
| Tune:        | -        | Wave:      | Triangle / Sine   | Cutoff:         | 40hz 10% | 40hz 10% |  |
|              |          | Frequency: | 4.5 hz moderate   | Resonance:      | 45%      |          |  |
| Mix:         | Odb 100% | De<br>th:  | 22 cents moderate | Envelope:       | 80%      |          |  |
| Oscillator 2 |          | Glide:     | on                | A               | 0        | S        |  |
| Wave:        | PW =20%  | time:      | 0.04s very fast   | Os              | 0.20s    | 70%      |  |
| Tune:        | +4 cents | Unison:    | off               | Amplifier       |          |          |  |
|              |          | Voices:    | multi             | A               | 0        | S        |  |
| Mix:         | Odb 100% |            |                   | Os              | max      | 100%     |  |
| Osc 2 Track: | on       |            |                   |                 |          |          |  |
| Osc 2 S nc:  | off      |            |                   |                 |          |          |  |
| Noise:       | off      |            |                   |                 |          |          |  |
| Mix:         | -        |            |                   |                 |          |          |  |

N**ew** A~ge L**ea**d

| Oscillator 1 |          | LFO        |                 | Low-pass filter |            |            |       |
|--------------|----------|------------|-----------------|-----------------|------------|------------|-------|
| Wave:        | Square   | Routing:   | PW osc1, osc2   |                 | 24db       | 12db       |       |
| Tune:        | +5 cents | Wave:      | Triangle / Sine | Cutoff:         | 104khz 61% | 1.0khz 56% |       |
|              |          | Frequency: | 5.5 Hz          | Resonance:      | 65%        |            |       |
| Mix:         | Odb 100% | Depth :    | 45%             | Envelope:       | 75%        |            |       |
| Oscillator 2 |          | Glide:     | off             | A               | 0          | S          | R     |
| Wave:        | Square   | time:      | -               | Os              | 1.20s      | 20%        | 0.60s |
| Tune:        | -5 cents | Unison:    | off             | Amplifier       |            |            |       |
|              |          | Voices:    | multi           | A               | 0          | S          | R     |
| Mix:         | Odb 100% |            |                 | 0.05s           | max        | 100%       | 0.355 |
| Osc 2 Track: | on       |            |                 |                 |            |            |       |
| Osc 2 Sync:  | off      |            |                 |                 |            |            |       |
| Noise:       | off      |            |                 |                 |            |            |       |
| Mix:         | -        |            |                 |                 |            |            |       |

## **R&B Slide**

| Oscillator 1 |          | LFO              |                    | Low-pass filte     | er         |             |       |
|--------------|----------|------------------|--------------------|--------------------|------------|-------------|-------|
| Wave:        | Triangle | Routing:         | -                  |                    | 24db       | <u>12db</u> |       |
| Tune:        | +1 oct   | Wave:            | -                  | Cutoff:            | 1.9khz 66% | 1.9khz 66%  |       |
|              |          | Frequency:       | -                  | Resonance:         | 45%        |             |       |
| Mix:         | 0db 100% | Depth:           | -                  | Envelope:          | 65%        |             |       |
| Oscillator 2 |          | Glide:           | on                 | Α                  | D          | S           | R     |
| Wave:        | Triangle | time:            | 0.02s              | 1.20s              | max        | 100%        | 6.30s |
| Tune:        | +3 oct   | Unison:          | off                | Amplifier          |            |             |       |
|              |          | Voices:          | mono               | Α                  | D          | s           | R     |
| Mix:         | -6db 85% |                  |                    | 0.02s              | max        | 100%        | 0.60s |
| Osc 2 Track: | on       |                  |                    |                    |            |             |       |
| Osc 2 Sync:  | off      |                  |                    |                    |            |             |       |
| Noise:       | off      | 1                |                    |                    |            |             |       |
| Mix:         | -        | note: Play in th | he higher octaves. | Also try using lig | ght unison |             |       |

**Screaming Sync** 

|              | ing Sync     |            |                 |                |             |             |       |
|--------------|--------------|------------|-----------------|----------------|-------------|-------------|-------|
| Oscillator 1 |              | LFO        |                 | Low-pass filte |             |             |       |
| Wave:        | Any waveform | Routing:   | Pitch osc2      |                | <u>24db</u> | <u>12db</u> |       |
| Tune:        | -1 oct       | Wave:      | Triangle / Sine | Cutoff:        | 20khz 100%  | 20khz 100%  |       |
|              |              | Frequency: | 0.66 Hz         | Resonance:     | 0%          |             |       |
| Mix:         | -40db 0%     | Depth:     | 4.5cents medium | Envelope:      | 0%          |             |       |
| Oscillator 2 |              | Glide:     | on              | Α              | D           | s           | R     |
| Wave:        | Square       | time:      | 0.02s           | -              | -           | -           | -     |
| Tune:        |              | Unison:    | on              | Amplifier      |             |             |       |
|              |              | Voices:    | mono            | Α              | D           | s           | R     |
| Mix:         | 0db 100%     |            |                 | 0s             | max         | 100%        | 0.60s |
| Osc 2 Track: | on           |            |                 |                |             |             |       |
| Osc 2 Sync:  | on           |            |                 |                |             |             |       |
| Noise:       | off          | 1          |                 |                |             |             |       |

note: make sure oscillator 1 is on but its volume is all the way down

**Strings Pulse-Width Modulation**

| Oscillator<br>1 |           | LFO        |                                   | Low-pass filter |          |          |       |
|-----------------|-----------|------------|-----------------------------------|-----------------|----------|----------|-------|
| Wave:           | Square    | Routing:   | PW osc1,osc2                      |                 | 24db     | 12db     |       |
| Tune:           | -10 cents | Wave:      | Sine                              | Cutoff:         | 2khz 67% | 2khz 67% |       |
|                 |           | Frequency: | 2hz slow                          | Resonance:      | 0%       |          |       |
| Mix:            | Odb 100%  | Depth:     | 47%                               | Envelope:       | 100%     |          |       |
| Oscillator<br>2 |           | Glide:     | off                               | A               | 0        | S        | R     |
| Wave:           | Square    | time:      | -                                 | 0.09s           | max      | 100%     | max   |
| Tune:           | +10 cents | Unison:    | off                               | Amplifier       |          |          |       |
|                 |           | Voices :   | multi                             | A               | 0        | S        | R     |
| Mix:            | Odb 100%  |            |                                   | 0.11s           | max      | 100%     | 0.355 |
| Osc 2 Track :   | on        |            |                                   |                 |          |          |       |
| Osc 2 Sync:     | off       |            |                                   |                 |          |          |       |
| Noise:          | off       |            |                                   |                 |          |          |       |
| Mix:            | -         |            | notes: use thick chorus and delay |                 |          |          |       |

## **Trance 5th**

| Oscillator<br>1 |          | LFO        |                 | Low-pass filter |            |            |    |
|-----------------|----------|------------|-----------------|-----------------|------------|------------|----|
| Wave:           | Square   | Routing:   | PW osc1, osc2   |                 | 24db       | 12db       |    |
| Tune:           | -        | Wave:      | Triangle / Sine | Cutoff:         | 20khz 100% | 20khz 100% |    |
|                 |          | Frequency: | 6 Hz moderate   | Resonance :     | 0%         |            |    |
| Mix:            | Odb 100% | Depth:     | 80%             | Envelope:       | 0%         |            |    |
| Oscillator<br>2 |          | Glide:     | off             | A               | 0          | S          | R  |
| Wave:           | Square   | time:      | -               | -               | -          | -          | -  |
| Tune:           | +7 semi  | Unison:    | on              | Amplifier       |            |            |    |
|                 |          | Voices:    | mono            | A               | 0          | S          | R  |
| Mix:            | Odb 100% |            |                 | Os              | max        | 100%       | Os |
| Osc 2 Track :   | on       |            |                 |                 |            |            |    |
| Osc 2 Sync:     | off      |            |                 |                 |            |            |    |
| Noise:          | off      |            |                 |                 |            |            |    |
| Mix:            | -        |            |                 |                 |            |            |    |

# **BASS**

## **Acid Bass**

| Oscillator 1 |           | LFO              |                      | Low-pass filte     | er             |             |       |
|--------------|-----------|------------------|----------------------|--------------------|----------------|-------------|-------|
| Wave:        | PW = 25%  | Routing:         | -                    |                    | 24db           | <u>12db</u> |       |
| Tune:        | +10 cents | Wave:            | -                    | Cutoff:            | 450hz 45%      | 330hz 40%   |       |
|              |           | Frequency:       | -                    | Resonance:         | 60%            |             |       |
| Mix:         | -12db 70% | Depth:           | -                    | Envelope:          | 0%             |             |       |
| Oscillator 2 |           | Glide:           | off                  | Α                  | D              | s           | R     |
| Wave:        | Square    | time:            | -                    | 0s                 | -              | -           | -     |
| Tune:        | -2 oct    | Unison:          | off                  | Amplifier          |                |             |       |
|              | -10 cents | Voices:          | mono                 | Α -                | D <sub>.</sub> | S           | R     |
| Mix:         | 0db 100%  |                  |                      | 0s                 | 0.45s          | 15%         | 0.26s |
| Osc 2 Track: | on        |                  |                      |                    |                |             |       |
| Osc 2 Sync:  | off       | ,                |                      |                    |                |             |       |
| Noise:       | off       |                  |                      |                    |                |             |       |
| Mix:         | -         | note: turn filte | r cutoff knob during | g play for acid et | fect           |             |       |

## **Bass of the Time Lords**

| Oscillator 1 |          | LFO        |      | Low-pass filte | r        |             |       |
|--------------|----------|------------|------|----------------|----------|-------------|-------|
| Wave:        | PW = 30% | Routing:   | -    |                | 24db     | <u>12db</u> |       |
| Tune:        | -2 oct   | Wave:      | -    | Cutoff:        | 40hz 10% | 40hz 10%    |       |
|              |          | Frequency: | -    | Resonance:     | 0%       |             |       |
| Mix:         | 0db 100% | Depth:     | -    | Envelope:      | 85%      |             |       |
| Oscillator 2 |          | Glide:     | off  | Α              | D        | S           | R     |
| Wave:        | PW=30%   | time:      | -    | 0s             | 0.25s    | 25%         | 0.25s |
| Tune:        | -1 oct   | Unison:    | off  | Amplifier      |          | _           |       |
|              |          | Voices:    | mono | Α              | D        | s           | R     |
| Mix:         | 0db 100% |            | *    | 0s             | 0.65s    | 0%          | 0.70s |
| Osc 2 Track: | on       |            |      |                |          |             |       |
| Osc 2 Sync:  | off      |            |      |                |          |             |       |
| Noise:       | off      | 1          |      |                |          |             |       |

## **Detroit Bass**

| Oscillator 1  |          | LFO        |       | Low-pass filter |            |            |    |
|---------------|----------|------------|-------|-----------------|------------|------------|----|
| Wave :        | Square   | Routing:   | -     |                 | 24db       | 12db       |    |
| Tune:         | -1 oct   | Wave :     | -     | Cutoff:         | 20khz 100% | 20khz 100% |    |
|               |          | Frequency: | -     | Resonance:      | 0%         |            |    |
| Mix:          | Odb 100% | Depth:     | -     | Envelope:       | 0%         |            |    |
| Oscillator 2  |          | Glide:     | on    | A               | D          | S          | R  |
| Wave:         | Sawtooth | time:      | 0.01s | -               | -          | -          | -  |
| Tune :        | -2 oct   | Unison:    | off   | Amplifier       |            |            |    |
|               |          | Voices :   | mono  | A               | D          | S          | R  |
| Mix:          | Odb 100% |            |       | Os              | max        | 100%       | Os |
| Osc 2 Track : | on       |            |       |                 |            |            |    |
| Osc 2 Sync:   | off      |            |       |                 |            |            |    |
| Noise:        | off      |            |       |                 |            |            |    |
| Mix:          | -        |            |       |                 |            |            |    |

## **Deutsche Bass**

| Oscillator 1  |            | LFO        |      | Low-pass filter |           |           |       |
|---------------|------------|------------|------|-----------------|-----------|-----------|-------|
| Wave :        | PW=<br>25% | Routing :  | -    |                 | 24db      | 12db      |       |
| Tune :        | -2 oct     | Wave:      | -    | Cutoff:         | 800hz 53% | 500hz 46% |       |
|               |            | Frequency: | -    | Resonance:      | 35%       |           |       |
| Mix:          | Odb 100%   | Depth:     | -    | Envelope:       | 50%       |           |       |
| Oscillator 2  |            | Glide:     | off  | A               | D         | S         | R     |
| Wave :        | Sawtooth   | time:      | -    | Os              | 0.15s     | 0%        | 0.15s |
| Tune :        | -1 oct     | Unison:    | off  | Amplifier       |           |           |       |
|               | -3 semi    | Voices:    | mono | A               | D         | S         | R     |
| Mix:          | Odb 100%   |            |      | Os              | max       | 100%      | 0.15s |
| Osc 2 Track : | on         |            |      |                 |           |           |       |
| Osc 2 Sync:   | on         |            |      |                 |           |           |       |
| Noise:        | off        |            |      |                 |           |           |       |
| Mix:          | -          |            |      |                 |           |           |       |

**Digital Bass** 

| Oscillator 1 |          | LFO        |      | Low-pass filte | er        |             |       |
|--------------|----------|------------|------|----------------|-----------|-------------|-------|
| Wave:        | Square   | Routing:   | -    |                | 24db      | <u>12db</u> |       |
| Tune:        | -1 oct   | Wave:      | -    | Cutoff:        | 122hz 26% | 75hz 19%    |       |
|              |          | Frequency: | -    | Resonance:     | 0%        |             |       |
| Mix:         | -6db 85% | Depth:     | -    | Envelope:      | 100%      |             |       |
| Oscillator 2 |          | Glide:     | off  | Α              | D         | s           | R     |
| Wave:        | Sawtooth | time:      | -    | 0s             | 0.15s     | 0%          | 0s    |
| Tune:        | -2 oct   | Unison:    | off  | Amplifier      |           |             |       |
|              |          | Voices:    | mono | Α              | D         | S           | R     |
| Mix:         | 0db 100% |            |      | 0s             | max       | 100%        | 1.00s |
| Osc 2 Track: | on       |            |      |                |           |             |       |
| Osc 2 Sync:  | off      |            |      |                |           |             |       |
| Noise:       | off      |            |      |                |           |             |       |
| Mix:         | -        |            |      |                |           |             |       |

## **Funk Bass**

| Oscillator 1 |          | LFO        |       | Low-pass filte | r        |             |       |
|--------------|----------|------------|-------|----------------|----------|-------------|-------|
| Wave:        | Sawtooth | Routing:   |       |                | 24db     | <u>12db</u> |       |
| Tune:        | -2 oct   | Wave:      | -     | Cutoff:        | 40hz 10% | 40hz 10%    | 1     |
|              |          | Frequency: | -     | Resonance:     | 50%      |             |       |
| Mix:         | 0db 100% | Depth:     | -,    | Envelope:      | 85%      |             |       |
| Oscillator 2 |          | Glide:     | on    | . А            | D        | S           | R     |
| Wave:        | PW = 30% | time:      | 0.02s | 0.15s          | 0.10s    | 45%         | 0.08s |
| Tune:        | -1 oct   | Unison:    | off   | Amplifier      |          |             |       |
|              |          | Voices:    | mono  | Α              | D        | s           | R     |
| Mix:         | 0db 100% |            |       | 0s             | 0.29s    | 30%         | 0.40s |
| Osc 2 Track: | on .     |            |       |                |          |             |       |
| Osc 2 Sync:  | off      |            |       |                |          |             |       |
| Noise:       | off      |            |       |                |          |             |       |
| Mix:         | -        |            |       |                |          |             |       |

**Growling Bass**

| Oscillator 1 |          | LFO        |      | Low-pass filter |           |          |       |
|--------------|----------|------------|------|-----------------|-----------|----------|-------|
| Wave:        | Square   | Routing:   | -    |                 | 24db      | 12db     |       |
| Tune:        | -2 oct   | Wave:      | -    | Cutoff:         | 122hz 26% | 75hz 19% |       |
|              |          | Frequency: | -    | Resonance:      | 0%        |          |       |
| Mix:         | Odb 100% | Depth:     | -    | Envelope:       | 100%      |          |       |
| Oscillator 2 |          | Glide:     | Off  | A               | D         | S        | R     |
| Wave:        | Sawtooth | time:      | -    | Os              | 0.50s     | 20%      | 0.60s |
| Tune:        | -9 semi  | Unison:    | Off  | Amplifier       |           |          |       |
|              |          | Voices:    | Mono | A               | D         | S        | R     |
| Mix:         | Odb 100% |            |      | Os              | max       | 100%     | 0.60s |
| Osc 2 Track: | on       |            |      |                 |           |          |       |
| Osc 2 Sync:  | off      |            |      |                 |           |          |       |
| Noise:       | off      |            |      |                 |           |          |       |
| Mix:         | -        |            |      |                 |           |          |       |

## **Rez Bass**

| Oscillator 1 |          | LFO        |                   | Low-pass filter |            |            |       |
|--------------|----------|------------|-------------------|-----------------|------------|------------|-------|
| Wave:        | Square   | Rout ing : | Pitch osc2        |                 | 24db       | 12db       |       |
| Tu ne:       | -2 oct   | Wave:      | Triangle I Sine   | Cutoff:         | 6.5khz 84% | 6.5khz 84% |       |
|              |          | Frequency: | 10 hz fast        | Resonance:      | 50%        |            |       |
| Mix:         | Odb 100% | Depth:     | 30 cents shallo w | Envelope:       | 0%         |            |       |
| Oscillator 2 |          | Glide:     | off               | A               | D          | S          | R     |
| Wave:        | Square   | time:      | 0.085             | -               | -          | -          | -     |
| Tune:        | -2 oct   | Unison:    | off               | Amplifier       |            |            |       |
|              |          | Voices:    | mono              | A               | D          | S          | R     |
| Mix:         | Odb 100% |            |                   | Os              | max        | 100%       | 0.10s |
| Osc 2 Track: | on       |            |                   |                 |            |            |       |
| Osc 2 Sync:  | on       |            |                   |                 |            |            |       |
| Noise:       | off      |            |                   |                 |            |            |       |
| Mix :        | -        |            |                   |                 |            |            |       |

# **PADS**

## **Android Dreams**

| Oscillator 1 |           | LFO             |                     | Low-pass fil     | ter             |                   |        |
|--------------|-----------|-----------------|---------------------|------------------|-----------------|-------------------|--------|
| Wave:        | Square    | Routing:        | *see note           |                  | 24db            | <u>12db</u>       |        |
| Tune:        | -2 oct    | Wave:           | Triangle / Sine     | Cutoff:          | 2.4khz 69%      | 1.7khz 64%        |        |
|              |           | Frequency:      | 0.25 hz very slow   | Resonance:       | 30%             |                   |        |
| Mix:         | 0db 100%  | Depth:          | *see note           | Envelope:        | 0%              |                   |        |
| Oscillator 2 |           | Glide:          | off                 | Α                | D               | S                 | R      |
| Wave:        | Sawtooth  | time:           | -                   | -                | -               | -                 | - '    |
| Tune:        | -1 semi   | Unison:         | off                 | Amplifier        |                 |                   |        |
|              |           | Voices:         | multi               | Α                | D               | S                 | R      |
| Mix:         | 0db 100%  |                 |                     | 0.45s            | max             | 100%              | 2.25s  |
| Osc 2 Track: | on .      |                 |                     |                  |                 |                   |        |
| Osc 2 Sync:  | on        |                 |                     |                  |                 |                   |        |
| Noise:       | on        | *note: multiple | e LFO routings with | their respective | e depths: PW os | sc1&2 45%, filter | cutoff |
| Mix:         | -6 db 90% | 10%, pitch os   | sc2 3-semitones     |                  |                 |                   |        |

## **Celestial Wash**

| Oscillator 1 |           | LFO              |                      | Low-pass filte     | r        |             |       |
|--------------|-----------|------------------|----------------------|--------------------|----------|-------------|-------|
| Wave:        | -         | Routing:         | Resonance            |                    | 24db     | <u>12db</u> |       |
| Tune:        | -         | Wave:            | Square               | Cutoff:            | 1khz 57% | 500hz 46%   |       |
|              |           | Frequency:       | 5.5 hz moderate      | Resonance:         | 100%     |             |       |
| Mix:         | -         | Depth:           | 100%                 | Envelope:          | 0%       |             |       |
| Oscillator 2 | ,         | Glide:           | off                  | Α                  | D        | s           | R     |
| Wave:        | -         | time:            | -                    | -                  | -        |             | -     |
| Tune:        | -         | Unison:          | off                  | Amplifier          |          |             |       |
|              |           | Voices:          | multi                | Α                  | D        | S           | R     |
| Mix:         | -         | (8)              |                      | 1.65s              | 5.85s    | 0%          | 4.40s |
| Osc 2 Track: | -         |                  |                      |                    |          |             |       |
| Osc 2 Sync:  | -         |                  |                      |                    |          |             | ÷     |
| Noise:       | on        |                  |                      |                    |          |             |       |
| Mix:         | 0 dB 100% | note: turn filte | r's keyboard trackir | ng on if available |          |             |       |

D**ark COtICy**

| Oscillator 1 |             | LFO        |                 | Low-pass filter |           |           |       |
|--------------|-------------|------------|-----------------|-----------------|-----------|-----------|-------|
| Wave:        | Square      | Routing:   | PW osc1 , osc2  |                 | 24db      | 12db      |       |
| Tune:        | -2 oct      | Wave:      | Triangle I Sine | Cutoff:         | 300hz 39% | 200hz 33% |       |
|              |             | Frequency: | 4 Hz moderate   | Resonance:      | 0%        |           |       |
| Mix :        | odb<br>100% | Depth :    | 45%             | Envelope:       | 75%       |           |       |
| Oscillator 2 |             | Glide:     | off             | A               | 0         | 5         | R     |
| Wave:        | Sawtooth    | time:      | -               | 5.15s           | 6.35s     | 50%       | 5.20s |
| Tune:        | -11 semi    | Unison:    | off             | Amplifier       |           |           |       |
|              | -92 cents   | Voices:    | multi           | A               | 0         | 5         | R     |
| Mix:         | odb<br>100% |            |                 | Os              | 3.90s     | 70%       | 6.35s |
| Osc 2 Track: | on          |            |                 |                 |           |           |       |
| Osc 2 Sync:  | off         |            |                 |                 |           |           |       |
| Noise:       | off         |            |                 |                 |           |           |       |
| Mix :        | -           |            |                 |                 |           |           |       |

## **Aurora**

Noise: off Mix: -

| Oscillator 1  |           | LFO        |                 | Low-pass filter |          |          |       |
|---------------|-----------|------------|-----------------|-----------------|----------|----------|-------|
| Wave:         | Square    | Routing:   | PW osc1 , osc2  |                 | 24db     | 12db     |       |
| Tune:         | +10 cents | Wave:      | Triangle I Sine | Cutoff:         | 40hz 10% | 40hz 10% |       |
|               |           | Frequency: | 4 Hz moderate   | Resonance:      | 65%      |          |       |
| Mix:          | Odb 100%  | Depth:     | 40%             | Envelope:       | 50%      |          |       |
| Oscillator 2  |           | Glide:     | off             | A               | 0        | 5        | R     |
| Wave:         | Square    | time:      | -               | 1.50s           | max      | 100%     | 0.60s |
| Tune:         | -10 cents | Unison:    | off             | Amplifier       |          |          |       |
|               |           | Voices:    | multi           | A               | 0        | 5        | R     |
| Mix:          | Odb 100%  |            |                 | 0.60s           | max      | 100%     | 0.60s |
| ·Osc 2 Track: | on        |            |                 |                 |          |          |       |
| Osc 2 Sync:   | off       |            |                 |                 |          |          |       |

## **Galactic Cathedral**

| cillator 1  |             | LFO        |                  | Low-pass filter |            |           |       |
|-------------|-------------|------------|------------------|-----------------|------------|-----------|-------|
| Wave :      | Square      | Routing:   | Filter cutoff    |                 | 24db       | 12db      |       |
| Tune :      | -11 cents   | Wave:      | Triangle I Sine  | Cutoff:         | 1.2khz 59% | 700hz 51% |       |
|             |             | Frequency: | 0.3 hz very slow | Resonance:      | 60%        |           |       |
| Mix:        | odb<br>100% | Depth:     | 10%              | Envelope:       | 0%         |           |       |
| cillator 2  |             | Glide:     | off              | A               | D          | S         | R     |
| Wave:       | Square      | time:      | -                | -               | -          | -         | -     |
| Tune :      | +2 oct      | Unison:    | off              | Amplifier       |            |           |       |
|             | +11 cents   | Voices :   | multi            | A               | D          | S         | R     |
| Mix:        | -6 db 85%   |            |                  | OAOs            | max        | 100%      | 2.25s |
| c 2 Track:  | on          |            |                  |                 |            |           |       |
| Osc 2 Sync: | off         |            |                  |                 |            |           |       |
| Noise:      | off         |            |                  |                 |            |           |       |
| Mix:        | -           |            |                  |                 |            |           |       |

**Galactic Chapel**

Noise: off Mix: -

| cillator 1   |             | LFO        |                     | Low-pass filter |            |          |       |
|--------------|-------------|------------|---------------------|-----------------|------------|----------|-------|
| Wave:        | Triangle    | Routing:   | Cutoff &Amp         |                 | 24db       | 12db     |       |
| Tune:        | -           | Wave :     | Triangle I Sine     | Cutoff:         | 104khz 61% | 1khz 57% |       |
|              |             | Frequency: | 0.3 hz very slow    | Resonance:      | 65%        |          |       |
| Mix:         | odb<br>100% | Depth:     | cutoff 10%, amp 17% | Envelope:       | 0%         |          |       |
| Oscillator 2 |             | Glide:     | off                 | A               | D          | S        | R     |
| Wave :       | Triangle    | time:      | -                   | -               | -          | -        | -     |
| Tune :       | +1 oct      | Unison:    | off                 | Amplifier       |            |          |       |
|              |             | Voices:    | multi               | A               | D          | S        | R     |
| Mix:         | -6 db 85%   |            |                     | 0.35s           | max        | 100%     | 2.25s |
| sc 2 Track : | on          |            |                     |                 |            |          |       |
| Osc 2 Sync:  | off         |            |                     |                 |            |          |       |

## **Portus**

| Oscillator 1 |          | LFO        |       | Low-pass filte | r        |             |       |
|--------------|----------|------------|-------|----------------|----------|-------------|-------|
| Wave:        | Triangle | Routing:   | -     |                | 24db     | <u>12db</u> |       |
| Tune:        | -        | Wave:      | -     | Cutoff:        | 75hz 19% | 75hz 19%    |       |
| 1            |          | Frequency: | -     | Resonance:     | 70%      |             |       |
| Mix:         | 0db 100% | Depth:     | -     | Envelope:      | 70%      |             |       |
| Oscillator 2 |          | Glide:     | on    | Α              | D        | s           | R     |
| Wave:        | Triangle | time:      | 1.5s  | 1.80s          | max      | 100%        | 2.90s |
| Tune:        | +1 oct   | Unison:    | off   | Amplifier      |          |             |       |
|              |          | Voices:    | multi | Α              | D        | S           | R     |
| Mix:         | 0db 100% |            |       | 1.50s          | max      | 100%        | 3.30s |
| Osc 2 Track: | on       |            |       |                |          |             |       |
| Osc 2 Sync:  | off      |            |       |                |          |             |       |
| Noise:       | off      |            |       |                |          |             |       |
| Mix:         | -        |            |       |                |          |             |       |

Post-Apocalyptic Sync Sweep

| Oscillator 1 |          | LFO        |                   | Low-pass filte | r           |             |       |
|--------------|----------|------------|-------------------|----------------|-------------|-------------|-------|
| Wave:        | Square   | Routing:   | Pitch osc2        |                | <u>24db</u> | <u>12db</u> |       |
| Tune:        | -2 oct   | Wave:      | Triangle / Sine   | Cutoff:        | 40hz 10%    | 40hz 10%    |       |
|              |          | Frequency: | 0.7 hz very slow  | Resonance:     | 65%         |             |       |
| Mix:         | 0db 100% | Depth:     | 4.5 semi moderate | Envelope:      | 50%         |             |       |
| Oscillator 2 |          | Glide:     | off               | Α              | D           | S           | R     |
| Wave:        | Square   | time:      | -                 | 2.10s          | 5.20s       | 0%          | 3.00s |
| Tune:        | -1 oct   | Unison:    | off               | Amplifier      |             |             |       |
|              |          | Voices:    | multi             | Α              | D           | S           | R     |
| Mix:         | -6db 85% |            |                   | 0s             | max         | 100%        | 0.60s |
| Osc 2 Track: | on       |            |                   |                |             |             |       |
| Osc 2 Sync:  | on       |            |                   |                |             |             |       |
| Noise:       | off      |            |                   |                |             |             |       |

## **Terra Enceladus**

| Oscillator 1 |          | LFO        |                 | Low-pass filter |            |           |       |
|--------------|----------|------------|-----------------|-----------------|------------|-----------|-------|
| Wave:        | Sawtooth | Routing:   | PWosc2          |                 | 24db       | 12db      |       |
| Tune:        | -        | Wave:      | Triangle I Sine | Cutoff:         | 1.3khz 60% | 600hz 49% |       |
|              |          | Frequency: | 1.75hz slow     | Resonance:      | 0%         |           |       |
| Mix:         | Odb 100% | Depth :    | 45%             | Envelope:       | 0%         |           |       |
| Oscillator 2 |          | Glide:     | off             | A               | D          | S         | R     |
| Wave:        | Square   | time:      | -               | -               | -          | -         | -     |
| Tune:        | -1 oct   | Unison:    | off             | Amplifier       |            |           |       |
|              |          | Voices:    | multi           | A               | D          | S         | R     |
| Mix:         | -3db 90% |            |                 | 0.40s           | max        | 100%      | 2.25s |
| Osc 2 Track: | on       |            |                 |                 |            |           |       |
| Osc 2 Sync : | off      |            |                 |                 |            |           |       |
| Noise:       | off      |            |                 |                 |            |           |       |

## Cat

| Oscillator 1 |           | LFO        |            | Low-pass filte | r           |             |       |
|--------------|-----------|------------|------------|----------------|-------------|-------------|-------|
| Wave:        | PW = 10%  | Routing:   | Pitch      |                | <u>24db</u> | <u>12db</u> |       |
| Tune:        | +1 octave | Wave:      | Sine Wave  | Cutoff:        | 270hz 37%   | 160hz 30%   |       |
|              | +5 semi   | Frequency: | 1.7hz slow | Resonance:     | 65%         |             |       |
| Mix:         | 0db 100%  | Depth:     | 11 cents   | Envelope:      | 65%         |             |       |
| Oscillator 2 |           | Glide:     | off        | Α              | D           | S           | R     |
| Wave:        | PW = 5%   | time:      | -          | 0.57s          | 1.90s       | 55%         | 0.29s |
| Tune:        | -         | Unison:    | off        | Amplifier      |             |             |       |
|              |           | Voices:    | multi      | Α              | D           | s           | R     |
| Mix:         | 0db 100%  |            |            | 0.51s          | 1.05s       | 55%         | 0.93s |
| Osc 2 Track: | on        |            |            |                |             |             |       |
| Osc 2 Sync:  | off       |            |            |                |             |             |       |
| Noise:       | off       |            |            |                |             |             |       |
| Mix:         | -         |            | ŕ          |                |             |             |       |

**Digital Alarm Clock** 

| 0            |          | 1.50       |           | T              |             |             |    |
|--------------|----------|------------|-----------|----------------|-------------|-------------|----|
| Oscillator 1 |          | LFO        |           | Low-pass filte | r           |             |    |
| Wave:        | PW = 5%  | Routing:   | Amplitude |                | <u>24db</u> | <u>12db</u> |    |
| Tune:        | -        | Wave:      | square    | Cutoff:        | 9.5khz 89%  | 5.7khz 82%  |    |
|              |          | Frequency: | 2hz slow  | Resonance:     | 0%          |             |    |
| Mix:         | 0db 100% | Depth:     | 100%      | Envelope:      | 40%         |             |    |
| Oscillator 2 |          | Glide:     | off       | Α              | D           | S           | R  |
| Wave:        | Sawtooth | time:      | -         | -              | -           | -           | _  |
| Tune:        | -        | Unison:    | off       | Amplifier      |             |             |    |
|              |          | Voices:    | multi     | Α              | D           | S           | R  |
| Mix:         | 0db 100% |            |           | 0s             | max         | 100%        | 0s |
| Osc 2 Track: | on       |            |           |                |             |             |    |
| Osc 2 Sync:  | off      |            |           |                |             |             |    |
|              |          | 1          |           |                |             |             |    |

**Journey to the Core**

| Oscillator 1 |          | LFO        |                                                   | Low-pass filter |                 |             |       |
|--------------|----------|------------|---------------------------------------------------|-----------------|-----------------|-------------|-------|
| Wave:        | Sawtooth | Routing :  | *see note                                         |                 | 24db            | 12db        |       |
| Tune:        | -2 oct   | Wave :     | Sawtooth                                          | Cutoff:         | 120hz 26%       | 120hz 26%   |       |
|              |          | Frequency: | 7.5hz<br>moderate                                 | Resonance:      | 45%             |             |       |
| Mix:         | Odb 100% | Depth:     | *see note                                         | Envelope :      | 100%            |             |       |
| Oscillator 2 |          | Glide:     | off                                               | A               | 0               | 5           | R     |
| Wave:        | Square   | time:      | -                                                 | 3.30s           | 3.20s           | 0%          | 3.20s |
| Tune :       | -1 oct   | Unison:    | off                                               | Amplifier       |                 |             |       |
|              | ,        | Voices:    | multi                                             | A               | 0               | 5           | R     |
| Mix:         | Odb 100% |            |                                                   | Os              | max             | 100%        | 0.805 |
| Osc 2 Track: | on       |            |                                                   |                 |                 |             |       |
| Osc 2 Sync:  | -        |            |                                                   |                 |                 |             |       |
| Noise:       | off      |            |                                                   |                 |                 |             |       |
| Mix:         | -        |            | *note: LFO routing and depth - Pitch osc1, osc2 = |                 | 7 semitones; PW | osc2 = 100% |       |

## **Kazoo**

| Oscillator 1 |          | LFO        |                                                              | Low-pass filter |            |           |       |
|--------------|----------|------------|--------------------------------------------------------------|-----------------|------------|-----------|-------|
| Wave:        | PW=15%   | Routing:   | Pitch                                                        |                 | 24db       | 12db      |       |
| Tune:        | -        | Wave:      | Noise or Saw                                                 | Cutoff:         | 1.2khz 59% | 600hz 49% |       |
|              |          | Frequency: | 32hz<br>very fast                                            | Resonance:      | 30%        |           |       |
| Mix:         | Odb 100% | Depth:     | 70 cents deep                                                | Envelope :      | 50%        |           |       |
| Oscillator 2 |          | Glide:     | off                                                          | A               | 0          | 5         | R     |
| Wave:        | PW=2%    | time:      | -                                                            | 0.06s           | 1.20s      | 0%        | 0.635 |
| Tune:        | -        | Unison:    | off                                                          | Amplifier       |            |           |       |
|              |          | Voices:    | mono                                                         | A               | 0          | 5         | R     |
| Mix:         | Odb 100% |            |                                                              | 0.03s           | 3.9s       | 0%        | 0.335 |
| Osc 2 Track: | on       |            |                                                              |                 |            |           |       |
| Osc 2 Sync:  | off      |            |                                                              |                 |            |           |       |
| Noise:       | off      |            |                                                              |                 |            |           |       |
| Mix:         | -        | note: If   | available, use noise for the LFO wave source otherwise use a |                 |            | sawtooth  |       |

## **Laser**

| :Oscillator 1 |             | LFO        |      | Low-pass filter |          |          |       |
|---------------|-------------|------------|------|-----------------|----------|----------|-------|
| Wave:         | -           | Routing:   | -    |                 | 24db     | 12db     |       |
| Tune:         | -           | Wave:      | -    | Cutoff:         | 40hz 10% | 40hz 10% |       |
|               |             | Frequency: | -    | Resonance:      | 100%     |          |       |
| Mix:          | -           | Depth :    | -    | Envelope:       | 100%     |          |       |
| Oscillator 2  |             | Glide :    | off  | A               | D        | S        | R     |
| Wave:         | -           | time :     | -    | Os              | 0.38s    | 0%       | 0.25s |
| Tune:         | -           | Unison:    | off  | Amplifier       |          |          |       |
|               |             | Voices:    | mono | A               | D        | S        | R     |
| Mix :         | -           |            |      | Os              | 0.45s    | 0%       | 0.30s |
| Osc 2 Track:  | -           |            |      |                 |          |          |       |
| Osc 2 Sync :  | -           |            |      |                 |          |          |       |
| Noise:        | on          |            |      |                 |          |          |       |
| Mix:          | odb<br>100% |            |      |                 |          |          |       |

## **Motor**

| Oscillator 1 |              | LFO        |                   | Low-pass filter |            |            |       |
|--------------|--------------|------------|-------------------|-----------------|------------|------------|-------|
| Wave:        | PW=25%       | Routing:   | Amplitude         |                 | 24db       | 12db       |       |
| Tune:        | -2 octaves   | Wave:      | Square            | Cutoff:         | 20khz 100% | 20khz 100% |       |
|              |              | Frequency: | 32hz<br>very fast | Resonance:      | 0%         |            |       |
| Mix:         | Odb 100%     | Depth :    | 40%               | Envelope:       | 0%         |            |       |
| Oscillator 2 |              | Glide:     | on                | A               | D          | S          | R     |
| Wave:        | PW=25%       | time :     | 1.3s long         | -               | -          | -          | -     |
| Tune:        | -1 octave    | Unison:    | off               | Amplifier       |            |            |       |
|              |              | Voices:    | mono              | A               | D          | S          | R     |
| Mix :        | -14 .3db 65% |            |                   | Os              | max        | 100%       | 0.60s |
| Osc 2 Track: | on           |            |                   |                 |            |            |       |
| Osc 2 Sync : | off          |            |                   |                 |            |            |       |
| Noise:       | off          |            |                   |                 |            |            |       |

Mix: - note: having the glide on is very important for this patch to sound right!

## **Nerd-O-Tron 2000**

| Oscillator 1 |            | LFO        |                    | Low-pass filter |           |           |       |
|--------------|------------|------------|--------------------|-----------------|-----------|-----------|-------|
| Wave:        | Sawtooth   | Routing:   | Filter cutoff      |                 | 24db      | 12db      |       |
| Tune:        | -          | .Wave:     | Noise              | Cutoff:         | 680hz 51% | 680hz 51% |       |
|              |            | Frequency: | very slow<br>0.9hz | Resonance:      | 85%       |           |       |
| Mix:         | Odb 100%   | Depth:     | 25%                | Envelope:       | 0%        |           |       |
| Oscillator 2 |            | Glide:     | off                | A               | D         | S         | R     |
| Wave:        | Square     | time:      | -                  | -               | -         | -         | -     |
| Tu ne:       | +2 octaves | Unison:    | off                | Amplifier       |           |           |       |
|              |            | Voices:    | multi              | A               | D         | S         | R     |
| Mix:         | Odb 100%   |            |                    | Os              | max       | 100%      | 2.005 |
| Osc 2 Track: | on         |            |                    |                 |           |           |       |
| Osc 2 Sync:  | -          |            |                    |                 |           |           |       |
| Noise:       | off        |            |                    |                 |           |           |       |
| Mix :        | -          |            |                    |                 |           |           |       |

o**cean aves** w **(WI**lth **f09**h**orn**)

| Oscillator 1 |             | LFO        | Low-pass filter                    |                             |            |                     |       |
|--------------|-------------|------------|------------------------------------|-----------------------------|------------|---------------------|-------|
| Wave:        | -           | Routing:   | Amp osc1 , noise                   |                             | 24db       | 12db                |       |
| Tune:        | -           | Wave:      | Triangle                           | Cutoff:                     | 4.3khz 78% | 2.0khz 67%          |       |
|              |             | Frequency: | very slow<br>0.2hz                 | Resonance:                  | 30%        |                     |       |
| Mix:         | -           | Depth:     | 75%                                | Envelope:                   | 0%         |                     |       |
| Oscillator 2 |             | Glide:     | Off                                | A                           | D          | S                   | R     |
| Wave:        | -           | time:      | -                                  | -                           | -          | -                   | -     |
| Tune:        | -           | Unison :   | off                                | Amplifier                   |            |                     |       |
|              |             | Voices:    | mult i                             | A                           | D          | S                   | R     |
| Mix:         | -           |            |                                    | 0.40s                       | max        | 100%                | 1.00s |
| Osc 2 Track: | -           |            |                                    |                             |            |                     |       |
| Osc 2 Sync:  | -           |            |                                    |                             |            |                     |       |
| Noise:       | on          |            |                                    |                             |            |                     |       |
| Mix:         | odb<br>100% |            | note: for foghorn set oscillator 1 | to Wave: Sawtooth, Tune: -1 |            | oct, Mix: 0 db 100% |       |

## . -..: EFFE

**onic Rh thm**

| , 1   |             | LFO        |                                                   | Low-pass   |         |                           |       |
|-------|-------------|------------|---------------------------------------------------|------------|---------|---------------------------|-------|
| .~    | Sawtooth    | Routing:   | *see note                                         |            | 2_<br>_ |                           |       |
| e :   | -2 oct      | Wave:      | Square                                            | Cutoff:    | 165hz   |                           |       |
|       |             | Frequency: | 4 hz moderate                                     | Resonance: | 45%     |                           |       |
|       | odb<br>100% | De th:     | *see note                                         | Envelope:  | 100%    |                           |       |
| 2     |             | Glide:     | off                                               | A          | D       | S                         |       |
| .ale: | Square      | time:      | -                                                 | 3.30s      | 4.00s   | 0%                        | 2.905 |
| _ e:  | -1 oct      | Unison:    | off                                               | Amplifier  |         |                           |       |
|       |             | Voices:    | multi                                             | A          | D       | S                         | R     |
|       | odb<br>100% |            |                                                   | Os         | max     | 100%                      | 0.80s |
|       | on          |            |                                                   |            |         |                           |       |
|       | off         |            |                                                   |            |         |                           |       |
|       | off         |            |                                                   |            |         |                           |       |
|       |             |            | *note: LFO routing and depth - Pitch osc1, osc2 = |            |         | 7 semitones; PWosc2 =100% |       |

## **Bpace Attack!**

| lator 1         |             | LFO             |                                                          | Low-pass filter |            |            |       |
|-----------------|-------------|-----------------|----------------------------------------------------------|-----------------|------------|------------|-------|
| Wave:           | Square      | Routing:        | Pitch osc1 , osc2                                        |                 | 24db       | 12db       |       |
| Tune:           | -1 oct      | Wave:           | Sawtooth                                                 | Cutoff:         | 20khz 100% | 20khz 100% |       |
|                 |             | Frequency:      | 2.5hz<br>moderate                                        | Resonance:      | 0%         |            |       |
| Mix:            | odb<br>100% | Depth:          | 1 oct deep                                               | Envelope:       | 0%         |            |       |
| Oscillator 2    |             | Glide:          | Off                                                      | A               | D          | S          | R     |
| Wave:           | Sawtooth    | time:           | -                                                        | -               | -          | -          | -     |
| Tune:           | -1 oct      | . Unison:       | off                                                      | Amplifier       |            |            |       |
|                 |             | Voices:         | mono                                                     | A               | D          | S          | R     |
| Mix:            | odb<br>100% |                 |                                                          | Os              | max        | 100%       | 2.00s |
| Osc<br>2 Track: | on          |                 |                                                          |                 |            |            |       |
| Osc 2 Sync:     | off         |                 |                                                          |                 |            |            |       |
| Noise:          | off         | note: if Z'dLFO | is available set it up as Routing: Amplitude osct, osc2, |                 |            |            |       |
| Mix:            | -           |                 | Wave: Sawtooth, Frequency: 15 hz (fast), Depth: 100%     |                 |            |            |       |

# Toad

| Oscillator 1 |            | LFO        |                | Low-pass filte | r           |             |       |
|--------------|------------|------------|----------------|----------------|-------------|-------------|-------|
| Wave:        | Triangle   | Routing:   | Amplitude      |                | <u>24db</u> | <u>12db</u> |       |
| Tune:        | +1 octave  | Wave:      | Triangle       | Cutoff:        | 40hz 10%    | 40hz 10%    |       |
|              |            | Frequency: | 32hz very fast | Resonance:     | 0%          |             |       |
| Mix:         | 0db 100%   | Depth:     | 100%           | Envelope:      | 0%          |             |       |
| Oscillator 2 |            | Glide:     | on             | Α              | D           | S           | R     |
| Wave:        | Square     | time:      | 1.3s long      | -              | -           | -           | -     |
| Tune:        | -2 octaves | Unison:    | off            | Amplifier      |             |             |       |
|              |            | Voices:    | multi          | Α              | D           | S           | R     |
| Mix:         | 0db 100%   |            |                | 0.09s          | 0.23s       | 0%          | 0.23s |
| Osc 2 Track: | on         |            |                |                | ,           |             |       |
| Osc 2 Sync:  | -          |            |                |                |             |             |       |
| Noise:       | off        |            |                |                |             |             |       |
| Mix:         | -          |            |                |                |             |             |       |

## Wind

| Oscillator 1 |           | LFO        |                 | Low-pass filt | er          |             |       |
|--------------|-----------|------------|-----------------|---------------|-------------|-------------|-------|
| Wave:        | -         | Routing:   | Noise amplitude |               | <u>24db</u> | <u>12db</u> |       |
| Tune:        | -         | Wave:      | Noise           | Cutoff:       | 780hz 53%   | 780hz 53%   |       |
|              |           | Frequency: | 0.7hz very slow | Resonance:    | 75%         |             |       |
| Mix:         | -         | Depth:     | 40%             | Envelope:     | 0%          |             |       |
| Oscillator 2 |           | Glide:     | Off             | Α             | D           | s           | R     |
| Wave:        |           | time:      | -               | -             |             |             |       |
| Tune:        | -         | Unison:    | off             | Amplifier     |             |             |       |
| ·            |           | Voices:    | multi           | Α             | D           | s           | R     |
| Mix:         | -         |            |                 | 0.40s         | max         | 100%        | 2.70s |
| Osc 2 Track: | -         |            |                 |               |             |             |       |
| Osc 2 Sync:  | -         |            |                 |               |             |             |       |
| Noise:       | on        |            |                 |               |             |             |       |
| Mix:         | 0 db 100% |            |                 |               |             |             |       |

This section is intended for those synthesizers that do not give the values oftheir settings in decibels, hertz, or seconds. By first calibrating such a synthesizer the patches in this book can programmed much more accurately than using the suggested percentage settings that are ::"ven in italics. It is advisable to at the very least calibrate the oscillator mix and filter cutoff frequency. There are two parts to this section. The first part explains how to calibrate a synth <sup>I</sup> sing the sound files on the CD and the second part explains how to using a sound editor and other metering devices. Using the CD is probably the quickest way to get started while using the directions in the second part will produce slightly more accurate results.

The most optimal way to use these two sections is probably to use the CD to calibrate the filter's cutoff frequency and if you can record your synth into a sound editor then use Part B to determine oscillator mix levels, LFO frequency and ADSR values. If you would like more clarification on any part ofthis section please feel free to email *meatfred\_v\_welsh@yahoo.com*

## **Part A - Using the CD**

Using the sounds files on the CD is quite simple. In a nutshell you are basically just comparing the output of your synth to each file and figuring out values such as decibels, Hz, and seconds from the filename ofthe sound that most closely matches what you hear from your synth.

#### **Oscillator Mix:**

- A. Get a piece of paper and a pencil or pen.
- B. Go into the *Oscillator Mix* folder on the CD. Although the filter isn't being calibrated at this point it is still important to use samples that correspond to the synth's filter type. Open the folder that corresponds to the filter type used by your synth. If both filter types are available then you can just pick one but of course make sure the synth is set to that filter.
- C. Now you should see two folders. We are going to use the *Dual Sawtooth Waveforms* folder. The *Dual Sawtooth Waveforms* folder contains samples where both oscillators are set to sawtooth and one is raised two octaves. Set your synthesizer up

- with both oscillators set to sawtooth, one raised two octaves. The purpose ofthis is so that the amplitude of one oscillator can be compared to the other
- D. In each one ofthese samples the high-pitch oscillator is left at its maximum setting. This maximum setting corresponds to 0 dB. The name of each file indicates the amplitude ofthe low-pitch oscillator. On your synth, tum the amplitude of both sawtooths all the way up. It should now produce the same tonal characteristics as the odB file when you play middle C on the keyboard. Also make sure your filter is completely open and that amplitude velocity sensitivity is off.
- E. Write down the number, dial position, or whatever your synth uses that corresponds to the maximum setting and next to it write down "0 dB." Make sure to write neatly because you are going to be using these values to patch the sounds in this book.
- F. Listen to the tonal characteristics ofthe -5 dB file. Now lower the amplitude of your low-pitch oscillator until it produces the same tonal characteristics as the -5 dB file. Write down the position followed by "-5 dB."
- G. Continue to do the same thing for each ofthe remaining sound files

The *"Single Sawtooth Waveform"* folder contains samples of a single sawtooth oscillator which just like in the instructions above is lowered in 5 dB increments. This is just an alternative to the Dual Sawtooth instructions above and is carried out in the exact same way.

#### **Filter**

*Determining Filter Type*

If you already know whether your filter is ofthe 12 dB or 24 dB variety then you can skip this section and proceed to the *Determining Filter Cutoff*section.

A. Open the *"Filter"* folder and then open the *"Determine Filter Type"* folder. There are four files in here. For each set (12 dB or 24 dB) there is a file where the filter resonance is set to a pitch of 440 Hz and after about ten seconds the resonance is turned all the way down. There are also two files where the filter is completely open at 20,000 Hz and resonance is set to zero. Play both ofthese files and you'll notice that the 12 dB filter produces a slightly brighter sound. That's because a filter that is "open" isn't completely open! It will still have some effect on the tone.

- B. Set your synth up so that it produces a single sawtooth waveform. Turn your filter resonance all the way up. Ifit distorts then turn it down some.
- C. While playing A440 (the A below mid-C) on your keyboard, lower the filter cutoff frequency until it matches the resonant pitch at the beginning of either one ofthese sound files.
- D. Tum the resonance all the way down so that you only hear the filtered sawtooth. Compare the tonal characteristics that you hear to those in the second half of each of the 12 dB and 24 db *"filter at 440 Hz "* files.
- E. Whichever file sounds the same indicates whether you have a 12 dB or 24 dB filter.

#### *Determining Filter Cutoff*

- A. Open the *"Filter "* folder and then open the folder that corresponds with your synth's filter type, either the *"I Zdb"* or *"24db"* folder.
- B. Set the synth up to produce a single sawtooth waveform.
- C. Tum the filter cutoff all the way up so that it is completely open.
- D. Now play the 20,000 Hz file. Does it have the same tonal characteristics as your synth played at middle C? Make sure you are listening to your synth and the wave file at relatively the same amplitude. This is important because the human ear perceives amplitude changes differently for different frequencies. That's also why it is a good idea to not have the volume cranked during the final mix of a song ... but I digress! If your synth doesn't sound as bright as the 20,000 Hz file then try the 16,000 Hz or the 12,000 Hz files. If your synth sounds brighter than the 20,000 Hz file it is probably only slightly and for all practical purposes you can label it as 20,000 Hz.
- E. On a piece ofpaper write down the maximum setting value/dial position as well as the cutoff frequency that it corresponds to.
- F. What we are going to do now is lower the filter cutoffsetting in evenly spaced increments. Use whatever increments are convenient for the way your filter displays its setting. Anywhere from five to ten total values works fine.
- G. For each setting find the file that sounds the closest in tone and write down both the dial setting and cutofffrequency.

## **LFO Frequency**

- A. Open the "LFO" folder and you will see a bunch ofsound files where the names correspond to the frequency ofthe recorded LFO.
- B. Set the synth up to produce a single sawtooth waveform. Set the LFO up to use a square wave as its source. Route the LFO to the amplitude ofthis oscillator and set the modulation amount to 100%.
- C. Set the LFO frequency setting to its minimum. You should of course not hear any change in the amplitude when you strike a key.
- D. Listen to the 0.5 Hz file. Notice how long it takes for the amplitude ofthe sawtooth to "pulse." Adjust your synth's LFO so that it pulses at the same rate. Write down the setting position/value along with the corresponding LFO frequency from the filename.
- E. Now match your LFO frequency to the pulsing ofthe 1 Hz sound file and again write down the position and frequency values.
- F. Work your way up the list ofsound files matching the LFO frequency and writing the values down. You don't have to do this for every sound file, but I would do it for at least every other one.

#### **ADSRVALUES**

- A. In the *"ADSR "* folder there is an *"A"* folder and a *"D and R".* Of course *"A"* stands for attack and *"D and R"* stand for decay and release. Remember that sustain is always set as a percentage ofthe maximum setting so it doesn't need to be calibrated.
- B. *Finding the attack time:* Open the *"A"* folder and you will see a series ofsound files where each has a filename that indicates the length ofthe attack.
- C. Set all the ADSR values to their minimum. No sound should be produced when you strike a key.
- D. We are going to increase the attack setting in evenly spaced increments. Pick increment values that are convenient for the way your synth displays its values. Again , five to ten increments should work well. Be sure to hold down the keys long enough.
- E. At each increment compare your synths output to the sound files and once you've found a file that is a close match write down both the attack setting and the time listed in the name ofthe file. Repeat this for each increment until the attack setting is maxed out.

- F. *Finding the decay time:* Follow the same procedure as outlined in steps B-E only this time raise the value ofthe decay.
- G. *Finding the release time:* Same as steps B-E but this time also begin with sustain set to 100% and quickly strike the keys. Do nothold them down.

## **Part B - Using Sound Editors, Meters, and by Ear**

#### **Oscillator Mix:**

- A. The levels for the amplitude of each oscillator are given in terms of decibels. The maximum level is at 0 decibels with lower levels given in negative values. To determine your synthesizer's oscillator levels in terms of decibels you will need to monitor the synth's output using either a sound editor or a level meter that displays amplitude in decibels. A sound editor is the best choice since a recording can be made which can then be normalized.
- B. Make sure the filter is completely open and that the amplitude is not being enveloped.
- C. Begin by turning the amplitude of one oscillator up to its maximum setting and turning all other oscillators and noise sources off.
- D. If you are using a sound editor start recording now.
- E. The maximum setting ofthe level corresponds to 0 dB so it will be convenient if at this point the output from the synth can be displayed as 0 dB on whatever is being used to meter the signal (Here we are using decibels on a relative scale rather than a measure of actual audio output). If you are using something other than a sound editor to meter the output then use your synth's master volume, the channel in the host application or mixing board or computer's audio mixer to bring the synth's level to 0 dB on the meter while keeping the oscillators own level setting at the maximum setting. In other words don 't manipulate the oscillator's level setting to bring the meter to 0 dB. If you are using a sound editor don 't bother messing with the level on the meter since we are going to normalize the recording to 0 dB anyways. If you are not able to adjust the signal to 0 dB on the display it's no big deal as the final values can be adjusted. This is explained more below.

- F. *Using a sound editor:* While recording, bring the level ofthe audible oscillator down in equally-spaced increments. 10 increments are fine and 5 are also okay but more is always better. Playa note once at each increment. Once the minimum level setting has been reached stop the recording and normalize it. This will bring the maximum value to 0 dB. Now make a note ofthe corresponding decibel levels for each setting ofthe oscillator level.
- G. *Not using a sound editor:* Bring the level ofthe audible oscillator down in equallyspaced increments while writing down the decibel level at each interval. 10 increments are fine and 5 are also okay but more is always better. If you were unable to adjust the level so that at it's maximum it displayed as 0 dB on the meter, simply take the difference between 0 dB and what you were able to get it to on the display and add this difference to each one of your decibel values. By adding this difference the maximum value becomes 0 dB and each ofthe successive values of course increases by the value ofthe difference.

#### **Filter Cutoff:**

- A. Some synthesizers have filters that are selfresonating. That means the filter will still produce resonance even if all ofthe oscillators or noise generators are turned off. If the synthesizer you are using is selfresonating then conduct this procedure with all oscillators and noise sources off. Ifthe synthesizer is not selfresonating then the next best thing to use is a noise source and ifthis is not available use a single oscillator.
- B. Ifthe filter has keyboard tracking make sure it is turned off.
- C. Also tum offthe filter envelope and filter velocity response ifpresent.
- D. Tum the filter resonance all the way up.
- E. Experiment by changing the amount offilter cutoff and notice how the pitch ofthe filter resonance changes. Weare going to use this to determine the frequency cutoff settings. The frequency ofthe resonance corresponds roughly with the frequency of the filter cutoff. The two are close enough that for the purposes ofthis book we can take the resonance frequency as being the same as the filter cutoff frequency. This process to an extent ignores the fact that filters are logarithmic. Despite these approximations the results are fairly close to the actual values ofthe filter.

- F. Whereas with the other setting calibrations we might start at the lowest value and work upward in intervals, here we are going to start in the middle ofthe filter cutoff's range and work outward. This is done because it can be very difficult to hear, let alone identify, the high and low frequencies produced by the resonator so it is best to start in the middle.
- G. With the cutofffrequency setting placed in the middle ofits range try to identify the resonator's pitch with a note either on another keyboard or by momentarily turning on one of your synthesizer's oscillators. Make sure that whatever source you use for comparison that it is not detuned!
- H. Locate the key in Table I to determine the corresponding frequency ofthe filter cutoffsetting. Adjusting the filter cutoff up or down, work outward in evenly-spaced intervals using this same approach. Remember to write down the settings along with their frequencies.
- 1. At extreme high and low cutofffrequencies the resonance may become inaudible. The thing to do here is to determine these frequencies by basing them off ofthe frequencies from the intervals that have already been determined. Looking at the values you've written down notice that with each interval the frequency multiplies by *about* the same amount each time. Now since filters are logarithmic the value doesn't multiply by exactly the same amount each time but it's fairly close. Knowing this makes it simple to find the high and low frequencies. Ok, maybe it's not so simple!
- J. Divide the highest frequency that you found by ear by the second highest frequency to form a ratio. Now multiply the ratio by the highest frequency. This new value is the frequency ofthe next highest interval that could not be found by ear. Multiply this new frequency by the ratio to find the frequency ofthe next interval and so on until you have all the inaudible high frequencies.
- K. To find the low frequencies divide the lowest frequency found by ear by the second lowest frequency to again form a ratio. Multiply this ratio by the lowest frequency that could be found by ear to determine the frequency ofthe next lowest interval. Repeat this process just like before. For more clarification please look at the example on the next page.

Table 1. Note Frequencies

| NOTE         | FREQUENCY | NOTE | FREQUENCY | NOTE | FREQUENCY  |
|--------------|-----------|------|-----------|------|------------|
|              | (Hz)      |      | (Hz)      |      | (Hz)       |
| C1           | 32.703    | F#4  | 369.994   | C8   | 4186.009   |
| C#1          | 34.648    | G4   | 391.995   | C#8  | 4434.922   |
| 01           | 36.708    | G#4  | 415.305   | 08   | 4698.636   |
| 0#1          | 38.891    | A4   | 440.000   | 0#8  | 4978.032   |
| E1           | 41.203    | A#4  | 466.164   | E8   | 5274.041   |
| F1           | 43.654    | 84   | 493.883   | F8   | 5587.652   |
| F#1          | 46.249    | C5   | 523.251   | F#8  | 5919.911   |
| G1           | 48.999    | C#5  | 554.365   | G8   | 6271.927   |
| G#1          | 51.913    | 05   | 587.330   | G#8  | 6644.875   |
| A1           | 55.000    | 0#5  | 622.254   | A8   | 7040.000   |
| A#1          | 58.270    | E5   | 659.255   | A#8  | 7458.620   |
| 81           | 61.735    | F5   | 698.456   | 88   | 7902.133   |
| C2           | 65.406    | F#5  | 739.989   | C9   | 8372.018   |
| C#2          | 69.296    | G5   | 783.991   | C#9  | 8869.844   |
| 02           | 73.416    | G#5  | 830.609   | 09   | 9397.273   |
| 0#2          | 77.782    | A5   | 880.000   | 0#9  | 9956.063   |
| E2           | 82.407    | A#5  | 932.328   | E9   | 10548.082  |
| F2           | 87.307    | 85   | 987.767   | F9   | 11175.303  |
| F#2          | 92.499    | C6   | 1046.502  | F#9  | 11839.8-22 |
| G2           | 97.999    | C#6  | 1108.731  | G9   | 12543.854  |
| G#2          | 103.826   | 06   | 1174.659  | G#9  | 13289.750  |
| A2           | 110.000   | 0#6  | 1244.508  | A9   | 14080.000  |
| A#2          | 116.541   | E6   | 1318.510  | A#9  | 14917.240  |
| 82           | 123.471   | F6   | 1396.913  | 89   | 15804.266  |
| C3           | 130.813   | F#6  | 1479.978  | C10  | 16744.036  |
| C#3          | 138.591   | G6   | 1567.982  | C#10 | 17739.688  |
| 03           | 146.832   | G#6  | 1661.219  | 010  | 18794.545  |
| 0#3          | 155.563   | A6   | 1760.000  | 0#10 | 19912.127  |
| E3           | 164.814   | A#6  | 1864.655  | E10  | 21096.164  |
| F3           | 174.614   | 86   | 1975.533  | F10  | 22350.607  |
| F#3          | 184.997   | C7   | 2093.005  | F#10 | 23679.643  |
| G3           | 195.998   | C#7  | 2217.461  | G10  | 25087 .708 |
| G#3          | 207.652   | 07   | 2349.318  | G#10 | 26579.501  |
| A3           | 220.000   | 0#7  | 2489.016  | A10  | 28160.000  |
| A#3          | 233.082   | E7   | 2637.020  | A#10 | 29834.481  |
| 83           | 246.942   | F7   | 2793.826  | 810  | 31608.531  |
| C4(mid<br>C) | 261.626   | F#7  | 2959.955  |      |            |
| C#4          | 277.183   | G7   | 3135.963  |      |            |
| 04           | 293.665   | G#7  | 3322.438  |      |            |
| 0#4          | 311.127   | A7   | 3520.000  |      |            |
| E4           | 329.628   | A#7  | 3729.310  |      |            |
| F4           | 349.228   | 87   | 3951.066  |      |            |

#### Example:

1. Below are the values of the filter cutoff frequency ofa particular ynthc:siz=- imI! "':Z; found by matching the resonance pitch to its corresponding note on <sup>a</sup> .lbood..b!IiIIJ~ Table 1 to find the frequency. Values from 0%-20% and 80%-100% are 3J·~as: i!a:::.I!II1e an accurate pitch could not be determined by ear. Those values will be f4~:;r::j IIl!!i~\_lllI£ math.

| Cutoff  | Cutoff     |
|---------|------------|
| Setting | Frequency  |
| 30%     | 836<br>Hz  |
| 40%     | 1463<br>Hz |
| 50%     | 2540<br>Hz |
| 60%     | 4277<br>Hz |
| 70%     | 6906<br>Hz |

2. Finding higher frequency settings: Take the highest frequency and div ide . lowest frequency to find a ratio.

$$\frac{6906Hz}{4277Hz} = 1.62$$

Multiply the value ofthis ratio by 6906 Hz in order to find the frequency at a ClIIO 80%

$$6906 \ Hz \times 1.62 = 11{,}155 \ Hz,$$

at 90%

$$11,155 Hz \times 1.62 = 17,273 Hz,$$

at 100%

$$17,273 \ Hz \times 1.62 = 25,735 \ Hz,$$

Notice that for each interval the ratio is multiplied by the previous frequency.

3. Finding lower frequency settings: Take the lowest frequency and divide it by the next *highest* frequency.

$$\frac{836Hz}{1463Hz} = 0.57$$

Multiply the value ofthis ratio by 836 Hz in order to find the frequency at a cutoffsetting of 20%

$$836 \ Hz \times 0.57 = 478 \ Hz,$$

at 10%

$$478 Hz \times 0.57 = 274 Hz$$

at 0%

$$274 \ Hz \times 0.57 = 156 \ Hz$$

4. Below on the left are the values that have been found. Those values found by ear are in bold and values that were calculated are in italics. Below on the right are the actual . values ofthe filter at their respective cutoffsettings.

| CALCULATED | VALUES       | ACTUAL<br>VALVES |              |  |
|------------|--------------|------------------|--------------|--|
| Cutoff     | Cutoff       | Cutoff           | Cutoff       |  |
| Setting    | Frequency    | Setting          | Frequency    |  |
| 0%         | 156<br>Hz    | 0%               | 26Hz         |  |
| 10%        | 274<br>Hz    | 10%              | 253<br>Hz    |  |
| 20%        | 478<br>Hz    | 20%              | 483<br>Hz    |  |
| 30%        | 836Hz        | 30%              | 836<br>Hz    |  |
| 40%        | 1,463<br>Hz  | 40%              | 1,463<br>Hz  |  |
| 50%        | 2,540<br>Hz  | 50%              | 2,540<br>Hz  |  |
| 60%        | 4,277<br>Hz  | 60%              | 4,277<br>Hz  |  |
| 70%        | 6,906<br>Hz  | 70%              | 6,906<br>Hz  |  |
| 80%        | 11,155<br>Hz | 80%              | 10,695<br>Hz |  |
| 90%        | 17,273<br>Hz | 90%              | 15,134<br>Hz |  |
| 100%       | 25,735<br>Hz | 100%             | 20,546<br>Hz |  |

The values that were calculated are quite a bit offfrom the actual values at the extreme ends ofthe filter. This is because we've ignored the fact that the filter is logarithmic. This is also why it is best to find as many frequencies as possible by ear. The

inaccuracies ofthe values found between 10%- 20% and 80%-90% won' t make a dramatic difference in the tonal color ofthe sound. In fact most cutoff frequencies above 12 kHz sound the same. At 0% it is safe to assume a value of 20 Hz with just about any synthesizer. For the 100% setting keep in mind that filters typicall y open up to 12 kHz. 16 kHz or most commonly 20 kHz.

It is not nece ssary that your intervals be done in 10% increments. The se were just chosen here for the example. However, it is important that the cutoffsettings be changed by the same amount each time. For instance ifthe filter is set using a dial then rotate the dial by the same amount each time. It would be possible to fmd values for all ofthe settings above even if only two frequencies had been determined in step one, but the more frequencies that are found by ear the more accurate the list will be.

#### **LFO Frequency:**

- A. To determine the frequency settings ofthe LFO requires the use of a sound editor.
- B. Route the LFO to the amplitude and set its waveshape to square. Set the LFO frequenc y to its highest (fastest) setting. Set the LFO amount to its maximum.
- C. Begin recording with the sound editor. Playa note on the synthesizer for a couple of seconds.
- D. Decrease the frequency setting in evenl y-spaced intervals and each time you decrease it playa note for a couple ofseconds.
- E. When the frequenc y setting is turned all the way down stop recording.
- F. The wave file should look something like this:

![](_page_122_Picture_10.jpeg)

G. Zoom into the recording ofthe first key that was played until you can easily identify individual pulses. It will look something like this: ':" if ---'· - . --\_.. Q,: '~ " *:i:'",,",* 'X" ••••> .• ,,.'L

![](_page_122_Picture_12.jpeg)

H. In order to determine frequenc y we must first determine period. Measure the time interval between the leading edges oftwo adjacent pulses. This time interval is the period. In many sound editors this can be done easily just by highlighting the region between the two leading edges and reading the time interval that becomes displayed.

Here's an example:

![](_page_123_Picture_2.jpeg)

- 1. Take the measured period and divide it into 1 in order to find the frequency.
- <sup>1</sup> J. Using the period of 0.06 seconds as an example: =16.7*Hz* 0.06sec
- K. Repeat steps G through I for each LFO setting in the recording.
- L. The lower LFG frequencies may be difficult to visually discern from one another in the sound editor window since it may be difficult to determine where one recording of an LFG setting ends and the next one begins. Look at the last third ofthe figure from step F:

![](_page_123_Picture_7.jpeg)

The period between LFO pulses is nearly the same length as the time between successive key strikes. Inside the above figure in the box there are actually three different LFO frequencies. The way to discern them is by noting that the width ofthe pulses become wider as the LFG frequency is decreased. **In**the figure below the three LFO settings have been separated. Notice that the pulse width in each group is different. The narrow slice in the first box is due to the LFG not being retriggered.

![](_page_123_Picture_9.jpeg)

#### **Glide time:**

- A. This calibration assumes a glide/portamento that is based on time rather than being proportional to the pitch interval between the two struck notes.
- B. Use a sound editor to record the sound of one note gliding to another note. Hold the lowest note on the keyboard followed by the highest note so that you hear a rise in pitch.
- C. In the recording zoom into the region where the two notes begin to glide. An example is given in the figure below.
- D. Measure the time interval from just before the pitch begins to change until just after it stops changing. This is glide time at that setting. In the figure below for example the glide time is measured to be 0.092 seconds.
- E. Complete this procedure multiple times at evenly-spaced intervals ofthe glide time setting while making note ofthe values.

![](_page_124_Figure_7.jpeg)

#### **ADSR Envelopes:**

- A. It can usually be assumed that the envelopes for amplitude and filtering have the same response. We will determine the envelope settings for both using the amplitude envelope but these same values can also be used for the filter envelope.
- B. Attack:
- 1. Set decay, sustain, and release all to zero. Set the attack time to its maximum setting.

- 2. Use a sound editor to record a note from the synthesizer. Hold the note long enough for the attack to finish. You will hear the amplitude increase and then instantly drop back to zero. In the sound editor measure the amount oftime it took for the amplitude . to max out. Make note ofthe values.
- 3. Repeat step 2 for successively smaller attack times by decreasing the setting in evenly-spaced intervals.

#### C. Decay:

- 1. Set attack, sustain and release to zero. Set the decay time to it's maximum setting.
- 2. Use a sound editor to record a note from the synthesizer. The decay will cause the sound to slowly decrease in amplitude. Hold the note long enough for the amplitude to go to zero. In the sound editor measure the amount oftime it takes for the amplitude to go to zero.
- 3. Repeat step 2 for successively smaller decay times by decreasing the setting in evenly-spaced intervals. Again, make note ofthe values.
- D. Sustain: this is measured as a percentage ofthe full setting rather than oftime and therefore doesn't require any determination. For example, if the knob/slider is turned halfway then the sustain is at 50%.

#### E. Release:

- 1. Set attack and decay to zero. Set sustain at 100%.
- 2. Use a sound editor to record a note from the synthesizer. Quickly strike but do not hold a note on the synthesizer. In the sound editor measure the amount oftime it takes for the amplitude to go to zero.
- 3. Repeat step 2 for successively smaller release times by decreasing the setting in evenly-spaced intervals. Make note ofthe values.

## **CONTENTS**

| ATORS                  | 1  | SYNTHESIS THROUGH<br>HARMONIC ANALYSIS AND    |     |
|------------------------|----|-----------------------------------------------|-----|
| mannes & waveforms     | 1  | REVERSE ENGINEERING                           | 29  |
| Page Villa             | 7  | Reverse engineering a a patch from another    |     |
| Semina .               | 9  | synth                                         | 30  |
| Mise                   | 12 | Reverse engineering a sound from a song       | 34  |
| Le ward tracking       | 13 | Emulating an acoustic                         |     |
| Projectory.            | 14 | instrument's harmonics and envelope: clarinet | 39  |
| Firmento               | 14 |                                               |     |
| 1500                   | 14 | COOKBOOK PATCHES                              | 47  |
| Rang modulation        | 15 | Instructions                                  | 47  |
| PILTERS                | 16 | String patches                                | 53  |
| Filter types           | 16 | Woodwinds                                     | 63  |
| Cinoff frequency       | 18 | Brass                                         | 69  |
| Filter slope           | 18 | Keyboards                                     | 73  |
| Resonance              | 20 | Vocals                                        | 77  |
| ENVELOPES              | 22 | Tuned percussion                              | 81  |
| LFOs                   | 24 | Untuned percussion                            | 85  |
| Pulse-width modulation | 25 | Leads                                         | 91  |
| Beat effects           | 26 | Bass                                          | 95  |
| Sample & hold          | 27 | Pads                                          | 99  |
| Sync sweeping          | 27 | Sound Effects                                 | 105 |
| KEYBOARD EXPRESSION    | 27 | CALIBRATION                                   | 111 |
| Velocity sensitivity   | 27 | Using the CD                                  | 111 |
| Aftertouch             | 27 | Using sound editors, meters                   | 115 |

## **PATCHES**

| STRINGS          |    | KEYBOARDS          |                     | New Age Lead                  | 92  |
|------------------|----|--------------------|---------------------|-------------------------------|-----|
| Banjo            | 53 | Accordion          | 73                  | R&B Slide                     | 93  |
| Cello            | 53 | Celeste            | 73                  | Screaming Sync                | 93  |
| Double Bass      | 54 | Clavichord         | 74                  | Strings PWM                   | 94  |
| Dulcimer         | 54 | Electric Piano     | 74                  | Trance 5th                    | 94  |
| Guitar, Acoustic | 55 | Harpsichord        | 75                  |                               |     |
| Guitar, Electric | 55 | Organ              | 75                  | BASS                          |     |
| Harp             | 56 | Piano              | 76                  | Acid Bass                     | 95  |
| Hurdy Gurdy      | 56 |                    |                     | Bass of the Time Lords        | 95  |
| Kora             | 57 | VOICE              |                     | Detroit Bass                  | 96  |
| Lute             | 57 | Angels             | 77                  | Deutsche Bass                 | 96  |
| Mandocello       | 58 | Choir              | 77                  | Digita l Bass                 | 97  |
| Mandolin         | 58 | Vocal, female      | 78                  | Funk Bass                     | 97  |
| Riti             | 59 | Vocal, male        | 78                  | Growling Bass                 | 98  |
| Sitar            | 59 | Whistling          | 79                  | Rez Bass                      | 98  |
| Stand up Bass    | 60 |                    |                     |                               |     |
| Viola            | 60 |                    | PERCUSSION, TUNED   |                               |     |
| Violin           | 61 | Bell               | 81                  | PADS<br>Android Dreams        | 99  |
|                  |    | Bongos             | 81                  | Aurora                        | 99  |
| WOODWINDS        |    | Conga              | 82                  | Celestial Wash                | 100 |
| Bagpipes         | 63 | Glockenspiel       | 82                  | Dark City                     | 100 |
| Bass Clarinet    | 63 | Marimba            | 83                  | Galactic Cathedral            | 101 |
| Bassoon          | 64 | Timpani            | 83                  | Galactic Chapel               | 101 |
| Clarinet         | 64 | Xylophone          | 84                  | Portus                        | 102 |
| Conch Shell      | 65 |                    |                     | Post-Apocalyptic              |     |
| Contrabassoon    | 65 |                    | PERCUSSION, UNTUNED |                               | 102 |
| Didgeridoo       | 66 | Bass Drum          | 85                  | Sync Sweep<br>Terra Enceladus | 103 |
| English Hom      | 66 | Castanets          | 85                  |                               |     |
| Flute            | 67 | Clap               | 86                  | SOUND EFFECTS                 |     |
| Oboe             | 67 | Claves             |                     |                               |     |
| Piccolo          | 68 | Cowbell            | 86                  | Cat                           | 105 |
|                  |    |                    | 87                  | Digital Alarm Clock           | 105 |
|                  |    | Cowbell, analog    | 87                  | Joumey to the Core            | 106 |
| BRA SS           |    | Cymbal             | 88                  | Kazoo                         | 106 |
| French Hom       | 69 | Side Stick         | 88                  | Laser                         | 107 |
| Harmonica        | 69 | Snare Drum         | 89                  | Motor                         | 107 |
| Penny Whistle    | 70 | Tambourine         | 89                  | Nerd-O-Tron 2000              | 108 |
| Saxophone        | 70 | Wheels of<br>Steel | 90                  | Ocean Waves                   |     |
| Trombone         | 71 |                    |                     | (with fog horn)               | 108 |
| Trumpet          | 71 | LEADS              |                     | Positronic Rhythm             | 109 |
| Tuba             | 72 | Brass Section      | 91                  | Space Attack!                 | 109 |
|                  |    | Mellow 70s Lead    | 91                  | Toad                          | 110 |
|                  |    | Mono Solo          | 92                  | Wind                          | 110 |

**PATCH QUICK START:** The filter cutofffrequency is the one parameter where getting the correct setting is most critical. If your synthesizer's filter doesn't give cutoff frequency values in Hz/kHz and the percentage values in the book don't seem to produce the correct results and if you don't feel like going through the whole calibration routine at the back ofthe book then to get offto a quick start do the following: Set the synth to output a single sawtooth. Set the filter' s cutoff frequency to the very middle ofits range and match the output to one ofthe sound files on the CD in the Calibration Sound Files -7 Filter -7 12 db *or* 24 db subfolder. The name ofthe sound file that matches the output gives the approximate cutoff frequency (in Hz) that corresponds to the middle position. Assume the lowest dial position of your synths cutofffrequency is 20 Hz and the highest position is a cutofffrequency of 20,000 Hz (20 kHz). These two values may not be correct for your synth but they will be close enough sound wise. Knowing just these three values, low, mid, and high, will actually make approximating the filter cutoff settings listed in the patches quite a bit more accurate.

Note: filter cutofffrequency settings generally do not operate on a linear scale so if you come up with a middle setting ofsomething like 300 Hz, 600 Hz, 1200 Hz etc. it is probably correct. In other words, the mid value is not going to be anywhere near 10,010 Hz which would be the *numerical* mid point between 20 Hz and 20,000 Hz.

## **Also be sure to check out: "Tri-Osc" t-shirt** \$12.95

![](_page_128_Picture_3.jpeg)

Shirt features the Synthesizer Cookbook triple oscillator logo across the front. Yellow print on a black 100% cottont-shirt. For more details, be sure to visit: www.synthesizer-cookbook.com