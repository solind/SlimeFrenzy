#include "raylib.h"

int main(){
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib Project");
    
    SetTargetFPS(60);
    int action = 0;
    const char* emotion = {"sad"};
    double startTime = GetTime();
    double currentTime = 0.0;
    double maxTime = 4;
    while(!WindowShouldClose()){
        BeginDrawing();
        currentTime = GetTime()-startTime;
        if(IsKeyDown(KEY_A)){
            action = 1;
            startTime = GetTime();
        }
        else{
            action = 0;
        }
        
        ClearBackground(WHITE);
        
        DrawCircle(300, 155, 50, DARKBROWN);//ear
        DrawCircle(500, 155, 50, DARKBROWN);//ear
        DrawCircle(400, 245, 120, BROWN); //head
        DrawCircle(330, 260, 10, BLACK); //eye
        DrawCircle(470, 260, 10, BLACK); //eye
        DrawCircle(400, 275, 50, DARKBROWN);
        DrawTriangle((Vector2){390, 260},
                    (Vector2){400, 270},
                    (Vector2){410, 260}, BLACK);//nose
        DrawTriangle((Vector2){400, 270},
                    (Vector2){375, 290},
                    (Vector2){425, 290}, BLACK);//mputh
        DrawTriangle((Vector2){400, 280},
                    (Vector2){375, 300},
                    (Vector2){425, 300}, DARKBROWN);//cover mouth
        
        DrawText("Press A to give attention", 250, 380, 20, LIGHTGRAY);
        switch(action){
            case 1:
                DrawText("Giving attention", 0, 50, 50, BLACK);
                break;
            default:
                break;
        }

        DrawText(emotion, 600, 225, 40, BLACK);
        if(currentTime>=maxTime){
            emotion = {"sad"};
        }
        else{
            emotion = {"happy"};
        }
        EndDrawing();
        
    }
    CloseWindow();
    return 0;
}