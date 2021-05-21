#include "_3DLsystem.h"
#include "../ini_configuration.h"
#include "../l_parser.h"
#include "../easy_image.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <stack>

_3DLsystem::_3DLsystem(const ini::Section &configuration) {
    std::ifstream lfile;
    // TODO: Hoe werkt hun filesystem?
    lfile.open("3DFigure/" + configuration["inputfile"].as_string_or_die());
    LParser::LSystem3D LSystem;
    lfile >> LSystem;
    lfile.close();
    alphabet = LSystem.get_alphabet();
    delta = LSystem.get_angle()*(M_PI/180);
    iterations = LSystem.get_nr_iterations();
    initiator = LSystem.get_initiator();
    auto cache = configuration["color"].as_double_tuple_or_die();
    color = img::Color(255*cache[0], 255*cache[1], 255*cache[2]);
    getString(LSystem, initiator);
    std::stack<std::vector<Vector3D>> st;
    std::vector<Vector3D> stor;
    std::vector<Vector3D> tempHold;
    int indexRef = 0;
    for(char symbol : statement){
        if(alphabet.find(symbol) != alphabet.end()){
            if(LSystem.draw(symbol)){
                // Not the most efficient, duplicates also get added to the points vector. Optimisation not worth the hassle atm.
                Vector3D temp1 = Vector3D::point(currentpoint.x, currentpoint.y, currentpoint.z);
                points.push_back(temp1);
                currentpoint += H;
                Vector3D temp2 = Vector3D::point(currentpoint.x, currentpoint.y, currentpoint.z);
                points.push_back(temp2);
                faces.push_back(Face(indexRef, indexRef+1));
                indexRef += 2;
            }
            else{
                currentpoint.x += H.x;
                currentpoint.y += H.y;
                currentpoint.z += H.z;
            }
        }
        else{
            Vector3D H_new;
            Vector3D L_new;
            Vector3D U_new;
            switch(symbol) {
                case '+':
                    H_new = H*cos(delta) + L*sin(delta);
                    L_new = -1*H*sin(delta) + L*cos(delta);
                    H = H_new;
                    L = L_new;
                    break;
                case '-':
                    H_new = H*cos(-1*delta) + L*sin(-1*delta);
                    L_new = -1*H*sin(-1*delta) + L*cos(-1*delta);
                    H = H_new;
                    L = L_new;
                    break;
                case '^':
                    H_new = H*cos(delta) + U*sin(delta);
                    U_new = -1*H*sin(delta) + U*cos(delta);
                    H = H_new;
                    U = U_new;
                    break;
                case '&':
                    H_new = H*cos(-1*delta) + U*sin(-1*delta);
                    U_new = -1*H*sin(-1*delta) + U*cos(-1*delta);
                    H = H_new;
                    U = U_new;
                    break;
                case '\\':
                    L_new = L*cos(delta) - U*sin(delta);
                    U_new = L*sin(delta) + U*cos(delta);
                    L = L_new;
                    U = U_new;
                    break;
                case '/':
                    L_new = L*cos(-1*delta) - U*sin(-1*delta);
                    U_new = L*sin(-1*delta) + U*cos(-1*delta);
                    L = L_new;
                    L.normalise();
                    U = U_new;
                    U.normalise();
                    break;
                case '|':
                    H = H*-1;
                    L = L*-1;
                    break;
                case '(':
                    tempHold.clear();
                    tempHold.push_back(currentpoint);
                    tempHold.push_back(H);
                    tempHold.push_back(L);
                    tempHold.push_back(U);
                    st.push(tempHold);
                    break;
                case ')':
                    stor = st.top();
                    st.pop();
                    currentpoint = stor[0];
                    H = stor[1];
                    L = stor[2];
                    U = stor[3];
                    break;
                default:
                    std::cout << "Undefined symbol in 3DLsystem statementstring";
                    break;
            }
        }
    }
}

void _3DLsystem::getString(const LParser::LSystem3D &LSystem, std::string &replacedstring, int nriterations) {
    if(nriterations == iterations){
        statement = replacedstring;
        return;
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

std::vector<Vector3D> _3DLsystem::getPoints() {
    return points;
}

std::vector<Face> _3DLsystem::getFaces() {
    return faces;
}
