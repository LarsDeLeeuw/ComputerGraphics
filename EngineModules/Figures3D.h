#ifndef ENGINE_FIGURES3D_H
#define ENGINE_FIGURES3D_H


#include <vector>
#include "Figure.h"
#include "Lines2D.h"

class Figures3D {
public:
    void applyTransformation(const Matrix& M_T);
    Lines2D* doProjection(const double d = 1);
    void addFigure(Figure* newFigure);
private:
    std::vector<Figure*> figures;
};



#endif //ENGINE_FIGURES3D_H
