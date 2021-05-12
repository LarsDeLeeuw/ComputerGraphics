#include "Figure.h"
#include <sstream>

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
        Face newFace = Face(cache1[0], cache1[1]);
        faces.push_back(newFace);
    }
}

