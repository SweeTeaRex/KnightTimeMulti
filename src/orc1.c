#include "orc1.h"

void Initorc(Orc* orc, int screenWidth, int screenHeight) {
    orc->screenWidth = screenWidth;
    orc->screenHeight = screenHeight;
    orc->texture = LoadTexture("assets/Soldier.png");
    orc->frameWidth = orc->texture.width/9.0;
    orc->frameHeight = orc->texture.height/7.0f;
    
    orc->scale = 6.0f;
    orc->position = (Vector2){
        orc->screenWidth/2-(orc->texture.width/9.0f*orc->scale/2),
        orc->screenHeight/2-(orc->texture.height/7.0f*orc->scale/2)
    };
    
    orc->origin = (Vector2){0.0f, 0.0f};
    orc->frameRec = (Rectangle){0.0f, 0.0f, orc->frameWidth, orc->frameHeight};
    orc->source = orc->frameRec;
    orc->dest = (Rectangle){
        orc->position.x,
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

void Renderorc(Orc* orc) {
    DrawTexturePro(orc->texture, orc->frameRec, orc->dest, 
                   orc->origin, 0.0f, WHITE);
}