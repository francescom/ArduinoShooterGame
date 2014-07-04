#include <HT1632.h>
#include <font_5x4.h>

#include "Arduino.h"
#include "game.h"
#include "sprites.h"

int x=0;
int y=0;
int z=0;
int zSp=0;
const int xOrigin = 16;
const int yOrigin = 8;


#define MAX_SHOTS 10
#define SHOT_SPEED 4
#define SHOT_INTERVAL 4

struct shot {
  int x;
  int y;
  int dir;
  boolean active;
} shots[MAX_SHOTS];

#define MAX_ENEMIES 20
#define ENEMY_SPEED_X 1
#define ENEMY_SPEED_Y 1

struct enemy {
  int x;
  int y;
  int dirX;
  int dirY;
  int status;
  int energy;
  boolean active;
} enemies[MAX_ENEMIES];

void clearSprites() {
    HT1632.drawTarget(BUFFER_BOARD(1));
    HT1632.clear();
    HT1632.drawTarget(BUFFER_BOARD(2));
    HT1632.clear();
}
void drawSprite(int xOrigin,int yOrigin,int x,int y,sprite* aSprite) {
    HT1632.drawTarget(BUFFER_BOARD(1));
    HT1632.drawImage(aSprite->green, aSprite->w,  aSprite->h, xOrigin+x-aSprite->regX, yOrigin+y-aSprite->regY);
    HT1632.drawTarget(BUFFER_BOARD(2));
    HT1632.drawImage(aSprite->red, aSprite->w,  aSprite->h, xOrigin+x-aSprite->regX, yOrigin+y-aSprite->regY);
}
void renderSprites() {
    HT1632.drawTarget(BUFFER_BOARD(1));
    HT1632.render();
    HT1632.drawTarget(BUFFER_BOARD(2));
    HT1632.render();
}

void gameSetup() {
  for(int i=0;i<MAX_SHOTS;i++) {
    shots[i].x=0;
    shots[i].y=0;
    shots[i].dir=1;
    shots[i].active=false;
  }
  for(int i=0;i<MAX_ENEMIES;i++) {
    enemies[i].x=0;
    enemies[i].y=0;
    enemies[i].dirX=1;
    enemies[i].dirY=1;
    enemies[i].active=false;
  }
}

