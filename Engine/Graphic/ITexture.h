//
// Created by evans on 18/01/2023.
//

#ifndef R_TYPE_SERVER_ITEXTURE_H
#define R_TYPE_SERVER_ITEXTURE_H

#include <any>

/**
 * @brief Interface representing a texture
 */
class ITexture {
public:
    std::any handle;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
};

#endif //R_TYPE_SERVER_ITEXTURE_H
