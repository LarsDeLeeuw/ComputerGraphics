#include "Lines2D.h"

img::EasyImage* Lines2D::drawLines(const int size, const img::Color backgroundcolor){
    if(lines.size()==0){
        std::cout << "There were no lines to draw";
        img::EasyImage* image = new img::EasyImage();
        return image;
    }
    auto start = std::chrono::high_resolution_clock::now();
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
    for(auto i : lines){
        image->draw_line(dx + scale * (i->x0->x), dy + scale * (i->x0->y),
                         dx + scale * (i->x1->x), dy + scale * (i->x1->y), i->color);

    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds >(stop - start);

    std::cout << "Actual drawing time: " << duration.count() << "ms\n"<< "Number of lines drawn: " << lines.size() << "\n"<<std::endl;

    std::cout.flush();

    return image;
}