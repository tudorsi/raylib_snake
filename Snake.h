#include <deque>
#include "SnakeSegment.h"

//TODO: Make method for moving snake (segment[i] moves to position of segment[i-1]

enum SnakeDirection {

    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT

};


class Snake{

   private:
       std::deque<SnakeSegment> m_segments;
       SnakeDirection m_direction;
   public:
       Snake(int snake_size, SnakeDirection direction);
       const std::deque<SnakeSegment>& getSnakeSegments() const;
       void changeDirection(SnakeDirection direction);


};
