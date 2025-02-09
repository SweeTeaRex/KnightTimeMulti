#ifndef CONSTANTS_H
#define CONSTANTS_H

#include<raylib.h>

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1
#define knight_IDLE_SPRITE_LENGTH 192
#define SPRITE_ROWS 8
#define SPRITE_COLS 5
#define SPRITE_GAP 2



// init game screens
typedef enum GameScreen
{
    SplashScreen = 0,
    StartScreen,
    Level_1
} GameScreen;

const int knightFrameCounts[]={
    6,
    8,
    6,
    4,
    4
};

typedef enum knightAnimationState{
    IDLE=0,
    RUN=1,
    ATTACK=2,
    ARROW=4,
    HIT=6,
    DEATH=7
} knightAnimationState;

#endif