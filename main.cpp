#include "Snake.h"
#include "raylib.h"
#include <cstdlib>
#include <memory>
#include<unistd.h>
#include "Snack.h"

//TODO:tidy up main, extract logic into separate functions

void processKeyPresses(std::unique_ptr<Snake>& snake);
Vector2 generateSnackPosition();
bool checkSnackCollision(const std::unique_ptr<Snake>& snake, const std::unique_ptr<Snack>& snack);

int main(){
    
//    SetConfigFlags(FLAG_WINDOW_HIGHDPI);    
    InitWindow(800,600, "Snake");
    SetTargetFPS(10);

    std::unique_ptr<Snake> snake = std::make_unique<Snake>(Snake(3, SnakeDirection::MOVE_LEFT));

    std::unique_ptr<Snack> snack = std::make_unique<Snack>(Snack());
    snack->m_snack_position = generateSnackPosition();

    while(!WindowShouldClose()){
       
        processKeyPresses(snake);

        BeginDrawing();
        ClearBackground(BLACK);
        
        //draw snake
        for (auto segment : snake->getSnakeSegments()){

            DrawRectangle(segment.m_position_vector.x, segment.m_position_vector.y,20.0f,20.0f, GREEN);

        }

        //draw snack
        DrawRectangleV(snack->m_snack_position, {20,20}, RED);

        //check snack colision
        if(checkSnackCollision(snake,snack)){
            snake->handleSnack();
            snack->m_snack_position = generateSnackPosition();
        }
        
        //check wall collisions
        if(snake->checkCollisions()){
            DrawText(
                "Game Over!",
                GetRenderWidth()/2-MeasureText("Game Over!",16),
                GetRenderHeight()/2,
                16,
                GREEN
            );

            EndDrawing();
            usleep(5*10e5);
            break;
        }
 
//        snake->moveSnake();
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

Vector2 generateSnackPosition(){

   int display_range_x = GetRenderWidth() - 10 + 1;
   int display_range_y = GetRenderHeight() - 10 + 1;
   Vector2 snack_position = {
        1.0f * (std::rand() % display_range_x + 10),
        1.0f * (std::rand() % display_range_y + 10)
   };

   return snack_position;
}

bool checkSnackCollision(const std::unique_ptr<Snake>& snake, const std::unique_ptr<Snack>& snack){

    Rectangle snackRectangle = {
        snack->m_snack_position.x, 
        snack->m_snack_position.y, 
        20.0f, 
        20.0f
    };
    Rectangle snakeRectangle = {
        snake->getSnakeSegments().front().m_position_vector.x, 
        snake->getSnakeSegments().front().m_position_vector.y, 
        20.0f, 
        20.0f
    };

    return CheckCollisionRecs(snackRectangle,snakeRectangle);
}
