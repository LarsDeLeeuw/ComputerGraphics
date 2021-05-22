#ifndef ENGINE_LINES2D_H
#define ENGINE_LINES2D_H

#include<list>
#include<cmath>
#include <chrono>

#include "Line2D.h"
#include "ZBuffer.h"

class Lines2D{
public:
    Lines2D(){

    }
    ~Lines2D(){
        for(auto i: lines){
            delete i;
        }
    }
    void addLine(Line2D& newLine){
        lines.push_back(&newLine);
    }
    std::list<Line2D*> getLines(){
        return lines;
    }
    img::EasyImage* drawLines(const int size, const img::Color backgroundcolor, bool zbuf = false);
    void draw_zbuf_line(ZBuffer & zbuffer, img::EasyImage & image, unsigned int x0, unsigned int y0,
            const double z0, unsigned int x1, unsigned int y1,const double z1, const img::Color &color);




private:
    std::list<Line2D*> lines;
};


#endif //ENGINE_LINES2D_H
