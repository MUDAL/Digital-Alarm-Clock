#ifndef SONG_H
#define SONG_H

#include "pitches.h"
#define BUZZER_PIN  11

extern void StopMusic(bool state);
extern bool MusicStopped(void);
extern void PlaySong_TakeOnMe(void);
extern void PlaySong_Birthday(void);

#endif
