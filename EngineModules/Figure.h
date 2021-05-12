#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <vector>
#include "../vector3d.h"
#include "Face.h"
#include "../easy_image.h"
#include "../ini_configuration.h"

class Figure {
public:
    Figure(const ini::Section &configuration);
    void applyTransformation(const Matrix& M_t);
    std::vector<Face> getFaces(){return faces;}
    std::vector<Vector3D> getPoints(){return points;}
    img::Color* getColor(){return color;}

private:
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    img::Color* color = nullptr;
};



#endif //ENGINE_FIGURE_H
