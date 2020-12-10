#ifndef stateMachine_included
#define stateMachine_included

char startX;
char startY;
char heartState;
char button;

void stateInit();
void heart_states();
void assyNoteScale();
void state_advance();
void both_lights();
void tgl_red_off();
void tgl_green_off();
#endif // included
