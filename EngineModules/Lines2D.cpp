#include "Lines2D.h"
#include "assert.h"

inline int roundToInt(double d)
{
    return static_cast<int>(std::round(d));
}

img::EasyImage* Lines2D::drawLines(const int size, const img::Color backgroundcolor, bool zbuf){
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
    ZBuffer* zbuffer = new ZBuffer(image->get_width(), image->get_height());
    if(!zbuf){
        for(auto i : lines){
            image->draw_line(roundToInt(dx + scale * (i->x0->x)), roundToInt(dy + scale * (i->x0->y)),
                             roundToInt(dx + scale * (i->x1->x)), roundToInt(dy + scale * (i->x1->y)), i->color);

        }
    }
    else{
        for(auto i : lines){
            draw_zbuf_line(*zbuffer, *image, roundToInt(dx + scale * (i->x0->x)), roundToInt(dy + scale * (i->x0->y)), i->z1,
                           roundToInt(dx + scale * (i->x1->x)), roundToInt(dy + scale * (i->x1->y)), i->z2, i->color);

        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds >(stop - start);

    std::cout << "Actual drawing time: " << duration.count() << "ms\n"<< "Number of lines drawn: " << lines.size() << "\n"<<std::endl;

    std::cout.flush();
    delete zbuffer;

    return image;
}

void Lines2D::draw_zbuf_line(ZBuffer & zbuffer, img::EasyImage & image, unsigned int x0, unsigned int y0, const double z0,
                             unsigned int x1, unsigned int y1, const double z1, const img::Color &color) {
    assert(x0 < image.get_width() && y0 < image.get_height());
    assert(x1 < image.get_width() && y1 < image.get_height());
    if (x0 == x1)
    {
        //special case for x0 == x1
        bool y0smallest =false;
        if(y0 == std::min(y0, y1))y0smallest = true;
        for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++)
        {
            double zval;
            if(y0smallest){
                zval = (double)(((y1-y0 -(i-y0))/(double)(y1 - y0))/z0)
                       + (double)((1-((y1-y0 -(i-y0))/(double)(y1 - y0)))/z1);
            }
            else{
                zval = (double)(((y0-y1 -(i-y1))/(double)(y0 - y1))/z1)
                       + (double)((1-((y0-y1 -(i-y1))/(double)(y0 - y1)))/z0);
            }
            if(zbuffer.getValue(x0, i) > zval){
                image(x0, i) = color;
                zbuffer.setValue(x0, i, zval);
            }
        }
    }
    else if (y0 == y1)
    {
        //special case for y0 == y1
        bool x0smallest =false;
        if(x0 == std::min(x0, x1))x0smallest = true;
        for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++)
        {
            double zval;
            if(x0smallest){
                zval = (double)(((x1-x0 -(i-x0))/(double)(x1 - x0))/z0)
                       + (double)((1-((x1-x0 -(i-x0))/(double)(x1 - x0)))/z1);
            }
            else{
                zval = (double)(((x0-x1 -(i-x1))/(double)(x0 - x1))/z1)
                       + (double)((1-((x0-x1 -(i-x1))/(double)(x0 - x1)))/z0);
            }
            if(zbuffer.getValue(i, y0) > zval){
                image(i, y0) = color;
                zbuffer.setValue(i, y0, zval);
            }
        }
    }
    else
    {
        if (x0 > x1)
        {
            //flip points if x1>x0: we want x0 to have the lowest value
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);
        if (-1.0 <= m && m <= 1.0)
        {
            for (unsigned int i = 0; i <= (x1 - x0); i++)
            {
                double zval = (double)(((x1 - x0 - i)/(double)(x1 - x0))/z0)
                              + (double)((1-((x1 - x0 - i)/(double)(x1 - x0)))/z1);
                if(zbuffer.getValue(x0 + i, (unsigned int) round(y0 + m * i)) > zval){
                    image(x0 + i, (unsigned int) round(y0 + m * i)) = color;
                    zbuffer.setValue(x0 + i, (unsigned int) round(y0 + m * i), zval);
                }
            }
        }
        else if (m > 1.0)
        {
            for (unsigned int i = 0; i <= (y1 - y0); i++)
            {
                double zval = (double)(((y1 - y0 - i)/(double)(y1 - y0))/z0)
                              + (double)((1-((y1 - y0 - i)/(double)(y1 - y0)))/z1);
                if(zbuffer.getValue((unsigned int) round(x0 + (i / m)), y0 + i) > zval){
                    image((unsigned int) round(x0 + (i / m)), y0 + i) = color;
                    zbuffer.setValue((unsigned int) round(x0 + (i / m)), y0 + i, zval);
                }
            }
        }
        else if (m < -1.0)
        {
            for (unsigned int i = 0; i <= (y0 - y1); i++)
            {
                double zval = (double)(((y0 - y1 - i)/(double)(y0 - y1))/z0)
                              + (double)((1-((y0 - y1 - i)/(double)(y0 - y1)))/z1);
                if(zbuffer.getValue((unsigned int) round(x0 - (i / m)), y0 - i) > zval){
                    image((unsigned int) round(x0 - (i / m)), y0 - i) = color;
                    zbuffer.setValue((unsigned int) round(x0 - (i / m)), y0 - i, zval);
                }
            }
        }
    }

}
