#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
#define CELL 12

#define ROWS (SCREEN_WIDTH / CELL)
#define COLS (SCREEN_HEIGHT / CELL)

enum Board{
    DEAD = 0,
    ALIVE
};
typedef enum Board Board;

Board Gen[ROWS][COLS];
Board nextGen[ROWS][COLS];

int randomVal(int min, int max){
    return (min + rand() % (max - min + 1));
}

void InitGen(){
    for (int x = 0; x < ROWS; x++){
        for (int y = 0; y < COLS; y++){
            Gen[x][y] = (randomVal(0, 1) == 1) ? ALIVE : DEAD;
        }
    }
}

int countNeighbours(int x, int y){
    int count = 0;

    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            if (i == 0 && j == 0){
                continue;
            }

            int xw = x + i;
            int yw = y + j;

            if (xw >= 0 && xw < ROWS && yw >= 0 && yw < COLS){
                if (Gen[xw][yw] == ALIVE){
                    count++;
                }
            }
        }
    }

    return count;
}

void UpdateGen(){
    for (int x = 0; x < ROWS; x++){
        for (int y = 0; y < COLS; y++){
            int neigh = countNeighbours(x, y);

            if (Gen[x][y] == ALIVE){
                if (neigh < 2 || neigh > 3){
                    nextGen[x][y] = DEAD;
                }else{
                    nextGen[x][y] = ALIVE;
                }
            }else{
                if (neigh == 3){
                    nextGen[x][y] = ALIVE;
                }else{
                    nextGen[x][y] = DEAD;
                }
            }
        }
    }

    for (int x = 0; x < ROWS; x++){
        for (int y = 0; y < COLS; y++){
            Gen[x][y] = nextGen[x][y];
        }
    }
}

void DrawGen(){
    for (int x = 0; x < ROWS; x++){
        for (int y = 0; y < COLS; y++){
            if (Gen[x][y] == 1){
                DrawRectangle(x * CELL, y * CELL, CELL, CELL, BLACK);
            }
        }
    }
}

void DrawGrid2D(int width, int height, int size){
    for (int x = 0; x < width; x += size){
        DrawLine(x, 0, x, height, LIGHTGRAY);
    }
    
    for (int y = 0; y < height; y += size){
        DrawLine(0, y, width, y, LIGHTGRAY);
    }
}

int main(){
    srand(time(NULL));
    SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE | FLAG_WINDOW_UNDECORATED);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Of Life");

    InitGen();

    float timer = 0.0f;
    float interval = 0.1f;

    SetTargetFPS(144);
    while (!WindowShouldClose()){
        timer += GetFrameTime();
        if (timer >= interval){
            UpdateGen();
            timer = 0.0f;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        DrawGen();
        DrawGrid2D(SCREEN_WIDTH, SCREEN_HEIGHT, CELL);

        DrawFPS(10, 10);
        EndDrawing();
    }
    return 0;
}