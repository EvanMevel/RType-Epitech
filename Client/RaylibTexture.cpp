//
// Created by evans on 18/01/2023.
//

#include <string>
#include "RaylibTexture.h"

RaylibTexture::RaylibTexture(const std::string &path) {
    const char *c = path.c_str();
    this->handle = LoadTexture(c);
}
