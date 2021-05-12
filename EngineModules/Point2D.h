#ifndef ENGINE_POINT2D_H
#define ENGINE_POINT2D_H


#include "../ini_configuration.h"

class Point2D {
public:
    Point2D(double x_input, double y_input){
        x = x_input;
        y = y_input;
    }
    Point2D(){
        x = 0;
        y = 0;
    }

    ~Point2D() = default;

    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    void setX(double new_x){
        x = new_x;
    }
    void setY(double new_y){
        y = new_y;
    }
    double x;
    double y;
};


#endif //ENGINE_POINT2D_H
