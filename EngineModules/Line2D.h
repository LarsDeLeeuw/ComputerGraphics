#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H


#include "Point2D.h"
#include "../easy_image.h"

class Line2D {
public:
    Line2D(Point2D& start, Point2D &end, img::Color& colour){
        x0 = start;
        x1 = end;
        color = colour;
    }
    Point2D x0;
    Point2D x1;
    img::Color color;
};


#endif //ENGINE_LINE2D_H
