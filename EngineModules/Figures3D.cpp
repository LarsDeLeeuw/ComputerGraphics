#include "Figures3D.h"

Point2D* doProjection(const Vector3D& point, const double d){
    Point2D* projected_point = new Point2D();
    projected_point->setX((d*point.x)/(-point.z));
    projected_point->setY((d*point.y)/(-point.z));
    return projected_point;
}

void Figures3D::applyTransformation(const Matrix &M_T) {
    for(int i = 0; i < figures.size(); i++){
        figures[i]->applyTransformation(M_T);
    }
}

Lines2D* Figures3D::doProjection(const double d) {
    Lines2D* projected_lines = new Lines2D();
    for(int i = 0; i < figures.size(); i++){
        std::vector<Point2D*> storage;
        auto cachePoints = figures[i]->getPoints();
        int numPoints = cachePoints.size();
        for(int k = 0; k < numPoints; k++){
            storage.push_back(::doProjection(cachePoints[k],d));
        }
        int numFaces = figures[i]->getFaces().size();
        auto cacheFaces = figures[i]->getFaces();
        for(int j = 0; j < numFaces; j++){
            auto cacheF = cacheFaces[j];
            int k = cacheF.index_vec.size();
            Line2D* new_line;
            if(k != 2){
                for(int j = 0; j < k; j++){
                    new_line = new Line2D(*storage[cacheF.index_vec[j]], *storage[cacheF.index_vec[(j+1)%k]], *figures[i]->getColor());
                    projected_lines->addLine(*new_line);
                }
            }else{
                new_line = new Line2D(*storage[cacheF.index_vec[0]], *storage[cacheF.index_vec[1]], *figures[i]->getColor());
                projected_lines->addLine(*new_line);
            }
        }
    }
    return projected_lines;
}

void Figures3D::addFigure(Figure* newFigure) {
    figures.push_back(newFigure);
}
