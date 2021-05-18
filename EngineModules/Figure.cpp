#include "Figure.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include "MatrixMath.h"

using namespace std;

void Figure::applyTransformation(const Matrix &M_t) {
    for(int i = 0; i < points.size(); i++){
        points[i] *= M_t;
    }
}

Figure::Figure(const ini::Section &configuration) {
    auto cache = configuration["color"].as_double_tuple_or_die();
    color = new img::Color(cache[0]*255, cache[1]*255, cache[2]*255);
    int nrPoints = configuration["nrPoints"].as_int_or_die();
    int nrLines = configuration["nrLines"].as_int_or_die();
    stringstream s;
    // Loop through every point, add them to point vector.
    for(int x = 0; x < nrPoints; x++){
        s.str("");
        s << "point" << x;
        cache = configuration[s.str()].as_double_tuple_or_die();
        Vector3D newPoint = Vector3D::point(cache[0], cache[1], cache[2]);
        points.push_back(newPoint);
    }
    // Loop through every face, add them to face vector.
    for(int x = 0; x < nrLines; x++){
        s.str("");
        s << "line" << x;
        auto cache1 = configuration[s.str()].as_int_tuple_or_die();
        Face newFace;
        if(cache1.size() == 2){
            newFace = Face(cache1[0], cache1[1]);
        }
        else{
            // TODO: Planar Face
            newFace = Face(cache1[0], cache1[1]);
        }

        faces.push_back(newFace);
    }
    scale = configuration["scale"].as_double_or_die();
    // TODO: Figure needs to be centered in (0, 0, 0)
    Matrix M = scaleFigure(1);
    if(scale != 1){
        M = scaleFigure(scale);
    }
    x_rot = configuration["rotateX"].as_double_or_die()*(M_PI/180);
    if(x_rot != 0){
        M *= rotateX(x_rot);
    }
    y_rot = configuration["rotateY"].as_double_or_die()*(M_PI/180);
    if(y_rot != 0){
        M *= rotateY(y_rot);
    }
    z_rot = configuration["rotateZ"].as_double_or_die()*(M_PI/180);
    if(z_rot != 0){
        M *= rotateZ(z_rot);
    }
    applyTransformation(M);
}

