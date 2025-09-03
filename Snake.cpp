#include "Snake.h"
#include "raylib.h"
#include <deque>
#include <iostream>

const float SEGMENT_SIZE = 20.0f;
Snake::Snake(int snake_size, SnakeDirection snake_direction)
    :m_direction(snake_direction){


        // generate snake segments
        for(int i = 0; i < snake_size; ++i){
            SnakeSegment snake_segment;
            snake_segment.m_position_vector ={
                (GetRenderWidth()/2.0f) - (i * SEGMENT_SIZE), 
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
//TODO: refine snake movement. Add one segment to front, remove one segment from the back using deque specific methods.
    Vector2 tmp_head_position = m_segments.front().m_position_vector;
     
    switch(m_direction){
        case SnakeDirection::MOVE_LEFT:
            m_segments.front().m_position_vector.x -= 20;
            break;

        case SnakeDirection::MOVE_RIGHT:
            m_segments.front().m_position_vector.x += 20;
            break;

        case SnakeDirection::MOVE_UP:
            m_segments.front().m_position_vector.y -= 20;
            break;

        case SnakeDirection::MOVE_DOWN:
            m_segments.front().m_position_vector.y += 20;
            break;

    };

    m_segments[1].m_position_vector = tmp_head_position;

    for(int i = m_segments.size()-1; i > 1; --i){

        m_segments[i].m_position_vector = m_segments[i-1].m_position_vector;

    }
 

}

void Snake::changeDirection(SnakeDirection direction){

    m_direction = direction;

}

bool Snake::checkCollisions() const{ 

    //check collision with self
    //we start from 3rd segment as head allways collides with self and neighbour segment
    for(size_t i = 2; i < m_segments.size(); ++i){
        Rectangle head_rectangle = {
            m_segments.front().m_position_vector.x,
            m_segments.front().m_position_vector.y,
            SEGMENT_SIZE,
            SEGMENT_SIZE
        };

        Rectangle current_rectangle = {
            m_segments[i].m_position_vector.x,
            m_segments[i].m_position_vector.y,
            SEGMENT_SIZE,
            SEGMENT_SIZE
        };

        if(CheckCollisionRecs(head_rectangle,current_rectangle)){
            std::cerr << "Head collides with element number " << i;
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
