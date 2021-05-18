#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H


#include <vector>
#include "../vector3d.h"

class Face {
public:
    Face() = default;
    Face(int index0, int index1);
    std::vector<int> index_vec;
};


#endif //ENGINE_FACE_H
