//
// Created by gugue on 03/03/2023.
//

#ifndef PONG_LOBBYSCENE_H
#define PONG_LOBBYSCENE_H


#include "Engine/Scene.h"
#include "Engine/EntityType.h"
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

std::shared_ptr<Scene> lobbyScene(EnginePtr engine);

#endif //PONG_LOBBYSCENE_H
