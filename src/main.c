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
#include "knight1.h"
#include "orc1.h"


#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

// init game screens
typedef enum GameScreen
{
    SplashScreen = 0,
    StartScreen,
    Level_1
} GameScreen;

int main(void)
{
    // init game screen 
    const int screenWidth = 1800;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "Knighty Knight");    
    
    // load knight sprite
    Knight knight;
    InitKnight(&knight, screenWidth, screenHeight);
    // load orc sprite
    Orc orc;
    InitOrc(&orc, screenWidth, screenHeight);
    
    // init frames
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
   
    // init current screen
    GameScreen currentScreen = Level_1;

    KnightAnimationState currentAnimationKnight = KNIGHT_IDLE;
    OrcAnimationState currentAnimationOrc = ORC_IDLE;

    bool knightFlipSprite = false;
    bool isAttacking = false;

    int fontSize = 50;
    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Game logic update
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
                UpdateOrc(&orc, currentAnimationOrc);
                MoveKnight(&knight, &currentAnimationKnight, &isAttacking);
                UpdateKnight(&knight, currentAnimationKnight);
                CheckKnightAttackCollision(&knight, &orc, &isAttacking, &currentAnimationOrc);
                OrcTakingDamage(&orc, orc.health, &currentAnimationOrc);
                //Moveorc(&orc, &currentAnimationOrc, &isAttacking);
                //CheckKnightAttackCollision(&knight, &orc, &isAttacking);
                //OrcTakingDamage(&orc, 50, &currentAnimationOrc);

                // Sprite flipping logic
                const float knight_BASE_WIDTH = knight.frameWidth;
                knight.frameRec.width = knightFlipSprite ? knight_BASE_WIDTH : -knight_BASE_WIDTH;

                // Animation frame logic
                framesCounter++;
                
                break;
            }
        }
        
        // Drawing
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

                RenderOrc(&orc);
                RenderKnight(&knight);
                
                // Optional: Draw bounding box for knight
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
    
    CloseWindow();
    return 0;    
}


