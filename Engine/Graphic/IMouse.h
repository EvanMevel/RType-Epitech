//
// Created by aaama on 02/02/2023.
//

#ifndef R_TYPE_SERVER_IMOUSE_H
#define R_TYPE_SERVER_IMOUSE_H


#include "Engine/Vector2i.h"

enum class MouseCode {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE
};

class IMouse {
public:
    virtual Vector2i getPos() = 0;
    virtual bool isClicked(MouseCode) = 0;
};

#endif //R_TYPE_SERVER_IMOUSE_H
