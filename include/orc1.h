#ifndef ORC1_H
#define ORC1_H
#include <raylib.h>
#include <stddef.h>

// Forward declaration for Knight
struct Knight;

typedef struct Orc {
    // Existing Orc struct fieldsasdad
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
    int health;
    bool isAlive;
} Orc;

// Rest of the existing code remains the same
typedef enum OrcAnimationState{
    ORC_IDLE=0,
    ORC_RUN=1,
    ORC_ATTACK=2,    
    ORC_HIT=5,
    ORC_DEATH=6
} OrcAnimationState;

void InitOrc(Orc* orc, int screenWidth, int screenHeight);
void RenderOrc(Orc* orc);
void UpdateOrc(Orc* orc, OrcAnimationState* currentAnimation);
void Moveorc(Orc* orc, OrcAnimationState* currentAnimation, bool* isAttacking);
void OrcTakingDamage(Orc* orc, int damage, OrcAnimationState* currentAnimation);

#endif
