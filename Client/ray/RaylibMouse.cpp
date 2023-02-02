//
// Created by aaama on 02/02/2023.
//

#include "RaylibMouse.h"

RaylibMouse::RaylibMouse() {
    button[MouseCode::MOUSE_BUTTON_LEFT] = ray::MOUSE_BUTTON_LEFT;
    button[MouseCode::MOUSE_BUTTON_MIDDLE] = ray::MOUSE_BUTTON_MIDDLE;
    button[MouseCode::MOUSE_BUTTON_RIGHT] = ray::MOUSE_BUTTON_RIGHT;
}

Vector2i RaylibMouse::getPos() {

    auto rayPos = ray::GetMousePosition();
    Vector2i pos{};
    pos.x = static_cast<int>(rayPos.x);
    pos.y = static_cast<int>(rayPos.y);
    return pos;
}

bool RaylibMouse::isClicked(MouseCode code){
    ray::MouseButton rayButton = button[code];
    return ray::IsMouseButtonPressed(rayButton);
}