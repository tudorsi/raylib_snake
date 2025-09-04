#pragma once

#include <deque>
#include "SnakeSegment.h"

enum SnakeDirection {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
};

class Snake{
    private:
        std::deque<SnakeSegment> m_segments;
        SnakeDirection           m_direction;

    public:
        Snake(int snake_size, SnakeDirection direction);
        const std::deque<SnakeSegment>& getSnakeSegments() const;
        void drawSnake() const;
        SnakeDirection getDirection() const;
        void changeDirection(SnakeDirection direction);
        void moveSnake();
        bool checkCollisions() const;
        void handleSnack();
};
