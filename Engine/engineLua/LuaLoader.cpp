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

#include <memory>
#include "LuaLoader.h"
#include <iostream>
#include <filesystem>
#include "Engine/Graphic/IGraphicLib.h"
#include "Engine/Component/TeamComponent.h"
#include "Engine/Component/HealthComponent.h"
#include "Engine/Component/CooldownComponent.h"
#include "PhysicComponent.h"
#include "IAComponent.h"
#include "LuaClass.h"
#include "LuaType.h"

LuaLoader::LuaLoader() {
    _lua.defineGlobal("ENGINE_TPS", ENGINE_TPS);
}

static void luaLoadFolder(LuaWrapper &lua, const std::filesystem::directory_entry &folder) {
    for (const auto & entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_directory()) {
            luaLoadFolder(lua, entry);
        } else if (entry.path().extension() == ".lua") {
            std::cout << "[LuaLoader] Loading " << entry.path().string() << std::endl;
            lua.doFile(entry.path().string());
        }
    }
}

void LuaLoader::loadFolder(const std::string &folderPath) {
    char *rtypeLuaPath = std::getenv("RTYPE_LUA_PATH");
    std::string luaPath = rtypeLuaPath ? rtypeLuaPath : "";
    std::string path = luaPath + folderPath;
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Folder " + path + " does not exist");
    }
    std::filesystem::directory_entry folderEntry(path);

    luaLoadFolder(_lua, folderEntry);
}

void addComponentConstructors(std::shared_ptr<LuaEntityTypeFactory> luaEntityTypeFactory) {
    luaEntityTypeFactory->getComponentFactory().addComponent("TeamComponent", [](std::shared_ptr<Entity> entity, std::vector<int> args) {
        entity->addComponent<TeamComponent>((std::size_t) args[0]);
    });

    luaEntityTypeFactory->getComponentFactory().addComponent("HealthComponent", [](std::shared_ptr<Entity> entity, std::vector<int> args) {
        entity->addComponent<HealthComponent>((std::size_t) args[0], (std::size_t) args[1]);
    });

    luaEntityTypeFactory->getComponentFactory().addComponent("CooldownComponent", [](std::shared_ptr<Entity> entity, std::vector<int> args) {
        entity->addComponent<CooldownComponent>((std::size_t) args[0]);
    });

    luaEntityTypeFactory->getComponentFactory().addComponent("PhysicComponent", [](std::shared_ptr<Entity> entity, std::vector<int> args) {
        auto physicComponent = entity->addComponent<PhysicComponent>();
        if (args.empty()) {
            return;
        }

        physicComponent->maxVelocity = (std::size_t) args[0];
        if (args.size() > 1) {
            physicComponent->accelerationSlow = (std::size_t) args[1];
        }
        if (args.size() > 2) {
            physicComponent->velocitySlow = (std::size_t) args[2];
        }
    });

    luaEntityTypeFactory->getComponentFactory().addComponent("IAComponent", [](std::shared_ptr<Entity> entity, std::vector<int> args) {
        entity->addComponent<IAComponent>();
    });
}

static int luaPreloadEntityTypeFactory(lua_State *L) {
    LuaEntityTypeFactory *factory = (LuaEntityTypeFactory*) lua_touserdata(L, 1);

    lua_pushlightuserdata(L, factory);
    luaL_setmetatable(L, "LuaEntityTypeFactory");

    std::cout << "ezaeza" << std::endl;

    return 1;
}

static int tst(lua_State *L) {
    std::cout << "tst" << std::endl;
    return 0;
}

void LuaLoader::loadEntityTypes(std::shared_ptr<LuaEntityTypeFactory> luaEntityTypeFactory) {
    void *luaEntityTypeFactoryPtr = luaEntityTypeFactory.get();

    _lua.registerFunction("registerEntityType", luaRegisterEntityType);

    auto entityType = LuaClass(_lua, "LuaEntityType", -1);
    entityType.registerFunction("addComponent", luaAddComponentToType);
    entityType.done();

    auto func = _lua.getFunction<VoidType, void*>("loadEntityTypes");
    //func.call(LuaType("LuaEntityTypeFactory", luaEntityTypeFactoryPtr));
    func.call(luaEntityTypeFactoryPtr);

    addComponentConstructors(luaEntityTypeFactory);
}

int luaRegisterSprite(lua_State *L) {
    IGraphicLib *lib = (IGraphicLib*) lua_touserdata(L, 1);
    const std::unique_ptr<StringRegistry<SpriteProperty>> &spriteRegistry = lib->getSpriteProperties();

    SpriteSheet *spriteSheet = (SpriteSheet*) lua_touserdata(L, 2);

    std::string name = lua_tostring(L, 3);

    int startX = lua_tointeger(L, 4);
    int startY = lua_tointeger(L, 5);

    int lengthX = lua_tointeger(L, 6);
    int lengthY = lua_tointeger(L, 7);

    int repeatX = lua_tointeger(L, 8);
    int repeatY = lua_tointeger(L, 9);

    int frameSpeed = lua_tointeger(L, 10);

    float scale = lua_tonumber(L, 11);

    auto sprite = spriteSheet->createSprite(startX, startY, lengthX, lengthY, repeatX, repeatY, frameSpeed, scale);

    spriteRegistry->registerValue(name, sprite);
    return 0;
}

int luaCreateSpriteSheet(lua_State *L) {
    IGraphicLib *lib = (IGraphicLib*) lua_touserdata(L, 1);

    std::string path = lua_tostring(L, 2);

    auto spriteSheet = lib->createSpriteSheet(path);

    lib->getSpriteSheets().push_back(spriteSheet);

    lua_pushlightuserdata(L, spriteSheet.get());

    return 1;
}

void LuaLoader::loadEntitySprites(std::shared_ptr<IGraphicLib> graphicLib) {
    void *graphicLibPtr = graphicLib.get();

    _lua.registerFunction("registerSprite", luaRegisterSprite);

    _lua.registerFunction("createSpriteSheet", luaCreateSpriteSheet);

    auto func = _lua.getFunction<VoidType, void*>("loadEntitySprites");

    func.call(graphicLibPtr);

    graphicLib->getSpriteSheets().clear();
}
