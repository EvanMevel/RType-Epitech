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

#ifndef R_TYPE_SERVER_CREATESCROLLINGTEXTURE_H
#define R_TYPE_SERVER_CREATESCROLLINGTEXTURE_H

#include "Engine/Entity.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "Engine/Scene.h"
#include "Engine/Graphic/Textures/ScrollingTextureComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Textures.h"

/**
 * @brief Create a scrolling texture component
 * @param lib Graphic library
 * @param sc Scene
 * @param texturePath Path to the texture
 * @param speed Speed of the scrolling
 * @return The entity with the scrolling texture component
 */
std::shared_ptr<Entity> createScrollingTextureComponent(const std::shared_ptr<IGraphicLib> &lib, const std::shared_ptr<Scene> &sc,
                                                        Textures texture, int speed);


#endif //R_TYPE_SERVER_CREATESCROLLINGTEXTURE_H
