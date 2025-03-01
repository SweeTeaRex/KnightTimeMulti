#include "orc1.h"
#include "knight1.h"
#include <raylib.h>
#include <stdio.h>

const int orcFrameCounts[] = {
    6,  // IDLE
    8,  // RUN
    6,  // ATTACK
    4,  // HIT
    4   // DEATH
};

void InitOrc(Orc* orc, int screenWidth, int screenHeight) {
    orc->screenWidth = screenWidth;
    orc->screenHeight = screenHeight;
    orc->texture = LoadTexture("assets/Orc.png");
    orc->frameWidth = orc->texture.width/8.0;
    orc->frameHeight = orc->texture.height/6.0f;
    orc->health=100;
    orc->isAlive = true;
    
    orc->scale = 6.0f;
    orc->position = (Vector2){
        orc->screenWidth/2-(orc->texture.width/8.0f*orc->scale/2),
        orc->screenHeight/2-(orc->texture.height/6.0f*orc->scale/2)
    };
    
    orc->origin = (Vector2){0.0f, 0.0f};
    orc->frameRec = (Rectangle){0.0f, 0.0f, orc->frameWidth, orc->frameHeight};
    orc->source = orc->frameRec;
    orc->dest = (Rectangle){
        orc->position.x+100,
        orc->position.y,
        orc->source.width*orc->scale,
        orc->source.height*orc->scale
    };
    
    orc->currentFrame = 0;
    orc->framesCounter = 0;
    orc->framesSpeed = 8;
    orc->flipSprite = false;
    orc->isAttacking = false;
}

void RenderOrc(Orc* orc) {

    Rectangle orcSourceRectangle = orc->frameRec;
    
    if(orc->flipSprite)
    {
        orcSourceRectangle.width = -orc->frameRec.width;
        DrawTexturePro(orc->texture, orcSourceRectangle, orc->dest, orc->origin, 0.0f, WHITE);
        
        
    } else {
        
        orcSourceRectangle.width = orc->frameRec.width;
        DrawTexturePro(orc->texture, orcSourceRectangle, orc->dest, orc->origin, 0.0f, WHITE);

        
    }

    
}

void UpdateOrc(Orc* orc, OrcAnimationState* currentAnimation)
{
    if (currentAnimation == NULL || orc == NULL) return;

    printf("UpdateOrc - isAlive: %d, currentAnimation %d, currentFrames: %d\n",
        orc->isAlive, *currentAnimation, orc->currentFrame);
    
    
    
    orc->framesCounter++;
    if (orc->framesCounter >= (60 / orc->framesSpeed))
    {
        orc->framesCounter = 0;
        orc->currentFrame++;
        
        int maxFrames = 4;  // Death animation frames
        int effectiveFrames = 4;

        switch(*currentAnimation)
        {
            case ORC_IDLE: maxFrames=6;
            effectiveFrames = 5; 
            break;

            case ORC_RUN: maxFrames=8; 
            effectiveFrames = 7;
            break;

            case ORC_ATTACK: maxFrames=6; 
            effectiveFrames = 5;
            break;

            case ORC_HIT: maxFrames=4; 
            effectiveFrames = 3;
            break;

            case ORC_DEATH: maxFrames=4; 
            effectiveFrames = 3;
            break;

            default: maxFrames=4; 
            effectiveFrames = 3;
            break;
        }

        printf("Max Frames: %d\n", maxFrames);
        
        if (orc->currentFrame >= effectiveFrames)
        {
            if(*currentAnimation == ORC_DEATH)
            {
                orc->currentFrame = effectiveFrames - 1;
            }
            else if(*currentAnimation == ORC_HIT)
            {
                orc->currentFrame = 0;
                *currentAnimation = ORC_IDLE;
            }
            else
            {
                orc->currentFrame = 0;
            }
        }
        
        // Update frame rectangle
        

        printf("Frame Rec - x: %f, y: %f\n", orc->frameRec.x, orc->frameRec.y);
    }
    orc->frameRec.x = orc->currentFrame * orc->frameWidth;
    orc->frameRec.y = *currentAnimation * orc->frameHeight;
    orc->frameRec.height = orc->frameHeight;
}


void Moveorc(Orc* orc, OrcAnimationState* currentAnimation, bool* isAttacking)
{
    if(IsKeyDown(KEY_W)) {
        *currentAnimation = *isAttacking?ORC_ATTACK:ORC_RUN;
        orc->dest.y--;
    } 
    else if(IsKeyDown(KEY_S)) {
        *currentAnimation = *isAttacking?ORC_ATTACK:ORC_RUN;
        orc->dest.y++;
    } 
    else if(IsKeyDown(KEY_A)) {
        *currentAnimation = *isAttacking?ORC_ATTACK:ORC_RUN;
        orc->flipSprite=true;
        orc->dest.x--;
    } 
    else if(IsKeyDown(KEY_D)) {
         *currentAnimation = *isAttacking?ORC_ATTACK:ORC_RUN;
        
        orc->flipSprite=false;
        orc->dest.x++;
    }
    
    else{
        *currentAnimation = *isAttacking ? ORC_ATTACK:ORC_IDLE;
        
    }
    
    if(IsKeyDown(KEY_SPACE))
    {
        *isAttacking=true;
        *currentAnimation=ORC_ATTACK;
    }
    else{
        *isAttacking=false;
    }

    if(!orc->isAlive)
    {
        *currentAnimation = ORC_DEATH;
        return;
    }
}

void OrcTakingDamage(Orc* orc, int damage, OrcAnimationState* currentAnimation)
{
    if(!orc->isAlive) return;
    
    orc->health -= damage;
    printf("\n %d = health", orc->health);
    if(orc->health <= 0)
    {
        orc->health = 0;
        orc->isAlive = false;
        
        // Update animation state to death if needed
        if (orc->isAlive == false) {
            *currentAnimation = ORC_DEATH;
            printf("\nDEAD\n");
            
            
        }
        
    }
    else
    {
        if(currentAnimation != NULL)
        {
            *currentAnimation=ORC_HIT;
            printf("\nHIT\n");
        }

    }
}       