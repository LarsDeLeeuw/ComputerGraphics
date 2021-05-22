#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H


#include <vector>

class ZBuffer {
public:
    ZBuffer(const int width, const int height);
    double getValue(int x, int y);
    void setValue(int x, int y, double val);

private:
    std::vector<std::vector<double> > buffer;
};


#endif //ENGINE_ZBUFFER_H
