//
// Created by evans on 18/01/2023.
//

#include <string>
#include "RaylibTexture.h"

RaylibTexture::RaylibTexture(const std::string &path) {
    const char *c = path.c_str();
    this->handle = ray::LoadTexture(c);
}

int RaylibTexture::getWidth() {
    auto texture2D = any_cast<ray::Texture2D>(handle);
    return texture2D.width;
}

int RaylibTexture::getHeight() {
    auto texture2D = any_cast<ray::Texture2D>(handle);
    return texture2D.height;
}
