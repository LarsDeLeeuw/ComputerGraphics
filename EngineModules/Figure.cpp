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
    if(configuration["type"].as_string_or_die() == "LineDrawing") {
        int nrPoints = configuration["nrPoints"].as_int_or_die();
        int nrLines = configuration["nrLines"].as_int_or_die();
        stringstream s;
        // Loop through every point, add them to point vector.
        for (int x = 0; x < nrPoints; x++) {
            s.str("");
            s << "point" << x;
            cache = configuration[s.str()].as_double_tuple_or_die();
            Vector3D newPoint = Vector3D::point(cache[0], cache[1], cache[2]);
            points.push_back(newPoint);
        }
        // Loop through every face, add them to face vector.
        for (int x = 0; x < nrLines; x++) {
            s.str("");
            s << "line" << x;
            auto cache1 = configuration[s.str()].as_int_tuple_or_die();
            Face newFace;
            if (cache1.size() == 2) {
                newFace = Face(cache1[0], cache1[1]);
            } else {
                // TODO: Planar Face
                newFace = Face(cache1[0], cache1[1]);
            }
            faces.push_back(newFace);
        }
    }
    else if(configuration["type"].as_string_or_die() == "Cube"){
        genCube();
    }
    else if(configuration["type"].as_string_or_die() == "Cone"){

    }
    else if(configuration["type"].as_string_or_die() == "Cylinder"){

    }
    else if(configuration["type"].as_string_or_die() == "Torus"){

    }
    else if(configuration["type"].as_string_or_die() == "Tetrahedron"){
        genTetrahedron();
    }
    else if(configuration["type"].as_string_or_die() == "Octahedron"){
        genOctahedron();
    }
    else if(configuration["type"].as_string_or_die() == "Icosahedron"){
        genIcosahedron();
    }
    else if(configuration["type"].as_string_or_die() == "Dodecahedron"){
        genDodecahedron();
    }
    else if(configuration["type"].as_string_or_die() == "Sphere"){

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

void Figure::genTetrahedron() {
    Vector3D newPoint = Vector3D::point(1,-1,-1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(-1,1,-1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(1,1,1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(-1,-1,1);
    points.push_back(newPoint);

    Face newFace = Face(0, 1, 2);
    faces.push_back(newFace);
    newFace = Face(1, 3, 2);
    faces.push_back(newFace);
    newFace = Face(0, 3, 1);
    faces.push_back(newFace);
    newFace = Face(0, 2, 3);
    faces.push_back(newFace);
}

void Figure::genCube() {
    Vector3D newPoint = Vector3D::point(-1,-1,1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(-1,1,-1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(1,1,1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(1,-1,-1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(-1,1,1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(-1,-1,-1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(1,-1,1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(1,1,-1);
    points.push_back(newPoint);

    Face newFace = Face(0, 4, 2, 6);
    faces.push_back(newFace);
    newFace = Face(4, 1, 7, 2);
    faces.push_back(newFace);
    newFace = Face(1, 5, 3, 7);
    faces.push_back(newFace);
    newFace = Face(5, 0, 6, 3);
    faces.push_back(newFace);
    newFace = Face(6, 2, 7, 3);
    faces.push_back(newFace);
    newFace = Face(0, 5, 1, 4);
}

void Figure::genOctahedron() {
    Vector3D newPoint = Vector3D::point(1,0,0);
    points.push_back(newPoint);
    newPoint = Vector3D::point(0,1,0);
    points.push_back(newPoint);
    newPoint = Vector3D::point(-1,0,0);
    points.push_back(newPoint);
    newPoint = Vector3D::point(0,-1,0);
    points.push_back(newPoint);
    newPoint = Vector3D::point(0,0,-1);
    points.push_back(newPoint);
    newPoint = Vector3D::point(0,0,1);
    points.push_back(newPoint);

    Face newFace = Face(0, 1, 5);
    faces.push_back(newFace);
    newFace = Face(1, 2, 5);
    faces.push_back(newFace);
    newFace = Face(2, 3, 5);
    faces.push_back(newFace);
    newFace = Face(3, 0, 5);
    faces.push_back(newFace);
    newFace = Face(1, 0, 4);
    faces.push_back(newFace);
    newFace = Face(2, 1, 4);
    faces.push_back(newFace);
    newFace = Face(3, 2, 4);
    faces.push_back(newFace);
    newFace = Face(0, 3, 4);
    faces.push_back(newFace);
}

void Figure::genIcosahedron() {
    Vector3D newPoint;
    for(int i = 1; i < 13; i++){
        // Allot of casting to double to play it safe.
        switch (i) {
            case 1:
                newPoint = Vector3D::point(0,0,(double)(sqrt(5))/(double)2);
                points.push_back(newPoint);
                break;
            case 2:
                newPoint = Vector3D::point(cos((double)((i-2)*2*M_PI)/(double)5),sin((double)((i-2)*2*M_PI)/(double)5),0.5);
                points.push_back(newPoint);
                break;
            case 3:
                newPoint = Vector3D::point(cos((double)((i-2)*2*M_PI)/(double)5),sin((double)((i-2)*2*M_PI)/(double)5),0.5);
                points.push_back(newPoint);
                break;
            case 4:
                newPoint = Vector3D::point(cos((double)((i-2)*2*M_PI)/(double)5),sin((double)((i-2)*2*M_PI)/(double)5),0.5);
                points.push_back(newPoint);
                break;
            case 5:
                newPoint = Vector3D::point(cos((double)((i-2)*2*M_PI)/(double)5),sin((double)((i-2)*2*M_PI)/(double)5),0.5);
                points.push_back(newPoint);
                break;
            case 6:
                newPoint = Vector3D::point(cos((double)((i-2)*2*M_PI)/(double)5),sin((double)((i-2)*2*M_PI)/(double)5),0.5);
                points.push_back(newPoint);
                break;
            case 7:
                newPoint = Vector3D::point(cos(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),sin(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),-0.5);
                points.push_back(newPoint);
                break;
            case 8:
                newPoint = Vector3D::point(cos(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),sin(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),-0.5);
                points.push_back(newPoint);
                break;
            case 9:
                newPoint = Vector3D::point(cos(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),sin(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),-0.5);
                points.push_back(newPoint);
                break;
            case 10:
                newPoint = Vector3D::point(cos(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),sin(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),-0.5);
                points.push_back(newPoint);
                break;
            case 11:
                newPoint = Vector3D::point(cos(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),sin(((double)M_PI/(double)5)+(double)((double)(i-7)*(double)2*(double)M_PI)/(double)5),-0.5);
                points.push_back(newPoint);
                break;
            case 12:
                newPoint = Vector3D::point(0,0,-(double)(sqrt(5))/(double)2);
                points.push_back(newPoint);
                break;
            default:
                cout << "Something went wrong in genIcosahedron";
        }
    }
    Face newFace = Face(0, 1, 2);
    faces.push_back(newFace);
    newFace = Face(0, 2, 3);
    faces.push_back(newFace);
    newFace = Face(0, 3, 4);
    faces.push_back(newFace);
    newFace = Face(0, 4, 5);
    faces.push_back(newFace);
    newFace = Face(0, 5, 1);
    faces.push_back(newFace);
    newFace = Face(1, 6, 2);
    faces.push_back(newFace);
    newFace = Face(2, 6, 7);
    faces.push_back(newFace);
    newFace = Face(2, 7, 3);
    faces.push_back(newFace);
    newFace = Face(3, 7, 8);
    faces.push_back(newFace);
    newFace = Face(3, 8, 4);
    faces.push_back(newFace);
    newFace = Face(4, 8, 9);
    faces.push_back(newFace);
    newFace = Face(4, 9, 5);
    faces.push_back(newFace);
    newFace = Face(5, 9, 10);
    faces.push_back(newFace);
    newFace = Face(5, 10, 1);
    faces.push_back(newFace);
    newFace = Face(1, 10, 6);
    faces.push_back(newFace);
    newFace = Face(11, 7, 6);
    faces.push_back(newFace);
    newFace = Face(11, 8, 7);
    faces.push_back(newFace);
    newFace = Face(11, 9, 8);
    faces.push_back(newFace);
    newFace = Face(11, 10, 9);
    faces.push_back(newFace);
    newFace = Face(11, 6, 10);
    faces.push_back(newFace);
}

void Figure::genDodecahedron() {
    genIcosahedron();
    Vector3D newPoint;
    std::vector<Vector3D> tempPoints;
    for(unsigned int i = 0; i < faces.size(); i++){
        newPoint = Vector3D::point((double)(points[faces[i].index_vec[0]].x + points[faces[i].index_vec[1]].x + points[faces[i].index_vec[2]].x)/(double)3,
                                   (double)(points[faces[i].index_vec[0]].y + points[faces[i].index_vec[1]].y + points[faces[i].index_vec[2]].y)/(double)3,
                                   (double)(points[faces[i].index_vec[0]].z + points[faces[i].index_vec[1]].z + points[faces[i].index_vec[2]].z)/(double)3);
        tempPoints.push_back(newPoint);
    }
    points = tempPoints;
    faces.clear();

    Face newFace = Face(0, 1, 2, 3, 4);
    faces.push_back(newFace);
    newFace = Face(0, 5, 6, 7, 1);
    faces.push_back(newFace);
    newFace = Face(1, 7, 8, 9, 2);
    faces.push_back(newFace);
    newFace = Face(2, 9, 10, 11, 3);
    faces.push_back(newFace);
    newFace = Face(3, 11, 12, 13, 4);
    faces.push_back(newFace);
    newFace = Face(4, 13, 14, 5, 0);
    faces.push_back(newFace);
    newFace = Face(19, 18, 17, 16, 15);
    faces.push_back(newFace);
    newFace = Face(19, 14, 13, 12, 18);
    faces.push_back(newFace);
    newFace = Face(18, 12, 11, 10, 17);
    faces.push_back(newFace);
    newFace = Face(17, 10, 9, 8, 16);
    faces.push_back(newFace);
    newFace = Face(16, 8, 7, 6, 15);
    faces.push_back(newFace);
    newFace = Face(15, 6, 5, 14, 19);
    faces.push_back(newFace);
}

