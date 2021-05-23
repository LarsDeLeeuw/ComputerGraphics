#include "easy_image.h"
#include "ini_configuration.h"
#include "EngineModules/_2DLSystemModule.h"
#include "EngineModules/_3DLineModule.h"

#include <fstream>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <list>
#include <cmath>



img::EasyImage generate_image(const ini::Configuration &configuration)
{
    img::EasyImage image;
    img::EasyImage* to_destroy;
    if(configuration["General"]["type"].as_string_or_die() == "2DLSystem"){
        _2DLSystemModule module = _2DLSystemModule(configuration);
        to_destroy = module.calculateFrame();
        image = *to_destroy;
        delete to_destroy;
    }
    else if(configuration["General"]["type"].as_string_or_die() == "Wireframe"){
        _3DLineModule module = _3DLineModule(configuration);
        to_destroy = module.calculateFrame();
        image = *to_destroy;
        delete to_destroy;
    }
    else if(configuration["General"]["type"].as_string_or_die() == "ZBufferedWireframe"){
        _3DLineModule module = _3DLineModule(configuration, true);
        to_destroy = module.calculateFrame();
        image = *to_destroy;
        delete to_destroy;
    }
    else if(configuration["General"]["type"].as_string_or_die() == "ZBuffering"){
        _3DLineModule module = _3DLineModule(configuration, true, true);
        to_destroy = module.calculateFrame();
        image = *to_destroy;
        delete to_destroy;
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
                        std::ifstream fileIn("3DFractals/filelist");
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
