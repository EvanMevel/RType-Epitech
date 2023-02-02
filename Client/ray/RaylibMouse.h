//
// Created by aaama on 02/02/2023.
//

#ifndef R_TYPE_SERVER_RAYLIBMOUSE_H
#define R_TYPE_SERVER_RAYLIBMOUSE_H

#include <unordered_map>
#include "Engine/Graphic/IMouse.h"

namespace ray {
#include "raylib.h"
}

class RaylibMouse : public IMouse{
private:
    std::unordered_map<MouseCode, ray::MouseButton> button;
public:
    RaylibMouse();
    Vector2i getPos() override;
    bool isClicked(MouseCode) override;
};


#endif //R_TYPE_SERVER_RAYLIBMOUSE_H
