#include "knight1.h"
#include "orc1.h"
#include <raylib.h>
#include <stdio.h>

const int knightFrameCounts[]={
    6,
    8,
    6,
    4,
    4
};

void InitKnight(Knight* knight, int screenWidth, int screenHeight) {
    knight->screenWidth = screenWidth;
    knight->screenHeight = screenHeight;
    knight->texture = LoadTexture("assets/Soldier.png");
    knight->frameWidth = knight->texture.width/9.0;
    knight->frameHeight = knight->texture.height/7.0f;
    
    knight->scale = 6.0f;
    knight->position = (Vector2){
        knight->screenWidth/2-(knight->texture.width/9.0f*knight->scale/2),
        knight->screenHeight/2-(knight->texture.height/7.0f*knight->scale/2)
    };
    
    knight->origin = (Vector2){0.0f, 0.0f};
    knight->frameRec = (Rectangle){0.0f, 0.0f, knight->frameWidth, knight->frameHeight};
    knight->source = knight->frameRec;
    knight->dest = (Rectangle){
        knight->position.x-100,
        knight->position.y,
        knight->source.width*knight->scale,
        knight->source.height*knight->scale
    };
    
    knight->currentFrame = 0;
    knight->framesCounter = 0;
    knight->framesSpeed = 8;
    knight->flipSprite = false;
    knight->isAttacking = false;
}



void UpdateKnight(Knight* knight, KnightAnimationState* currentAnimation)
{
    knight->framesCounter++;

    if(knight->framesCounter >= (60/knight->framesSpeed))
    {
        knight->framesCounter=0;
        knight->currentFrame++;

        if(knight->currentFrame>=knightFrameCounts[*currentAnimation])
        knight->currentFrame=0;

        knight->frameRec.x=knight->currentFrame*knight->frameWidth;
        knight->frameRec.y=*currentAnimation * knight->frameHeight;
        knight->frameRec.height = knight->frameHeight;
    }
    
}
void RenderKnight(Knight* knight) {
    if (knight->flipSprite) {
        Rectangle sourceRect = knight->frameRec;
        sourceRect.width = -knight->frameRec.width;
        DrawTexturePro(knight->texture, sourceRect, knight->dest, 
            knight->origin, 0.0f, WHITE);
    } else {
        Rectangle sourceRect = knight->frameRec;
        sourceRect.width = knight->frameRec.width;
        DrawTexturePro(knight->texture, sourceRect, knight->dest, 
            knight->origin, 0.0f, WHITE);
    }
}

void MoveKnight(Knight* knight, KnightAnimationState* currentAnimation, bool* isAttacking)
{
    if(IsKeyDown(KEY_W)) {
        *currentAnimation = *isAttacking?KNIGHT_ATTACK:KNIGHT_RUN;
        knight->dest.y--;
    } 
    else if(IsKeyDown(KEY_S)) {
        *currentAnimation = *isAttacking?KNIGHT_ATTACK:KNIGHT_RUN;
        knight->dest.y++;
    } 
    else if(IsKeyDown(KEY_A)) {
        *currentAnimation = *isAttacking?KNIGHT_ATTACK:KNIGHT_RUN;
        knight->flipSprite=false;
        knight->dest.x--;
    } 
    else if(IsKeyDown(KEY_D)) {
         *currentAnimation = *isAttacking?KNIGHT_ATTACK:KNIGHT_RUN;
        
        knight->flipSprite=true;
        knight->dest.x++;
    }
    
    else{
        *currentAnimation = *isAttacking ? KNIGHT_ATTACK:KNIGHT_IDLE;
        
    }
    
    if(IsKeyDown(KEY_SPACE))
    {
        *isAttacking=true;
        *currentAnimation=KNIGHT_ATTACK;
    }
    else{
        *isAttacking=false;
    }
}

void CheckKnightAttackCollision(Knight* knight, Orc* orc, bool* isAttacking, KnightAnimationState* currentAnimation)
{
    if(!*isAttacking) return;
    Rectangle knightAttackRect = {
        knight->dest.x,
        knight->dest.y,
        knight->dest.width,
        knight->dest.height

    };
       
    Rectangle orcRect ={
        orc->dest.x,
        orc->dest.y,
        orc->dest.width,
        orc->dest.height
    };

    if(*isAttacking && CheckCollisionRecs(knightAttackRect, orcRect))
    {
        OrcTakingDamage(orc, 50, currentAnimation);
        printf("\nCollision Check\n");
       
    }
}