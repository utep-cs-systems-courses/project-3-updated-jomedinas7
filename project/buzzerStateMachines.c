#include <msp430.h>
#include "buzzer.h"

//music notes for frequency equation
#define FSfv 759
#define Dfv 587
#define Ffv 699
#define Efv 659
#define Csfv 554
#define Bfv 987
#define Bfr 494
#define Afv 880
#define Gfv 784

static int notes[52] = {

  FSfv, 20, 0, 0, 40, 0, 40, 20, 60, 0,
  FSfv, Dfv, Efv, Efv, Ffv, Efv, Dfv, Csfv, Dfv, Efv,
  FSfv, Bfv, Bfr, Csfv, Dfv, Efv, Dfv, Csfv, Afv, Gfv,
  FSfv, Dfv, Efv, Efv, Ffv, Efv, Dfv, Csfv, Dfv, Efv,
  FSfv, Bfv, Bfr, 277, Dfv, 392, 370, 349, Dfv, 466,
  494, 0
};

int beats[52] = {

  4,6,1,1,2,2,2,2,2,2,
  4,6,1,1,2,2,2,2,2,2,
  4,6,1,1,2,2,2,2,2,2,
  4,6,1,1,2,2,2,2,2,2,
  4,6,1,1,2,2,2,2,2,2,
  4,5
};

void play_song()
{
  // static char blink_count = 0; //count to mimick interrupts
  static char noteIndex = 0;
  static int state = 0; //the note that will be played
  if(noteIndex == 52){ //if we reach the end of the song
    buzzer_set_period(0); //turn off buzzer
    // blink_count = 0; //reset counts
    noteIndex = 0;
    }
  else if(++state == (beats[noteIndex]*33)){ //timing the beats to play notes for
    noteIndex++; //move to next note
    buzzer_set_period(2000000/notes[noteIndex])//play note
;
    state = 0;//reset count
    }
  
}

  

  
  
