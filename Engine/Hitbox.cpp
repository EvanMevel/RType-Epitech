//
// Created by evans on 02/02/2023.
//

#include "Hitbox.h"


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

bool Hitbox::contains(int x, int y) {
    return (x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height);
}
