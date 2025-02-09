#include "knight1.h"

void Initknight(Knight* knight, int screenWidth, int screenHeight) {
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
        knight->position.x,
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

void Renderknight(Knight* knight) {
    DrawTexturePro(knight->texture, knight->frameRec, knight->dest, 
                   knight->origin, 0.0f, WHITE);
}