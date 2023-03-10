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

#ifndef R_TYPE_SERVER_IPSCENE_H
#define R_TYPE_SERVER_IPSCENE_H

#include "Engine/Scene.h"
#include "Engine/Entity.h"
#include "Engine/Engine.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "Client/Textures/Textures.h"
#include "Client/Textures/CreateScrollingTexture.h"
#include "Engine/VelocitySystem.h"
#include "CreateTextBox.h"
#include "Engine/SceneHolder.h"
#include "ClientNetServer.h"
#include "Engine/Network/Packets/HandshakePacket.h"
#include "Scenes.h"

/**
 * @brief function that create and return ipScene
 * @param engine
 * @return ipScene
 */
std::shared_ptr<Scene> ipScene(EnginePtr engine);

#endif //R_TYPE_SERVER_IPSCENE_H
