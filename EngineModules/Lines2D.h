#ifndef ENGINE_LINES2D_H
#define ENGINE_LINES2D_H

#include<list>
#include<cmath>
#include <chrono>

#include "Line2D.h"

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
    img::EasyImage* drawLines(const int size, const img::Color backgroundcolor);



private:
    std::list<Line2D*> lines;
};


#endif //ENGINE_LINES2D_H
