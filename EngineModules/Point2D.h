#ifndef ENGINE_POINT2D_H
#define ENGINE_POINT2D_H


class Point2D {
public:
    Point2D(double x_input, double y_input){
        x = x_input;
        y = y_input;
    }
    Point2D(){

    }
    double x;
    double y;
};


#endif //ENGINE_POINT2D_H