int gameStatus=0;
int score=0;
int lives=3;
int lastShotCounter=0;
int lastEnemyCreatCounter=0;
void gameLoop(int xValue,int yValue,boolean btnJPress,boolean btnLPress,boolean btnTPress,boolean btnRPress,boolean btnBPress) {
    
    clearSprites();
    
    int delayAfterRender=0;
    char scoreStr[20];
    String(score/10).toCharArray(scoreStr,20);
    int sw=HT1632.getTextWidth(scoreStr, FONT_5X4_WIDTH, FONT_5X4_HEIGHT);
    HT1632.drawTarget(BUFFER_BOARD(1));
    HT1632.drawText(scoreStr, OUT_SIZE-sw, 0, FONT_5X4, FONT_5X4_WIDTH, FONT_5X4_HEIGHT, FONT_5X4_STEP_GLYPH);
    String(lives).toCharArray(scoreStr,20);
    HT1632.drawTarget(BUFFER_BOARD(1));
    HT1632.drawText(scoreStr, 0, 0, FONT_5X4, FONT_5X4_WIDTH, FONT_5X4_HEIGHT, FONT_5X4_STEP_GLYPH);
    
    
    if(gameStatus==10) {
      if(btnLPress || btnRPress || btnBPress || btnTPress) {
        HT1632.render();
        return;
      }
      gameStatus=11;
    }
    
    if(gameStatus==0 || gameStatus==11) {
      
      if(btnLPress || btnRPress || btnBPress || btnTPress) {
        if(gameStatus==11) {
          lives=3;
          score=0;
        }
        gameStatus=1;
      }
      HT1632.render();
      return;
    }
    
    
    
    int lastShot=-1;
    int firstFreeShot=-1;
    
    int lastEnemy=-1;
    int firstFreeEnemy=-1;
    
    if(z>0) {
        zSp-=1;
    }
    if(btnBPress && z==0) {zSp=6;}
    
    if(zSp!=0) {
        z+=zSp;
        if(z<0) z=0;
        zSp*=19;
        zSp/=20;
    }
    
    x+=xValue/128;
    y+=yValue/128;
    
    if(x>16*2-2*sshipSp.regX) x=16*2-2*sshipSp.regX;
    if(x<-16*2+2*sshipSp.regX) x=-16*2+2*sshipSp.regX;
    if(y>8*2-2*sshipSp.regY) y=8*2-2*sshipSp.regY;
    if(y<-8*2+2*sshipSp.regY) y=-8*2+2*sshipSp.regY;
    
    for(int i=0;i<MAX_SHOTS;i++) {
      if(shots[i].active) {
        shots[i].x+=shots[i].dir*SHOT_SPEED;
        drawSprite(xOrigin,yOrigin,shots[i].x,shots[i].y,&shotSp);
        if(abs(shots[i].x)>16+3) {
          shots[i].x=0;
          shots[i].y=0;
          shots[i].active=false;
          shots[i].dir=1;
          if(firstFreeShot==-1) firstFreeShot=i;
        } else lastShot=i;
      } else if(firstFreeShot==-1) firstFreeShot=i;
    }
    
    for(int i=0;i<MAX_ENEMIES;i++) {
      if(enemies[i].active) {
        score++;

        enemies[i].x+=enemies[i].dirX*ENEMY_SPEED_X;
        enemies[i].y+=enemies[i].dirY*ENEMY_SPEED_Y;
        if(abs(enemies[i].x)<=12 && abs(enemies[i].y)<=6){
          if(random(0, 6)<=1 ) {
            enemies[i].dirX=random(0,3)-1;
          }
          if(random(0, 6)<=1 ) {
            enemies[i].dirY=random(0,3)-1;
          }
        } else {
          if(enemies[i].x>12) {
            enemies[i].dirX=-1;
          } else if(enemies[i].x<-12) {
            enemies[i].dirX=1;
          }
          if(enemies[i].y>6) {
            enemies[i].dirY=-1;
          } else if(enemies[i].y<-6) {
            enemies[i].dirY=1;
          }
        }
        lastEnemy=i;
        for(int j=0;j<MAX_SHOTS;j++) {
          if(shots[j].active) {
            if(abs(enemies[i].x-shots[j].x)<3 && abs(enemies[i].y-shots[j].y)<3) {
              enemies[i].energy--;
              shots[j].active=false;
              score+=20;
              if(enemies[i].energy<=0) {
                enemies[i].active=false;
                score+=30;
                // SOUND
              }
            }
          }
        }
        if(abs(enemies[i].x-x/2)<3 && abs(enemies[i].y-y/2+z/2)<3 /** / && z==0 /**/) {
          gameSetup();
          lastEnemyCreatCounter=50;
          x=y=0;
          delay(200);
          // SOUND
          lives--;
          if(lives<=0) {
            gameStatus=10;
            // SOUND
          }
        }
        
        drawSprite(xOrigin,yOrigin,enemies[i].x,enemies[i].y,&enemySp);
        } else if(firstFreeEnemy==-1) firstFreeEnemy=i;
    }
    if(lastEnemyCreatCounter>0) lastEnemyCreatCounter--;
    if(random(0,20)<=1 && firstFreeEnemy!=-1 && lastEnemyCreatCounter<=0) {
      if(random(0,2)<1) {
        enemies[firstFreeEnemy].x=18;
        enemies[firstFreeEnemy].dirX=-1;
      } else {
        enemies[firstFreeEnemy].x=-18;
        enemies[firstFreeEnemy].dirX=1;
      }
      enemies[firstFreeEnemy].dirY=random(0,3)-1;
      enemies[firstFreeEnemy].energy=random(1,3);
      enemies[firstFreeEnemy].active=true;
      
      lastEnemyCreatCounter=10;
    }
    if(lastShotCounter>0) lastShotCounter--;
    
    if(btnRPress && firstFreeShot!=-1 && lastShotCounter<=0) {
      shots[firstFreeShot].active=true;
      shots[firstFreeShot].x=x/2;
      shots[firstFreeShot].y=y/2-z/2;
      shots[firstFreeShot].dir=1;
      lastShotCounter=SHOT_INTERVAL;
    }

    if(btnLPress && firstFreeShot!=-1 && lastShotCounter<=0) {
      shots[firstFreeShot].active=true;
      shots[firstFreeShot].x=x/2;
      shots[firstFreeShot].y=y/2-z/2;
      shots[firstFreeShot].dir=-1;
      lastShotCounter=SHOT_INTERVAL;
    }

    
    drawSprite(xOrigin,yOrigin,x/2,y/2-z/2,&sshipSp);
    renderSprites();
    
    if(delayAfterRender>0) delay(delayAfterRender);
}

