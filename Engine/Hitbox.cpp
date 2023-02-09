// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Hitbox.h"

Hitbox::Hitbox() : x(0), y(0), width(0), height(0){

}

Hitbox::Hitbox(int x, int y, size_t width, size_t height) : x(x), y(y), width(width), height(height) {}

Hitbox::Hitbox(std::shared_ptr<PositionComponent> pos, std::shared_ptr<HitboxComponent> hitbox) {
    this->x = pos->getX();
    this->y = pos->getY();
    this->width = hitbox->getLengthX();
    this->height = hitbox->getLengthY();
}

Hitbox::Hitbox(std::shared_ptr<Entity> entity) {
    auto pos = entity->getComponent<PositionComponent>();
    auto hitbox = entity->getComponent<HitboxComponent>();
    if (pos == nullptr || hitbox == nullptr)
        throw std::runtime_error("Entity does not have a position or hitbox component");
    this->x = pos->getX();
    this->y = pos->getY();
    this->width = hitbox->getLengthX();
    this->height = hitbox->getLengthY();
}

bool Hitbox::isColliding(Hitbox &other) {
    return (x < other.x + other.width &&
            x + width > other.x &&
            y < other.y + other.height &&
            y + height > other.y);
}

bool Hitbox::contains(int x, int y) const{
    return (x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height);
}

bool Hitbox::contains(Vector2i pos) const {
    return contains(pos.x, pos.y);
}
