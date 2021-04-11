#include "easy_image.h"
#include "ini_configuration.h"

#include <fstream>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <list>
#include <cmath>

class Point2D{
public:
    Point2D(double x_input, double y_input){
        x = x_input;
        y = y_input;
    }
    Point2D(){

    }
    double x;
    double y;
};

class Line2D{
public:
    Line2D(Point2D& start, Point2D &end, img::Color& colour){
        x0 = start;
        x1 = end;
        color = colour;
    }
    Point2D x0;
    Point2D x1;
    img::Color color;
};

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
    // Bro
    std::list<Line2D> lines;
};


img::EasyImage generate_image(const ini::Configuration &configuration)
{
    img::EasyImage image;
    if(configuration["General"]["type"].as_string_or_die() == "2DLSystem"){

    }
	return image;
}



int main(int argc, char const* argv[])
{
        auto start = std::chrono::high_resolution_clock::now();
        int retVal = 0;
        try
        {
                std::vector<std::string> args = std::vector<std::string>(argv+1, argv+argc);
                if (args.empty()) {
                        std::ifstream fileIn("2DLsystems/filelist");
                        std::string fileName;
                        while (std::getline(fileIn, fileName)) {
                                args.push_back(fileName);
                        }
                }
                for(std::string fileName : args)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(fileName);
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << fileName << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		//mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds >(stop - start);

        std::cout << duration.count() << std::endl;
        return retVal;
}
