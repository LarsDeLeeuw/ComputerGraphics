#include "Line2D.h"

Line2D::Line2D(Point2D &start, Point2D &end, img::Color &colour) {
    x0 = start;
    x1 = end;
    color = colour;
}

Line2D::Line2D(Point2D &start, Point2D &end, img::Color &colour, double zVal1, double zVal2) {
    x0 = start;
    x1 = end;
    color = colour;
    z1 = zVal1;
    z2 = zVal2;
}

Line2D::~Line2D(){

}