#ifndef ENGINE__3DLSYSTEM_H
#define ENGINE__3DLSYSTEM_H


#include <set>
#include "../easy_image.h"
#include "../vector3d.h"
#include "Face.h"
#include "../ini_configuration.h"
#include "../l_parser.h"

class _3DLsystem {
public:
    _3DLsystem(const ini::Section &configuration);
    std::vector<Vector3D> getPoints();
    std::vector<Face> getFaces();

private:
    void getString(const LParser::LSystem3D &LSystem, std::string& replacedstring, int nriterations = 0);
    Vector3D H = Vector3D::point(1,0,0);
    Vector3D L = Vector3D::point(0,1,0);
    Vector3D U = Vector3D::point(0,0,1);
    double delta;
    std::set<char> alphabet;
    std::string initiator;
    std::string statement;
    unsigned int iterations;
    Vector3D currentpoint;
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    img::Color color;
};


#endif //ENGINE__3DLSYSTEM_H
