#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H


#include "Point2D.h"
#include "../easy_image.h"

class Line2D {
public:
    Line2D(Point2D& start, Point2D &end, img::Color& colour);
    Line2D(Point2D& start, Point2D &end, img::Color& colour, double zVal1, double zVal2);
    ~Line2D();
    Point2D* x0;
    Point2D* x1;

    double z1 = 0;
    double z2 = 0;

    img::Color color;
};


#endif //ENGINE_LINE2D_H
