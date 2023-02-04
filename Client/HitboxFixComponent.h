//
// Created by audre on 02/02/2023.
//

#ifndef R_TYPE_SERVER_HITBOXFIXCOMPONENT_H
#define R_TYPE_SERVER_HITBOXFIXCOMPONENT_H


#include "Engine/Component/IComponent.h"
#include "Engine/Hitbox.h"

class HitboxFixComponent  : public IComponent {
private:
    Hitbox hitbox;
public:
    HitboxFixComponent();

    const Hitbox &getHitbox() const;

    void setHitbox(const Hitbox &hitbox);
};


#endif //R_TYPE_SERVER_HITBOXFIXCOMPONENT_H
