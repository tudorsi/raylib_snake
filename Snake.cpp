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
                400.0f - (i * segment_size * 1.25f), 
                300.0f
            };
            m_segments.push_back(snake_segment);

        }

    }


const std::deque<SnakeSegment>& Snake::getSnakeSegments() const{
    return m_segments;
}
