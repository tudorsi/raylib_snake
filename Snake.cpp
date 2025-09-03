#include "Snake.h"
#include "raylib.h"
#include <deque>

const float SEGMENT_SIZE = 20.0f;

Snake::Snake(int snake_size, SnakeDirection snake_direction)
    : m_direction(snake_direction){

     // generate snake segments
    for(int i = 0; i < snake_size; ++i){
        SnakeSegment snake_segment;
        snake_segment.m_position_vector ={
            (GetRenderWidth()/2.0f) + (i * SEGMENT_SIZE), 
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
    switch(m_direction){
        case SnakeDirection::MOVE_LEFT:
            m_segments.push_front(SnakeSegment{
                m_segments[0].m_position_vector.x - SEGMENT_SIZE,
                m_segments[0].m_position_vector.y
            });
            break;

        case SnakeDirection::MOVE_RIGHT:
            m_segments.push_front(SnakeSegment{
                m_segments[0].m_position_vector.x + SEGMENT_SIZE,
                m_segments[0].m_position_vector.y
            });
            break;

        case SnakeDirection::MOVE_UP:
            m_segments.push_front(SnakeSegment{
                m_segments[0].m_position_vector.x,
                m_segments[0].m_position_vector.y - SEGMENT_SIZE
            });
            break;

        case SnakeDirection::MOVE_DOWN:
            m_segments.push_front(SnakeSegment{
                m_segments[0].m_position_vector.x,
                m_segments[0].m_position_vector.y + SEGMENT_SIZE
            });
            break;
    };

    m_segments.pop_back();
}

void Snake::changeDirection(SnakeDirection direction){
    m_direction = direction;
}

bool Snake::checkCollisions() const{ 
    //check collision with self
    //we start from 3rd segment as head allways collides with self and neighbour segment
    
    const Vector2& head_pos = m_segments.front().m_position_vector;
    
    for(size_t i = 2; i < m_segments.size(); ++i){

        const Vector2& current_pos = m_segments[i].m_position_vector;

        if(head_pos.x == current_pos.x && head_pos.y == current_pos.y){
            return true;
        }
    }

    // check wall collision
    return m_segments[0].m_position_vector.x <= 0 || 
        m_segments[0].m_position_vector.y <= 0 || 
        m_segments[0].m_position_vector.x >= GetRenderWidth() || 
        m_segments[0].m_position_vector.y >= GetRenderHeight();
}

void Snake::handleSnack(){
    SnakeSegment snake_segment;
    
    snake_segment.m_position_vector ={
    m_segments.back().m_position_vector.x + SEGMENT_SIZE, 
    m_segments.back().m_position_vector.y
    };

    m_segments.push_back(snake_segment);
}
