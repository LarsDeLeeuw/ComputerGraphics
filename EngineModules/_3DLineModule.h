#ifndef ENGINE__3DLINEMODULE_H
#define ENGINE__3DLINEMODULE_H

#include "../vector3d.h"
#include "../easy_image.h"
#include "../ini_configuration.h"
#include "AbstractModule.h"
#include "Figures3D.h"

class _3DLineModule : public AbstractModule{
public:
    _3DLineModule(const ini::Configuration &configuration, bool zbuf = false, bool triangulate = false);
    ~_3DLineModule() = default;
    img::EasyImage* calculateFrame() override;

private:
    Figures3D figures;
    Vector3D eye_point;
    img::EasyImage* draw_zbuf_triangles(const int size, const img::Color backgroundcolor);
    int size;
    img::Color backgroundcolor;
    Lines2D* lines;
    bool fZbuf = false;
    bool fTriangulate = false;
};



#endif //ENGINE__3DLINEMODULE_H
