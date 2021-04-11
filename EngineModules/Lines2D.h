#ifndef ENGINE_LINES2D_H
#define ENGINE_LINES2D_H

#include<list>

#include "Line2D.h"

class Lines2D{
public:
    Lines2D(){

    }
    ~Lines2D(){

    }
    void addLine(Line2D& newLine){
        lines.push_back(newLine);
    }
    std::list<Line2D> getLines(){
        return lines;
    }
    img::EasyImage& drawLines(const int size, const std::vector<int> backgroundcolor){
        img::Color background = img::Color(255**(backgroundcolor.begin()), 255**(backgroundcolor.begin() + 1), 255**(backgroundcolor.begin() + 2));
        int largestX = lines.begin()->x1.x;
        int smallestX = lines.begin()->x0.x;
        int largestY = lines.begin()->x1.y;
        int smallestY = lines.begin()->x0.y;
        for(auto i: lines){
            if(i.x0.x < smallestX)smallestX = i.x0.x;
            if(i.x0.y < smallestY)smallestY = i.x0.y;
            if(i.x1.x > largestX)largestX = i.x1.x;
            if(i.x1.y > largestY)largestY = i.x1.y;
        }
        int xrange = std::abs(largestX) + std::abs(smallestX); int yrange = std::abs(largestY) + std::abs(smallestY);
        img::EasyImage* image = new img::EasyImage(size*((xrange)/std::max(xrange, yrange)), size*((yrange)/std::max(xrange, yrange)), background);
        double scale = 0.95*image->get_width()/xrange;
        for(auto i : lines){
            image->draw_line(scale*i.x0.x, scale*i.x0.y, scale*i.x1.x, scale*i.x1.y, i.color);
        }
        return *image;
    }

private:
    std::list<Line2D> lines;
};


#endif //ENGINE_LINES2D_H
