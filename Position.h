
#ifndef POSITION_H
#define POSITION_H
#include "string"
#include "stdexcept"
    struct Position{
        int x,y;
        public:
        Position(int x, int y){
            if(x<0 || y<0){
                throw std::out_of_range("Position coordinate cant be less zero");
                this->x = x;
                this->y = y;
            }
        } 
    };

    
    
#endif
