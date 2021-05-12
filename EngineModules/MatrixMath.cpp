#include "../vector3d.h"
#include <cmath>

Matrix genEyePointTransformation(const Vector3D& point){
    double r = sqrt((pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2)));
    double theta = std::atan2(point.y, point.x);
    double phi = std::acos(point.z/r);
    Matrix M;
    M(1,1) = -sin(theta);
    M(1,2) = -cos(theta)*cos(phi);
    M(1, 3) = cos(theta)*sin(phi);
    M(2, 1) = cos(theta);
    M(2, 2) = -sin(theta)*cos(phi);
    M(2, 3) = sin(theta)*sin(phi);
    M(3, 2) = sin(phi);
    M(3, 3) = cos(phi);
    M(4, 3) = -r;
    return M;
}

Matrix scaleFigure(const double scale){
    Matrix M;
    for(int i = 1; i < 4; i++){
        M(i,i) = scale;
    }
    M(4,4) = 1;
    return M;
}

Matrix rotateX(const double angle){
    Matrix M;
    for(int i = 2; i < 4; i++){
        M(i,i) = cos(angle);
    }
    M(2,3) = sin(angle);
    M(3,2) = -sin(angle);
    return M;
}

Matrix rotateY(const double angle){
    Matrix M;
    M(1,1) = cos(angle);
    M(3,3) = cos(angle);
    M(3,1) = sin(angle);
    M(1,3) = -sin(angle);
    return M;
}

Matrix rotateZ(const double angle){
    Matrix M;
    for(int i = 1; i < 3; i++){
        M(i,i) = cos(angle);
    }
    M(1,2) = sin(angle);
    M(2,1) = -sin(angle);
    return M;
}

Matrix translate(const Vector3D& vector){
    Matrix M;
    M(4,1) = vector.x;
    M(4,2) = vector.y;
    M(4,3) = vector.z;
}
