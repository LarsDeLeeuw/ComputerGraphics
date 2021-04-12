#ifndef ENGINE__2DLSYSTEMMODULE_H
#define ENGINE__2DLSYSTEMMODULE_H


#include <set>
#include "AbstractModule.h"
#include "../ini_configuration.h"
#include "Lines2D.h"
#include "../l_parser.h"


class _2DLSystemModule : public AbstractModule{
public:
    explicit _2DLSystemModule(const ini::Configuration &configuration);
    ~_2DLSystemModule();
    img::EasyImage& calculateFrame() override;
private:
    std::string& getString(const LParser::LSystem2D &LSystem, std::string& replacedstring, int nriterations = 0);
    double alpha;
    double delta;
    std::set<char> alphabet;
    std::map<char, bool> drawfunction;
    std::string initiator;
    std::string statement;
    unsigned int iterations;
    Point2D currentpoint;
    Lines2D lines;
    img::Color color;
    img::Color backgroundcolor;
    int size;
};


#endif //ENGINE__2DLSYSTEMMODULE_H
