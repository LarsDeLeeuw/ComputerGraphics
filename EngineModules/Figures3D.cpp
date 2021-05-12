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
        for(int k = 0; k < figures[i]->getPoints().size(); k++){
            storage.push_back(::doProjection(figures[i]->getPoints()[k],1));
        }
        for(int j = 0; j < figures[i]->getFaces().size(); j++){
            if(figures[i]->getFaces()[j].index_vec.size() == 2){
                Line2D* new_line = new Line2D(*storage[figures[i]->getFaces()[j].index_vec[0]], *storage[figures[i]->getFaces()[j].index_vec[1]], *figures[i]->getColor());
                projected_lines->addLine(*new_line);
            }
            else{
                std::cout << "Not implemented yet";
            }
        }
    }
    return projected_lines;
}

void Figures3D::addFigure(Figure* newFigure) {
    figures.push_back(newFigure);
}
