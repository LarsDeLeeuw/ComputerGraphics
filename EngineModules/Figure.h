#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <vector>
#include "../vector3d.h"
#include "Face.h"
#include "../easy_image.h"

class Figure {
public:
    void applyTransformation(const Matrix& M_t);
    std::vector<Face*> getFaces(){return faces;}
    img::Color* getColor(){return color;}

private:
    std::vector<Vector3D*> points;
    std::vector<Face*> faces;
    img::Color* color;
};



#endif //ENGINE_FIGURE_H
