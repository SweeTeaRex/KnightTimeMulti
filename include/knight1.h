#ifndef KNIGHT1_H
#define KNIGHT1_H
#include <raylib.h>


// forward declaration for Orc
struct Orc;

typedef struct Knight{
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
} Knight;

typedef enum KnightAnimationState {
    KNIGHT_IDLE = 0,
    KNIGHT_RUN = 1,
    KNIGHT_ATTACK = 2,
    KNIGHT_ARROW = 4,
    KNIGHT_HIT = 6,
    KNIGHT_DEATH = 7
} KnightAnimationState;

void InitKnight(Knight* knight, int screenWidth, int screenHeight);
void RenderKnight(Knight* knight);
void UpdateKnight(Knight* knight, KnightAnimationState* currentAnimation);
void MoveKnight(Knight* knight, KnightAnimationState* currentAnimation, bool* isAttacking);
void CheckKnightAttackCollision(Knight* knight, struct Orc* orc, bool* isAttacking, KnightAnimationState* currentAnimation);

#endif