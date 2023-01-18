//
// Created by evans on 18/01/2023.
//

#include <string>
#include "RaylibTexture.h"

RaylibTexture::RaylibTexture(std::string path) {
    this->handle = LoadTexture(path.c_str());
}
