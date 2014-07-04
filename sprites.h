#ifndef SPRITES
#define SPRITES

#include <HT1632.h>

struct sprite {
  int w;
  int h;
  int regX;
  int regY;
  prog_char * red;
  prog_char * green;
};

prog_char SHOTRED [] PROGMEM = {0b0010, 0b0010, 0b0010, 0b0000};
prog_char SHOTGRE [] PROGMEM = {0b0010, 0b0000, 0b0010, 0b0000};

#define SHOT_WIDTH 	 4
#define SHOT_HEIGHT 	 4
#define SHOT_REGX 	 2
#define SHOT_REGY 	 1

struct sprite shotSp={SHOT_WIDTH,SHOT_HEIGHT,SHOT_REGX,SHOT_REGY,SHOTRED,SHOTGRE};



prog_char SSHIPRED [] PROGMEM = {0b1010, 0b0101, 0b0101, 0b1010};
prog_char SSHIPGRE [] PROGMEM = {0b1000, 0b0010, 0b0010, 0b1000};

#define SSHIP_WIDTH 	 4
#define SSHIP_HEIGHT 	 4
#define SSHIP_REGX 	 2
#define SSHIP_REGY 	 2

struct sprite sshipSp={SSHIP_WIDTH,SSHIP_HEIGHT,SSHIP_REGX,SSHIP_REGY,SSHIPRED,SSHIPGRE};




prog_char ENEMYRED [] PROGMEM = {0b1110, 0b0000, 0b0101, 0b0001, 0b0111, 0b0000, 0b0101, 0b0001, 0b1110, 0b0000};
prog_char ENEMYGRE [] PROGMEM = {0b1000, 0b0000, 0b0010, 0b0001, 0b0000, 0b0000, 0b0010, 0b0001, 0b1000, 0b0000};

#define ENEMY_WIDTH 	 5
#define ENEMY_HEIGHT 	 5
#define ENEMY_REGX 	 2
#define ENEMY_REGY 	 2

struct sprite enemySp={ENEMY_WIDTH,ENEMY_HEIGHT,ENEMY_REGX,ENEMY_REGY,ENEMYRED,ENEMYGRE};

#endif
