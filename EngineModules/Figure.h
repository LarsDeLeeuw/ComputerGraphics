#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <vector>
#include "../vector3d.h"
#include "Face.h"
#include "../easy_image.h"
#include "../ini_configuration.h"


class Figure {
public:
    Figure() = default;
    Figure(const ini::Section &configuration);
    void applyTransformation(const Matrix& M_t);
    std::vector<Face> getFaces(){return faces;}
    std::vector<Vector3D> getPoints(){return points;}
    img::Color* getColor(){return color;}

private:
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    img::Color* color = nullptr;
    Vector3D center;
    double scale = 1;
    double x_rot = 0;
    double y_rot = 0;
    double z_rot = 0;
};



#endif //ENGINE_FIGURE_H
