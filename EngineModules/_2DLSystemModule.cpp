#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stack>
#include "_2DLSystemModule.h"
#include "../l_parser.h"


double dMod(double x, double y){
    // Small function that returns mod of doubles, with y > 0.
    if(x <= 0){
        x *= -1;
        if(x < y)return -1*x;
        else if (x == y)return 0;
        else{
            return -1*(x - (int)(x/y)*y);
        }
    }else{
        if(x < y)return x;
        else if (x == y)return 0;
        else{
            return (x - (int)(x/y)*y);
        }
    }
}

_2DLSystemModule::_2DLSystemModule(const ini::Configuration &configuration) {
    std::ifstream lfile;
    lfile.open("2DLsystems/" + configuration["2DLSystem"]["inputfile"].as_string_or_die());
    LParser::LSystem2D LSystem;
    lfile >> LSystem;
    lfile.close();
    alpha = LSystem.get_starting_angle()*(M_PI/180);
    alphabet = LSystem.get_alphabet();
    delta = LSystem.get_angle()*(M_PI/180);
    iterations = LSystem.get_nr_iterations();
    initiator = LSystem.get_initiator();
    size = configuration["General"]["size"].as_int_or_die();
    backgroundcolor = img::Color(255*configuration["General"]["backgroundcolor"].as_double_tuple_or_die()[0], 255*configuration["General"]["backgroundcolor"].as_double_tuple_or_die()[1], 255*configuration["General"]["backgroundcolor"].as_double_tuple_or_die()[2]);
    color = img::Color(255*configuration["2DLSystem"]["color"].as_double_tuple_or_die()[0], 255*configuration["2DLSystem"]["color"].as_double_tuple_or_die()[1], 255*configuration["2DLSystem"]["color"].as_double_tuple_or_die()[2]);
    getString(LSystem, initiator);
    std::stack<std::pair<Point2D, double>> st;
    std::pair<Point2D, double> stor;
    for(char symbol : statement){
        if(alphabet.find(symbol) != alphabet.end()){
            if(LSystem.draw(symbol)){
                Point2D* temp1 = new Point2D(currentpoint.getX(), currentpoint.getY());
                currentpoint.setX(currentpoint.getX()+std::cos(alpha));
                currentpoint.setY(currentpoint.getY()+std::sin(alpha));
                Point2D* temp2 = new Point2D(currentpoint.getX(), currentpoint.getY());
                Line2D* newLine = new Line2D(*temp1, *temp2, color);
                lines.addLine(*newLine);
            }
            else{
                currentpoint.setX(currentpoint.getX()+std::cos(alpha));
                currentpoint.setY(currentpoint.getY()+std::sin(alpha));
            }
        }
        else{
            switch(symbol) {
                case '+':
                    alpha += delta;
                    alpha = dMod(alpha, 2*M_PI);
                    break;
                case '-':
                    alpha -= delta;
                    alpha = dMod(alpha, 2*M_PI);
                    break;
                case '(':
                    st.push(std::pair<Point2D, double>(currentpoint, alpha));
                    break;
                case ')':
                    stor = st.top();
                    st.pop();
                    currentpoint = stor.first;
                    alpha = stor.second;
                    break;
                default:
                    break;
            }
        }
    }
}

_2DLSystemModule::~_2DLSystemModule() {

}

img::EasyImage& _2DLSystemModule::calculateFrame() {
    return lines.drawLines(size, backgroundcolor);
}

std::string &_2DLSystemModule::getString(const LParser::LSystem2D &LSystem, std::string& replacedstring, int nriterations) {
    if(nriterations == iterations){
        statement = replacedstring;
        return replacedstring;
    }
    std::string iteratedstring;
    for(char symbol : replacedstring){
        if(alphabet.find(symbol) != alphabet.end()){
            iteratedstring += LSystem.get_replacement(symbol);
        }
        else {
            iteratedstring += symbol;
        }
    }
    return getString(LSystem, iteratedstring, nriterations+1);
}
