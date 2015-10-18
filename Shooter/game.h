#define prog_char const char PROGMEM
const char audioPin=8;


#ifndef GAME
#define GAME


#include "Arduino.h"


/* ..Declarations.. */

void gameSetup();
void gameLoop(int xValue,int yValue,boolean btnJPress,boolean btnLPress,boolean btnTPress,boolean btnRPress,boolean btnBPress);



#endif
