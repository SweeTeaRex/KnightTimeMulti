//
//
//  MMP""MM""YMM              `7MM"""Mq.                        `7MM"""Mq.
//  P'   MM   `7                MM   `MM.                         MM   `MM.
//       MM  .gP"Ya   ,6"Yb.    MM   ,M9  .gP"Ya `7M'   `MF'      MM   ,M9 `7Mb,od8 ,pW"Wq.   .P"Ybmmm `7Mb,od8 ,6"Yb.  `7MMpMMMb.pMMMb.  ,pP"Ybd
//       MM ,M'   Yb 8)   MM    MMmmdM9  ,M'   Yb  `VA ,V'        MMmmdM9    MM' "'6W'   `Wb :MI  I8     MM' "'8)   MM    MM    MM    MM  8I   `"
//       MM 8M""""""  ,pm9MM    MM  YM.  8M""""""    XMX          MM         MM    8M     M8  WmmmP"     MM     ,pm9MM    MM    MM    MM  `YMMMa.
//       MM YM.    , 8M   MM    MM   `Mb.YM.    ,  ,V' VA.        MM         MM    YA.   ,A9 8M          MM    8M   MM    MM    MM    MM  L.   I8
//     .JMML.`Mbmmd' `Moo9^Yo..JMML. .JMM.`Mbmmd'.AM.   .MA.    .JMML.     .JMML.   `Ybmd9'   YMMMMMb  .JMML.  `Moo9^Yo..JMML  JMML  JMML.M9mmmP'
//                                                                                           6'     dP
//                                                                                           Ybmmmd'
//
//
// Created by: Trey Adams


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <constants.h>
#include <knight1.h>


int main(void)
{
    // init game screen 
    const int screenWidth = 1800;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "RE_CLONE");    
    
    // load knight sprite
    Knight knight;
    Initknight(&knight, screenWidth, screenHeight);

    
    //Rectangle knightFrameRec = {0.0f, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT};

    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;
   
    
    // init current screen
    // GameScreen currentScreen = SplashScreen;
    GameScreen currentScreen = Level_1;

    knightAnimationState currentAnimation = IDLE;

    bool knightFlipSprite = false;
    bool isAttacking = false;

    
    
    int fontSize = 50;
    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
    
        switch(currentScreen)
        {
            case SplashScreen:
            {
                if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
                {
                    currentScreen = StartScreen;
                }
                break;
            }
            case StartScreen:
            {
                if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
                {
                    // Add any start screen logic here
                }
                break;
            }
            case Level_1:
            {
                // Syntax corrections:
                // 1. Fixed missing parenthesis
                // 2. Corrected variable declaration (removed '+')
                // 3. Fixed logical errors in key checking
                if(IsGamepadAvailable(0)) {
                    float axisX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
                    float axisY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
                    
                    // Gamepad movement logic
                    if(axisX != 0 || axisY != 0) {
                        currentAnimation = RUN;
                    } else {
                        currentAnimation = IDLE;
                    }
                
                }
                // Keyboard movement logic
                // Corrected logical OR/AND conditions
                if(IsKeyDown(KEY_W)) {
                    currentAnimation = isAttacking?ATTACK:RUN;
                    knight.dest.y--;
                } 
                else if(IsKeyDown(KEY_S)) {
                    currentAnimation = isAttacking?ATTACK:RUN;
                    knight.dest.y++;
                } 
                else if(IsKeyDown(KEY_A)) {
                    currentAnimation = isAttacking?ATTACK:RUN;
                    knightFlipSprite=false;
                    knight.dest.x--;
                } 
                else if(IsKeyDown(KEY_D)) {
                     currentAnimation = isAttacking?ATTACK:RUN;
                    currentAnimation = RUN;
                    knightFlipSprite=true;
                    knight.dest.x++;
                }
                
                else{
                    currentAnimation = isAttacking ? ATTACK:IDLE;
                    
                }
                
                if(IsKeyDown(KEY_SPACE))
                {
                    isAttacking=true;
                    currentAnimation=ATTACK;
                }
                else{
                    isAttacking=false;
                }
                //flip sprite
                const float knight_BASE_WIDTH = knight.frameWidth;

                knight.frameRec.width = knightFlipSprite ? knight_BASE_WIDTH : -knight_BASE_WIDTH;

                
                // Animation frame logic
                framesCounter++;
                
                if(framesCounter >= (60/framesSpeed)) {
                    framesCounter = 0;
                    currentFrame++;
                    
                    // Note: Changed knightFrameCounts to frameCounts
                    if(currentFrame >= knightFrameCounts[currentAnimation])
                        currentFrame = 0;
                    
                    // Note: Changed knightFrameRec to soldierFrameRec
                    knight.frameRec.x = currentFrame * knight.frameWidth;
                    knight.frameRec.y = currentAnimation * knight.frameHeight;
                    
                    knight.frameRec.height = knight.frameHeight;
                }
                
                break;
            }
            
        
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
        
        switch(currentScreen)
        {
            case SplashScreen:
            {
                DrawText("SplashScreen", (screenWidth/2), 5, 50, BLACK);
                int xButtonWidth = MeasureText("Press X Button", fontSize);

                DrawText("Press X Button", (screenWidth/2)-(xButtonWidth/2), screenHeight-fontSize, 50, BLACK);
                break;
            }
            case StartScreen:
            {
                DrawText("StartScreen", (screenWidth/2), 5, 50, BLACK);
                 int startButtonWidth = MeasureText("Press Start Button", fontSize);

                DrawText("Press Start Button", (screenWidth/2)-(startButtonWidth/2), screenHeight-fontSize, 50, BLACK);
                
                break;
            }
            case Level_1:
            {
                DrawText("Level 1", (screenWidth/2), 5, 50, BLACK);

                
                Renderknight(&knight);
                //DrawTextureRec(knight, knightFrameRec, position, WHITE);

                //DrawTextureEx(knight, position, 0.0f, scale, WHITE);

                DrawRectangleLines(
                    knight.origin.x+(screenWidth/2)-(knight.frameRec.width*knight.scale/2), 
                    knight.origin.y+(screenHeight/2)-(knight.frameRec.height*knight.scale/2), 
                    knight.frameRec.width*knight.scale, 
                    knight.frameRec.height*knight.scale, 
                    RED
                );
                break;
            }
        }
        
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;    


}


