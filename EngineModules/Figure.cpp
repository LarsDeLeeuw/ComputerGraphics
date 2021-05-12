#include "Figure.h"

void Figure::applyTransformation(const Matrix &M_t) {
    for(int i = 0; i < points.size(); i++){
        *points[i] *= M_t;
    }
}