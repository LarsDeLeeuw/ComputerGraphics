#include "ZBuffer.h"
#include <limits>

ZBuffer::ZBuffer(const int width, const int height) {
    for(int i = 0; i < height; i++){
        buffer.push_back(std::vector<double>());
        for(int j = 0; j < width; j++){
            buffer[i].push_back(std::numeric_limits<double>::infinity());
        }
    }
}

double ZBuffer::getValue(int x, int y) {
    return buffer[y][x];
}

void ZBuffer::setValue(int x, int y, double val) {
    buffer[y][x] = val;
}
