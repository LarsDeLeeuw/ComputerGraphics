#include "Face.h"

Face::Face(int index0, int index1) {
    index_vec.push_back(index0);
    index_vec.push_back(index1);
}

Face::Face(int index0, int index1, int index2) {
    index_vec.push_back(index0);
    index_vec.push_back(index1);
    index_vec.push_back(index2);
}

Face::Face(int index0, int index1, int index2, int index3) {
    index_vec.push_back(index0);
    index_vec.push_back(index1);
    index_vec.push_back(index2);
    index_vec.push_back(index3);
}

Face::Face(int index0, int index1, int index2, int index3, int index4) {
    index_vec.push_back(index0);
    index_vec.push_back(index1);
    index_vec.push_back(index2);
    index_vec.push_back(index3);
    index_vec.push_back(index4);
}

void Face::addPoint(int index) {
    index_vec.push_back(index);
}
