#ifndef ORC1_H
#define ORC1_H

#include<raylib.h>

typedef struct {
    Texture2D texture;
    Rectangle frameRec;
    Vector2 position;
    Vector2 origin;
    Rectangle source;
    Rectangle dest;
    float scale;
    float frameWidth;
    float frameHeight;
    int screenWidth;
    int screenHeight;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    bool flipSprite;
    bool isAttacking;
} Orc;

void InitOrc(Orc* orc, int screenWidth, int screenHeight);
void RenderOrc(Orc* orc);



#endif