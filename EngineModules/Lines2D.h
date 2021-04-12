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
    img::EasyImage& drawLines(const int size, const img::Color backgroundcolor){
        if(lines.size()==0){
            std::cout << "There were no lines to draw";
            img::EasyImage* image = new img::EasyImage();
            return *image;
        }
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
        double xrange = std::abs(largestX) + std::abs(smallestX); double yrange = std::abs(largestY) + std::abs(smallestY);
        img::EasyImage* image = new img::EasyImage(size*((xrange)/std::max(xrange, yrange)), size*((yrange)/std::max(xrange, yrange)), backgroundcolor);
        double scale = 0.95*image->get_width()/xrange;
        double DCx = scale*(smallestX + largestX)/2;
        double DCy = scale*(smallestY + largestY)/2;
        double dx = image->get_width()/2 - DCx;
        double dy = image->get_height()/2 -DCy;
        for(auto i : lines){

                image->draw_line(dx + scale * (i.x0.x), dy + scale * (i.x0.y),
                                 dx + scale * (i.x1.x), dy + scale * (i.x1.y), i.color);

        }

        return *image;
    }

private:
    std::list<Line2D> lines;
};


#endif //ENGINE_LINES2D_H
