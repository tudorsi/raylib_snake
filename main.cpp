#include "Snake.h"
#include "raylib.h"
#include <cstdlib>
#include <memory>
#include<unistd.h>
#include "Snack.h"

const char* GAME_OVER_TEXT {"Game Over!"};
const int GAME_OVER_FONT_SIZE {20};
const float SEGMENT_SIZE {20.0};
const int SNAKE_INITIAL_SIZE {3};

void processKeyPresses(std::unique_ptr<Snake>& snake);
Vector2 generateSnackPosition();
bool checkSnackCollision(const std::unique_ptr<Snake>& snake, const std::unique_ptr<Snack>& snack);

int main(){
    InitWindow(800,600, "Snake");
    
    const int GAME_OVER_POS_X {GetRenderWidth()/2 - MeasureText(GAME_OVER_TEXT, GAME_OVER_FONT_SIZE)};
    const int GAME_OVER_POS_Y {GetRenderHeight()/2};

    SetTargetFPS(10);

    std::unique_ptr<Snake> snake = std::make_unique<Snake>(Snake(SNAKE_INITIAL_SIZE, SnakeDirection::MOVE_LEFT));
    
    std::unique_ptr<Snack> snack = std::make_unique<Snack>(Snack());
    snack->m_snack_position = generateSnackPosition();

    while(!WindowShouldClose()){
        processKeyPresses(snake);

        BeginDrawing();
        
        ClearBackground(BLACK);
        snake->drawSnake();
        DrawRectangleV(snack->m_snack_position, {SEGMENT_SIZE, SEGMENT_SIZE}, RED);

        if(checkSnackCollision(snake,snack)){
            snake->handleSnack();
            snack->m_snack_position = generateSnackPosition();
        }
        
        //check wall/self collisions
        if(snake->checkCollisions()){
            DrawText(
                GAME_OVER_TEXT,
                GAME_OVER_POS_X, 
                GAME_OVER_POS_Y,
                GAME_OVER_FONT_SIZE,
                GREEN
            );

            EndDrawing();
            usleep(5*10e5);
            break;
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
    Rectangle snackRectangle{
        snack->m_snack_position.x, 
        snack->m_snack_position.y, 
        SEGMENT_SIZE, 
        SEGMENT_SIZE
    };

    Rectangle snakeRectangle{
        snake->getSnakeSegments().front().m_position_vector.x, 
        snake->getSnakeSegments().front().m_position_vector.y, 
        SEGMENT_SIZE, 
        SEGMENT_SIZE
    };

    return CheckCollisionRecs(snackRectangle, snakeRectangle);
}
