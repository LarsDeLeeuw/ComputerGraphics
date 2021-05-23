#include "Figure.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include <limits>
#include "MatrixMath.h"
#include "_3DLsystem.h"
#include "Point2D.h"

using namespace std;

inline int roundToInt(double d)
{
    return static_cast<int>(std::round(d));
}

double ddMod(double x, double y){
    // Small function that returns mod of doubles, with y > 0.
    if(x <= 0){
        x *= -1;
        if(x < y)return -1*x;
        else if (x == y)return 0;
        else{
            return -1*(x - (int)(x/y)*y);
        }
    }else{
        if(x < y)return x;
        else if (x == y)return 0;
        else{
            return (x - (int)(x/y)*y);
        }
    }
}



void Figure::applyTransformation(const Matrix &M_t) {
    for(int i = 0; i < points.size(); i++){
        points[i] *= M_t;
    }
}

Figure::Figure(const ini::Section &configuration, bool zbuf) {
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
                newFace = Face(cache1[0], cache1[1]);
            }
            faces.push_back(newFace);
        }
    }
    else if(configuration["type"].as_string_or_die() == "Cube"){
        genCube();
    }
    else if(configuration["type"].as_string_or_die() == "Sphere"){
        genSphere(configuration["n"].as_int_or_die());
    }
    else if(configuration["type"].as_string_or_die() == "Cylinder"){
        genCylinder(configuration["n"].as_int_or_die(), configuration["height"].as_double_or_die());
    }
    else if(configuration["type"].as_string_or_die() == "Torus"){
        genTorus(configuration["n"].as_int_or_die(), configuration["m"].as_int_or_die(),
                 configuration["r"].as_double_or_die(), configuration["R"].as_double_or_die());
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
    else if(configuration["type"].as_string_or_die() == "Cone"){
        genCone(configuration["n"].as_int_or_die(), configuration["height"].as_double_or_die());
    }
    else if(configuration["type"].as_string_or_die() == "3DLSystem"){
        _3DLsystem LSystem = _3DLsystem(configuration);
        points = LSystem.getPoints();
        faces = LSystem.getFaces();
        int i = points.size();

        cout << endl;
    }
    else if(configuration["type"].as_string_or_die() == "FractalCube"){
        genCube();
        generateFractal(configuration["nrIterations"].as_int_or_die(), configuration["fractalScale"].as_double_or_die());
    }
    else if(configuration["type"].as_string_or_die() == "FractalTetrahedron"){
        genTetrahedron();
        generateFractal(configuration["nrIterations"].as_int_or_die(), configuration["fractalScale"].as_double_or_die());
    }
    else if(configuration["type"].as_string_or_die() == "FractalOctahedron"){
        genOctahedron();
        generateFractal(configuration["nrIterations"].as_int_or_die(), configuration["fractalScale"].as_double_or_die());
    }
    else if(configuration["type"].as_string_or_die() == "FractalIcosahedron"){
        genIcosahedron();
        generateFractal(configuration["nrIterations"].as_int_or_die(), configuration["fractalScale"].as_double_or_die());
    }
    else if(configuration["type"].as_string_or_die() == "FractalDodecahedron"){
        genDodecahedron();
        generateFractal(configuration["nrIterations"].as_int_or_die(), configuration["fractalScale"].as_double_or_die());
    }
    else{
        cout << "Unknown type defined in Figure segment";
    }

    scale = configuration["scale"].as_double_or_die();
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
    cache = configuration["center"].as_double_tuple_or_die();
    M *= translate(Vector3D::point(cache[0], cache[1], cache[2]));
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
    faces.push_back(newFace);
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

void Figure::genSphere(const int n) {
    genIcosahedron();
    for(int i = 0; i < n; i++){
        divideTriangles();
    }
    rescalePoints();
}

void Figure::divideTriangles() {
    std::vector<Face> moreFaces;
    // This for loop is not multithread friendly, new points get added to points vector and their index for the faces are calculated with points.size().
    for(int i = 0; i < faces.size(); i++){
        int s = points.size();
        Vector3D A = points[faces[i].index_vec[0]];
        Vector3D B = points[faces[i].index_vec[1]];
        Vector3D C = points[faces[i].index_vec[2]];
        Vector3D D = Vector3D::point((double)(A.x + B.x)/(double)2,(double)(A.y + B.y)/(double)2 ,(double)(A.z + B.z)/(double)2);
        points.push_back(D);
        Vector3D E = Vector3D::point((double)(A.x + C.x)/(double)2,(double)(A.y + C.y)/(double)2 ,(double)(A.z + C.z)/(double)2);
        points.push_back(E);
        Vector3D F = Vector3D::point((double)(C.x + B.x)/(double)2,(double)(C.y + B.y)/(double)2 ,(double)(C.z + B.z)/(double)2);
        points.push_back(F);
        //ADE
        Face newFace = Face(faces[i].index_vec[0], s, s+1);
        moreFaces.push_back(newFace);
        //BFD
        newFace = Face(faces[i].index_vec[1], s+2, s);
        moreFaces.push_back(newFace);
        //CEF
        newFace = Face(faces[i].index_vec[2], s+1, s+2);
        moreFaces.push_back(newFace);
        //DFE
        newFace = Face(s, s+2, s+1);
        moreFaces.push_back(newFace);
    }
    faces.clear();
    faces = moreFaces;
}

void Figure::rescalePoints() {
    int numPoints = points.size();
    for(int i = 0; i < numPoints; i++){
        points[i].normalise();
    }
}

void Figure::genCone(const int n, const double h) {
    points.push_back(Vector3D::point(0, 0, h));
    points.push_back(Vector3D::point(cos(0), sin(0), 0));
    Face newFace;
    for(int i = 1; i < n; i++){
        points.push_back(Vector3D::point(cos((double)(2*i*M_PI)/(double)n), sin((double)(2*i*M_PI)/(double)n), 0));
        newFace = Face(i, i+1, 0);
        faces.push_back(newFace);
    }
    faces.push_back(Face(n, 1, 0));
    newFace = Face();
    for(int i = 1; i < n+1; i++){
        newFace.addPoint(i);
    }
    faces.push_back(newFace);
}

void Figure::genCylinder(const int n, const double h) {
    // All points with an even index (0 included) are part of upper surface.

    // Generate sides.
    points.push_back(Vector3D::point(cos(0), sin(0), h));
    points.push_back(Vector3D::point(cos(0), sin(0), 0));
    Face newFace;
    int indexRef = 0;
    for(int i = 1; i < n; i++){
        points.push_back(Vector3D::point(cos((double)(2*i*M_PI)/(double)n), sin((double)(2*i*M_PI)/(double)n), h));
        points.push_back(Vector3D::point(cos((double)(2*i*M_PI)/(double)n), sin((double)(2*i*M_PI)/(double)n), 0));
        newFace = Face(indexRef, indexRef+1,  indexRef+3, indexRef+2);
        indexRef += 2;
        faces.push_back(newFace);
    }
    faces.push_back(Face(indexRef, indexRef+1, 1, 0));

    // Generate surfaces
    newFace = Face();
    Face topFace = Face();
    for(int i = 0; i < 2*n; i++){
        if(i%2 == 0){
            topFace.addPoint(i);
        }
        else{
            newFace.addPoint(i);
        }
    }
    faces.push_back(newFace);
    faces.push_back(topFace);
}

void Figure::genTorus(const int n, const int m, const double r, const double R) {
    // Generates Torus with parameterequation, n is the number of circles the torus is divided in, m are the amount of points per circle.
    // I first calculate the first circle, then I start the main loop and start calculating the rest of the points, when I calculated the new points
    // I also create the faces, when I create the faces I also use a loop for every face except the face that connects m-1 to 0.
    double u = 0;
    double v = 0;
    int indexRef = 0;
    for(int j = 0; j < m; j++){
        v = (double)(2*j*M_PI)/(double)m;
        points.push_back(Vector3D::point((R + r* cos(v))*cos(u),(R + r* cos(v))*sin(u), r*sin(v)));
    }
    for(int i = 1; i < n; i++){
        for(int j = 0; j < m; j++){
            u = (double)(2*i*M_PI)/(double)n;
            v = (double)(2*j*M_PI)/(double)m;
            points.push_back(Vector3D::point((R + r* cos(v))*cos(u),(R + r* cos(v))*sin(u), r*sin(v)));
        }
        for(int k = 1; k < m; k++){
            faces.push_back(Face(indexRef, indexRef+1, indexRef+1+m, indexRef+m));
            indexRef++;
        }
        faces.push_back(Face(indexRef, indexRef-m+1, indexRef+1, indexRef+m));
        indexRef++;
    }
    for(int k = 0; k < m-1; k++){
        faces.push_back(Face(indexRef, indexRef+1, k+1, k));
        indexRef++;
    }
    faces.push_back(Face(indexRef, indexRef-m+1, 0, m-1));
}

void Figure::triangulate() {
    vector<Face> newFaces;
    for(auto face : faces){
        vector<int> indexVecCache = face.index_vec;
        int faceSize = indexVecCache.size();
        if(faceSize > 3){
            for(int i = 1; i <= faceSize-2; i++){
                   newFaces.push_back(Face(indexVecCache[0], indexVecCache[i], indexVecCache[i+1]));
            }
        }
        else{
            newFaces.push_back(face);
        }
    }
    faces = newFaces;
}

void Figure::draw_zbuf_triangles(ZBuffer &zbuffer, img::EasyImage &image, double d, double dx, double dy) {
    for(int w = 0; w < faces.size();w++){
        draw_zbuf_triag(zbuffer, image, faces[w].index_vec[0], faces[w].index_vec[1], faces[w].index_vec[2], d, dx, dy);
//        img::Color* newcolor = new img::Color(ddMod(color->red+20, 130) + 30, ddMod(color->green+20, 130) + 30, ddMod(color->blue+20, 130) + 30);
//        delete color;
//        color = newcolor;
    }
}

void Figure::draw_zbuf_triag(ZBuffer &zbuffer, img::EasyImage &image, int indexA, int indexB, int indexC, double d, double dx, double dy) {
    Point2D projA = Point2D((d*(points[indexA].x))/(-1*(points[indexA].z)) + dx, (d*(points[indexA].y))/(-1*(points[indexA].z)) + dy);
    Point2D projB = Point2D((d*(points[indexB].x))/(-1*(points[indexB].z)) + dx, (d*(points[indexB].y))/(-1*(points[indexB].z)) + dy);
    Point2D projC = Point2D((d*(points[indexC].x))/(-1*(points[indexC].z)) + dx, (d*(points[indexC].y))/(-1*(points[indexC].z)) + dy);
    int yMin = roundToInt(std::min(std::min(projA.y, projB.y), projC.y) + 0.5);
    int yMax = roundToInt(std::max(std::max(projA.y, projB.y), projC.y) - 0.5);
    double xG = (projA.x + projB.x + projC.x)/(double)3;
    double yG = (projA.y + projB.y + projC.y)/(double)3;
    double zG = 1/(3*points[indexA].z) + 1/(3*points[indexB].z) + 1/(3*points[indexC].z);
    Vector3D u = Vector3D::point(points[indexB].x - points[indexA].x,
                                 points[indexB].y - points[indexA].y,
                                 points[indexB].z - points[indexA].z);
    Vector3D v = Vector3D::point(points[indexC].x - points[indexA].x,
                                 points[indexC].y - points[indexA].y,
                                 points[indexC].z - points[indexA].z);
    Vector3D w = Vector3D::point(u.y*v.z - u.z*v.y,
                                 u.z*v.x - u.x*v.z,
                                 u.x*v.y - u.y*v.x);
    double kval = points[indexA].x*w.x + points[indexA].y*w.y + points[indexA].z*w.z;

//    Vector3D u = points[indexB] - points[indexA];
//    Vector3D v = points[indexC] - points[indexA];
//    Vector3D w = u.cross_equals(v);
//    double kval = w.dot(points[indexA]);

    for(int i = yMin; i <= yMax; i++){
        int numOfSuccesTest = 0;
        double xLAB = std::numeric_limits<double>::infinity();
        double xLAC = std::numeric_limits<double>::infinity();
        double xLBC = std::numeric_limits<double>::infinity();
        double xRAB = -std::numeric_limits<double>::infinity();
        double xRAC = -std::numeric_limits<double>::infinity();
        double xRBC = -std::numeric_limits<double>::infinity();
        int xL = 0;
        int xR = 0;
        if((i-projA.y)*(i-projB.y) <= 0 && projA.y != projB.y){
            xLAB = projB.x + (projA.x - projB.x)*((i-projB.y)/(projA.y - projB.y));
            xRAB = xLAB;
            numOfSuccesTest++;
        }
        if((i-projA.y)*(i-projC.y) <= 0 && projA.y != projC.y){
            xLAC = projC.x + (projA.x - projC.x)*((i-projC.y)/(projA.y - projC.y));
            xRAC = xLAC;
            numOfSuccesTest++;
        }
        if((i-projC.y)*(i-projB.y) <= 0 && projC.y != projB.y) {
            xLBC = projC.x + (projB.x - projC.x)*((i-projC.y)/(projB.y - projC.y));
            xRBC = xLBC;
            numOfSuccesTest++;
        }
        if(numOfSuccesTest == 2){
            xL = roundToInt(std::min(std::min(xLAB, xLAC), xLBC) + 0.5);
            xR = roundToInt(std::max(std::max(xRAB, xRAC), xRBC) - 0.5);
            for (int k = xL; k <= xR; k++)
            {
                int x = roundToInt(k);
                int y = roundToInt(i);
                double zval = 1.0001*zG + (x - xG)*((w.x)/(-d*kval)) + (y - yG)*((w.y)/(-d*kval));
                if(zbuffer.getValue(x, y) > zval){
                    image(x, y) = *color;
                    zbuffer.setValue(x, y, zval);
                }
            }
        }
    }
}

void Figure::generateFractal(const int nr_iterations, const double fracscale) {
    vector<vector<Face> > subfigures;
    subfigures.push_back(faces);
    vector<vector<Vector3D> > subpoints;
    subpoints.push_back(points);
    Matrix scaleMatrix = scaleFigure(1/fracscale);
    for(int i = 0; i < nr_iterations; i++){
        vector<vector<Face> > newSubFigures;
        vector<vector<Vector3D> > newSubPoints;
        for(int numOfFigures = 0; numOfFigures < subpoints.size(); numOfFigures++){
            for(int point = 0; point < subpoints[numOfFigures].size(); point++){
                Vector3D projP = subpoints[numOfFigures][point] * scaleMatrix;
                Matrix translateMatrix = translate(subpoints[numOfFigures][point]-projP);
                newSubFigures.push_back(subfigures[numOfFigures]);
                vector<Vector3D> temphold;
                for(int pointToProject = 0; pointToProject < subpoints[numOfFigures].size(); pointToProject++){
                    Vector3D tempVec = subpoints[numOfFigures][pointToProject]*scaleMatrix*translateMatrix;
                    temphold.push_back(tempVec);
                }
                newSubPoints.push_back(temphold);
            }
        }
        subfigures = newSubFigures;
        subpoints = newSubPoints;
    }
    points.clear();
    faces.clear();
    int indexRef = 0;
    for(int i = 0; i < subpoints.size(); i++){
        int subpointSize = subpoints[i].size();
        for(int j = 0; j < subpointSize ; j++){
            points.push_back(subpoints[i][j]);
        }
        int subfigureSize = subfigures[i].size();
        for(int j = 0; j < subfigureSize; j++){
            Face newFace = Face();
            vector<int> indexVecCache = subfigures[i][j].index_vec;
            for(int index = 0; index < indexVecCache.size(); index++){
                newFace.addPoint(indexVecCache[index] + indexRef);
            }
            faces.push_back(newFace);
        }
        indexRef += subpointSize;
    }
}

void Figure::genBuckyball() {

}

void Figure::genMengerSponge(const int nr_iterations) {

}

