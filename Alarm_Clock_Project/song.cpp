#include <Arduino.h>
#include "song.h"

static volatile bool stopMusic;

typedef enum
{
  UNINTERRUPTED = 0,
  INTERRUPTED
}delayFuncStatus_t;

static delayFuncStatus_t NonBlockingDelay(int delayTime)
{
  int start = millis();
  while((millis() - start) < delayTime)
  {
    if(MusicStopped())
    {
      return INTERRUPTED;
    }
  }
  return UNINTERRUPTED;
}

void StopMusic(bool state)
{
  stopMusic = state;
}

bool MusicStopped(void)
{
  return stopMusic;
}

void PlaySong_TakeOnMe(void)
{
  const int melody[] = 
  {
    NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
    NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
    NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
    NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
  };
  const int durations[] = 
  {
    8, 8, 8, 4, 4, 4, 
    4, 5, 8, 8, 8, 8, 
    8, 8, 8, 4, 4, 4, 
    4, 5, 8, 8, 8, 8
  };  
  const int songLength = sizeof(melody)/sizeof(melody[0]);
  
  for (int thisNote = 0; thisNote < songLength; thisNote++)
  {
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    if(NonBlockingDelay(pause) == INTERRUPTED)
    {
      noTone(BUZZER_PIN);
      break;
    }
    // stop the tone
    noTone(BUZZER_PIN);
  }  
}

void PlaySong_Birthday(void)
{
  const int melody[] = 
  {
    NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_E5, PAUSE,
    NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_G5, NOTE_F5, PAUSE,
    NOTE_C5, NOTE_C5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_E5, NOTE_D5, PAUSE,
    NOTE_AS5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_G5, NOTE_F5 
  };  
  const int durations[] =
  {
    4,2,8,8,8,16,50,     //50  millis for the first pause
    4,2,8,8,8,16,100,    //100 millis for the second pause
    4,2,8,8,8,8,16,150,    //150 millis for the third pause
    4,2,8,8,8,20 
  };
  const int songLength = sizeof(melody)/sizeof(melody[0]);
  const int tempo = 25;
  
  for (int thisNote = 0; thisNote < songLength; thisNote++)
  {
    if (melody[thisNote] != PAUSE) 
    {
      tone(BUZZER_PIN,melody[thisNote]);
      if(NonBlockingDelay(durations[thisNote] * tempo) == INTERRUPTED)
      {
        noTone(BUZZER_PIN);
        break;
      }
      noTone(BUZZER_PIN);
      //delay after note reproduction following TEMPO variable's diktat
      if(NonBlockingDelay(tempo) == INTERRUPTED)
      {
        noTone(BUZZER_PIN);
        break;
      }
    } 
    else 
    {
      //delay if this is a pause. (it will be in millis, check NOTE_LEN)
      if(NonBlockingDelay(durations[thisNote]) == INTERRUPTED)
      {
        noTone(BUZZER_PIN);
        break;
      }
    }
  } 
}

void PlaySong_Starwars(void)
{
  const int melody[] = 
  {
    NOTE_G3, NOTE_G3, NOTE_G3, NOTE_D4, NOTE_G4, NOTE_E4, NOTE_D4, 
    NOTE_C4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C5, 
    NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4
  };  
  const int durations[] = 
  {
    6, 6, 6, 1, 1, 6, 6, 6, 1, 2, 6, 6, 6, 1, 2, 6, 6, 6, 1
  };
  //iterate over the notes of the melody
  for (int thisNote = 0 ; thisNote < 19; thisNote++) 
  {
    //to calculate the note duration, take one second. Divided by the note type
    int duration = 1000 / durations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], duration);
    //to distinguish the notes, set a minimum time between them
    //the note's duration +30% seems to work well
    int pauseBetweenNotes = duration * 1.30;
    if(NonBlockingDelay(pauseBetweenNotes) == INTERRUPTED)
    {
      noTone(BUZZER_PIN);
      break;
    }
    //stop the tone playing
    noTone(BUZZER_PIN);
  } 
}

