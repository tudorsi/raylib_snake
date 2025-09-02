#include "Snake.h"
#include "raylib.h"
#include <deque>

Snake::Snake(int snake_size, SnakeDirection snake_direction)
    :m_direction(snake_direction){

        float segment_size = 20.0f;

        // generate snake segments
        for(int i = 0; i < snake_size; ++i){
            SnakeSegment snake_segment;
            snake_segment.m_position_vector ={
                (GetRenderWidth()/2.0f) - (i * segment_size), 
                GetRenderHeight()/2.0f
            };
            m_segments.push_back(snake_segment);

        }

    }


const std::deque<SnakeSegment>& Snake::getSnakeSegments() const{
    return m_segments;
}

SnakeDirection Snake::getDirection() const{

    return m_direction;
    
}

void Snake::moveSnake(){
    
    for(int i = m_segments.size(); i > 0; --i){

        m_segments[i].m_position_vector = m_segments[i-1].m_position_vector;

    }
  
    switch(m_direction){
        case SnakeDirection::MOVE_LEFT:
            m_segments[0].m_position_vector.x -= 20;
            break;

        case SnakeDirection::MOVE_RIGHT:
            m_segments[0].m_position_vector.x += 20;
            break;

        case SnakeDirection::MOVE_UP:
            m_segments[0].m_position_vector.y -= 20;
            break;

        case SnakeDirection::MOVE_DOWN:
            m_segments[0].m_position_vector.y += 20;
            break;

    };

}

void Snake::changeDirection(SnakeDirection direction){

    m_direction = direction;

}

bool Snake::checkCollisions() const{    
    return m_segments[0].m_position_vector.x <= 0 || 
        m_segments[0].m_position_vector.y <= 0 || 
        m_segments[0].m_position_vector.x >= GetRenderWidth() || 
        m_segments[0].m_position_vector.y >= GetRenderHeight();
}
