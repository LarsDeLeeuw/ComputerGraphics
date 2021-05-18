#include "_3DLineModule.h"
#include "MatrixMath.h"
#include "sstream"

using namespace std;

_3DLineModule::_3DLineModule(const ini::Configuration &configuration) {
    size = configuration["General"]["size"];
    auto cache = configuration["General"]["eye"].as_double_tuple_or_die();
    eye_point = Vector3D::point(cache[0], cache[1], cache[2]);
    cache = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    backgroundcolor = img::Color(cache[0]*255, cache[1]*255, cache[2]*255);
    Matrix transEye = genEyePointTransformation(eye_point);
    int numOfFigures = configuration["General"]["nrFigures"].as_int_or_die();
    stringstream s;
    // Create every figure.
    for(int x = 0; x < numOfFigures; x++){
        s.str("");
        s << "Figure" << x;
        Figure* newFigure = new Figure(configuration[s.str()]);
        figures.addFigure(newFigure);
    }
    figures.applyTransformation(transEye);
    lines = figures.doProjection();
}

img::EasyImage *_3DLineModule::calculateFrame() {
    return lines->drawLines(size, backgroundcolor);
}

