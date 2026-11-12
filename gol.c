#include <stdio.h>
#include "raylib.h"

void DrawGrid2D(int width, int height, int size){
    for (int x = 0; x < width; x += size){
        DrawLine(x, 0, x, height, DARKGRAY);
    }
    
    for (int y = 0; y < height; y += size){
        DrawLine(0, y, width, y, DARKGRAY);
    }
}

int main(){
    int screenWidth = 1280;
    int screenHeight = 720;
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Game Of Life");

    int Gen[screenWidth][screenHeight];
    int nextGen[screenWidth][screenHeight];

    SetTargetFPS(144);
    while (!WindowShouldClose()){
        if (IsWindowResized()){
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
        }
        BeginDrawing();
        ClearBackground(BLACK);

        DrawGrid2D(screenWidth, screenHeight, 12);

        DrawFPS(10, 10);
        EndDrawing();
    }
    return 0;
}