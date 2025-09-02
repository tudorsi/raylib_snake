#include "Snake.h"
#include "raylib.h"
#include <memory>

void processKeyPresses(std::unique_ptr<Snake>& snake);

int main(){

    InitWindow(800,600, "Snake");
    SetTargetFPS(10);
    
    std::unique_ptr<Snake> snake = std::make_unique<Snake>(Snake(3, SnakeDirection::MOVE_LEFT));
    
    while(!WindowShouldClose()){
       
        processKeyPresses(snake);

        BeginDrawing();
            ClearBackground(BLACK);
            
            for (auto segment : snake->getSnakeSegments()){

                DrawRectangle(segment.m_position_vector.x, segment.m_position_vector.y,20.0f,20.0f, GREEN);

            }
    
        EndDrawing();
        snake->moveSnake();
    
    }

    return 0;
}

void processKeyPresses(std::unique_ptr<Snake>& snake){

        if(IsKeyPressed(KEY_UP) && snake->getDirection() != SnakeDirection::MOVE_DOWN){
            snake->changeDirection(SnakeDirection::MOVE_UP);
        }

        if(IsKeyPressed(KEY_DOWN) && snake->getDirection() != SnakeDirection::MOVE_UP){
            snake->changeDirection(SnakeDirection::MOVE_DOWN);
        }
  
        if(IsKeyPressed(KEY_LEFT) && snake->getDirection() != SnakeDirection::MOVE_RIGHT){
            snake->changeDirection(SnakeDirection::MOVE_LEFT);
        }

        if(IsKeyPressed(KEY_RIGHT) && snake->getDirection() != SnakeDirection::MOVE_LEFT){
            snake->changeDirection(SnakeDirection::MOVE_RIGHT);
        }

}
