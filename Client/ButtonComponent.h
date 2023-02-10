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

#ifndef R_TYPE_SERVER_BUTTONCOMPONENT_H
#define R_TYPE_SERVER_BUTTONCOMPONENT_H


#include <functional>
#include "Engine/Component/IComponent.h"
#include "Engine/Hitbox.h"

/**
 * @brief Component that contains a FIX hitbox, it does not move, and can be clicked
 * @details This component is used to create buttons
 */
class ButtonComponent : public IComponent {
private:
    Hitbox hitbox;
    std::function<void(EnginePtr)> _onClick;
public:
    ButtonComponent();

    const Hitbox &getHitbox() const;

    void setHitbox(const Hitbox &hitbox);

    void setOnClick(const std::function<void(EnginePtr)> &onClick);

    void clicked(EnginePtr engine);
};


#endif //R_TYPE_SERVER_BUTTONCOMPONENT_H