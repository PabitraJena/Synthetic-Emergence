#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
#define CELL 12

#define ROWS (SCREEN_WIDTH / CELL)
#define COLS (SCREEN_HEIGHT / CELL)

#define ANT_COUNT 1

enum Board{
    DEAD = 0,
    ALIVE
};
typedef enum Board Board;

enum Direction{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};
typedef enum Direction Direction;

struct Ant{
    int x, y;
    Direction direction;
};
typedef struct Ant Ant;

Board Gen[ROWS][COLS];

void InitGen(){
    for (int x = 0; x < ROWS; x++){
        for (int y = 0; y < COLS; y++){
            Gen[x][y] = DEAD;
        }
    }
}

void InitAnts(Ant ants[], int count){
    for (int i = 0; i < count; i++){
        ants[i].x = ROWS / 2;
        ants[i].y = COLS / 2;
        ants[i].direction = rand() % 4;
    }
}

void UpdateAnt(Ant *ant){
    if (Gen[ant->x][ant->y] == DEAD){
        ant->direction = (ant->direction + 1) % 4;
        Gen[ant->x][ant->y] = ALIVE;
    }else{
        ant->direction = (ant->direction + 3) % 4;
        Gen[ant->x][ant->y] = DEAD;
    }

    switch (ant->direction){
    case UP:
        ant->y--;
        break;
    case DOWN:
        ant->y++;
        break;
    case LEFT:
        ant->x--;
        break;
    case RIGHT:
        ant->x++;
        break;
    }

    if (ant->x < 0){
        ant->x = ROWS - 1;
    }
    if (ant->x >= ROWS){
        ant->x = 0;
    }
    
    if (ant->y < 0){
        ant->y = COLS - 1;
    }
    if (ant->y >= COLS){
        ant->y = 0;
    }
}

void UpdateAnts(Ant ants[], int count){
    for (int i = 0; i < count; i++){
        UpdateAnt(&ants[i]);
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

void DrawAnts(Ant ants[], int count){
    for (int i = 0; i < count; i++){
        DrawRectangle(ants[i].x * CELL, ants[i].y * CELL, CELL, CELL, RED);
    }
}

int main(){
    srand(time(NULL));
    SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE | FLAG_WINDOW_UNDECORATED);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Langton's Ant");

    InitGen();

    Ant ants[ANT_COUNT];
    InitAnts(ants, ANT_COUNT);
    ants[0].direction = UP; // testing for highway

    float timer = 0.0f;
    float interval = 0.001f; // for highway 

    SetTargetFPS(144);
    while (!WindowShouldClose()){
        timer += GetFrameTime();
        while (timer >= interval){
            UpdateAnts(ants, ANT_COUNT);
            timer -= interval;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        DrawGen();
        DrawAnts(ants, ANT_COUNT);
        DrawGrid2D(SCREEN_WIDTH, SCREEN_HEIGHT, CELL);

        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}