#ifndef ENGINE_ABSTRACTMODULE_H
#define ENGINE_ABSTRACTMODULE_H


#include "../easy_image.h"

/*
 * This class serves as an abstract object for the other modules to inherit from.
 */
class AbstractModule {
    AbstractModule(){}
    ~AbstractModule(){}

    virtual img::EasyImage calculateFrame(){
        return img::EasyImage();
    }
};


#endif //ENGINE_ABSTRACTMODULE_H
