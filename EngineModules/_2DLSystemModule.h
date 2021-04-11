#ifndef ENGINE__2DLSYSTEMMODULE_H
#define ENGINE__2DLSYSTEMMODULE_H


#include "AbstractModule.h"

class _2DLSystemModule : public AbstractModule{

    _2DLSystemModule();
    ~_2DLSystemModule();

    img::EasyImage calculateFrame() override;
};


#endif //ENGINE__2DLSYSTEMMODULE_H
