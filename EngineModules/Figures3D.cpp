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
                    new_line = new Line2D(*storage[cacheF.index_vec[j]], *storage[cacheF.index_vec[(j+1)%k]], *figures[i]->getColor(), cachePoints[cacheF.index_vec[j]].z, cachePoints[cacheF.index_vec[(j+1)%k]].z);
                    projected_lines->addLine(*new_line);
                }
            }else{
                new_line = new Line2D(*storage[cacheF.index_vec[0]], *storage[cacheF.index_vec[1]], *figures[i]->getColor(), cachePoints[cacheF.index_vec[0]].z, cachePoints[cacheF.index_vec[1]].z);
                projected_lines->addLine(*new_line);
            }
        }
    }
    return projected_lines;
}

void Figures3D::addFigure(Figure* newFigure) {
    figures.push_back(newFigure);
}

void Figures3D::triangulateFigures() {
    for(auto i : figures){
        i->triangulate();
    }
}

img::EasyImage* Figures3D::draw_zbuf_triangles(const int size, const img::Color backgroundcolor) {
    Lines2D* lines2d = doProjection();
    std::list<Line2D*> lines = lines2d->getLines();
    Line2D* temp = *(lines.begin());
    double largestX = temp->x1->x;
    double smallestX = temp->x0->x;
    double largestY = temp->x1->y;
    double smallestY = temp->x0->y;
    for(auto i: lines){
        if(i->x0->x < smallestX)smallestX = i->x0->x;
        if(i->x1->x < smallestX)smallestX = i->x1->x;
        if(i->x0->y < smallestY)smallestY = i->x0->y;
        if(i->x1->y < smallestY)smallestY = i->x1->y;
        if(i->x0->x > largestX)largestX = i->x0->x;
        if(i->x1->x > largestX)largestX = i->x1->x;
        if(i->x0->y > largestY)largestY = i->x0->y;
        if(i->x1->y > largestY)largestY = i->x1->y;
    }
    double xrange = std::fabs(largestX) + std::fabs(smallestX); double yrange = std::fabs(largestY) + std::fabs(smallestY);
    img::EasyImage* image = new img::EasyImage(size*((xrange)/std::max(xrange, yrange)), size*((yrange)/std::max(xrange, yrange)), backgroundcolor);
    double scale = 0.95*image->get_width()/xrange;
    double DCx = scale*(smallestX + largestX)/2;
    double DCy = scale*(smallestY + largestY)/2;
    double dx = image->get_width()/2 - DCx;
    double dy = image->get_height()/2 -DCy;
    ZBuffer* zbuffer = new ZBuffer(image->get_width(), image->get_height());
    for(int j = 0; j < figures.size(); j++) {
        figures[j]->draw_zbuf_triangles(*zbuffer, *image, scale, dx, dy);
    }
    return image;
}
