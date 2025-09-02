#include "Snake.h"
#include "raylib.h"
#include <memory>

int main(){

    InitWindow(800,600, "Snake");
    
    std::unique_ptr<Snake> snake = std::make_unique<Snake>(Snake(3, SnakeDirection::MOVE_UP));
    
    while(!WindowShouldClose()){
        BeginDrawing();
            for (auto segment : snake->getSnakeSegments()){

                DrawRectangle(segment.m_position_vector.x, segment.m_position_vector.y,20.0f,20.0f, GREEN);

            }
        EndDrawing();
    }

    return 0;
}
