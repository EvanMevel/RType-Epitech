//
// Created by evans on 18/01/2023.
//

#ifndef R_TYPE_SERVER_RAYLIBTEXTURE_H
#define R_TYPE_SERVER_RAYLIBTEXTURE_H

#include "Engine/Graphic/ITexture.h"
namespace ray {
#include "raylib.h"
}

class RaylibTexture : public ITexture {
public:
    RaylibTexture(const std::string &path);
};


#endif //R_TYPE_SERVER_RAYLIBTEXTURE_H
