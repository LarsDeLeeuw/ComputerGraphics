#ifndef ENGINE_MATRIXMATH_H
#define ENGINE_MATRIXMATH_H
Matrix genEyePointTransformation(const Vector3D& point);

Matrix scaleFigure(const double scale);

Matrix rotateX(const double angle);

Matrix rotateY(const double angle);

Matrix rotateZ(const double angle);

Matrix translate(const Vector3D& vector);
#endif //ENGINE_MATRIXMATH_H
