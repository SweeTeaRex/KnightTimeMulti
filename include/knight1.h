#ifndef KNIGHT1_H    // Conventionally uppercase
#define KNIGHT1_H
#include <raylib.h>

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
} Knight;           // Capitalize Knight as it's a type name

// Function names should be consistent with the type name
void InitKnight(Knight* knight, int screenWidth, int screenHeight);
void RenderKnight(Knight* knight);

#endif