#ifndef MUSIC_H_
#define MUSIC_H_

#define DEAD_TIME_MS 20
#define TICKS_PER_BEAT 4

#define E3 3033
#define Fs3 2703
#define G3 2551
#define Gs3 2408
#define A3 2273
#define As3 2145
#define B3 2025
#define Cb4 
#define C4 1911
#define Cs4 1804
#define Db4 1804
#define D4 1703
#define Ds4 1607
#define Eb4 1607
#define E4 1517
#define F4 1432
#define Fs4 1351
#define Gb4 1351
#define G4 1276
#define Gs4 1204
#define Ab4 1204
#define A4 1136
#define As4 1073
#define Bb4 1073
#define B4 1012
#define C5 956
#define Cs5 902
#define Db5 902
#define D5 851
#define Ds5 804
#define Eb5 804
#define E5 758
#define F5 716
#define Fs5 676
#define Gb5 676
#define G5 638
#define Gs5 602
#define Ab5 602
#define A5 568

extern volatile unsigned int sound_enabled;

extern volatile unsigned int current_note;

extern volatile unsigned int ms_elapsed;

void song_play();

void set_bpm(unsigned int bpm);

void play(unsigned int note, unsigned int duration_ticks);

#endif
