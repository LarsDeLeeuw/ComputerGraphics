#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H

#include <vector>
#include "../vector3d.h"
#include "Face.h"
#include "../easy_image.h"
#include "../ini_configuration.h"
#include "ZBuffer.h"


class Figure {
public:
    void divideTriangles();
    void rescalePoints();

    Figure() = default;
    Figure(const ini::Section &configuration, bool zbuf = false);
    void applyTransformation(const Matrix& M_t);
    std::vector<Face> getFaces(){return faces;}
    std::vector<Vector3D> getPoints(){return points;}
    img::Color* getColor(){return color;}

    void generateFractal(const int nr_iterations, const double scale);

    void triangulate();
    void draw_zbuf_triangles(ZBuffer& zbuffer, img::EasyImage& image, double d, double dx, double dy);
    void draw_zbuf_triag(ZBuffer& zbuffer, img::EasyImage& image, int indexA, int indexB, int indexC, double d, double dx, double dy);

    void genCube();
    void genTetrahedron();
    void genOctahedron();
    void genIcosahedron();
    void genDodecahedron();

    void genSphere(const int n);
    void genCone(const int n, const double h);
    void genCylinder(const int n, const double h);
    void genTorus(const int n,const int m, const double r,const double R);
    void genBuckyball();
    void genMengerSponge(const int nr_iterations);

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
