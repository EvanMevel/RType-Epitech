//
// Created by evans on 18/01/2023.
//

#ifndef R_TYPE_SERVER_IGRAPHICLIB_H
#define R_TYPE_SERVER_IGRAPHICLIB_H

#include <unordered_map>
#include <typeindex>
#include <any>
#include <vector>
#include <cstddef>
#include <string>
#include "../IConsumer.h"
#include "IWindow.h"
#include "../ISystem.h"

class Engine;

class IGraphicLib {
private:
    std::unordered_map<std::type_index, std::any> eventConsumers;
    std::vector<ISystem*> systems;

public:
    virtual ~IGraphicLib();

    template<class Event>
    void registerEventConsumer(IConsumer<Event> consumer);
    void processEvents(Engine);
    void addSystem(ISystem*);
    void update(Engine&);
    virtual std::vector<std::any> retrieveEvents() = 0;
    virtual IWindow& createWindow(int width, int height, std::string title) = 0;
    virtual IWindow& getWindow() = 0;
    virtual void closeWindow() = 0;
    virtual ITexture createTexture(const std::string &texturePath) = 0;
    virtual void drawTexture(ITexture, int x, int y, ColorCodes) = 0;
    virtual void drawText(std::string, int x, int y, int size, ColorCodes) = 0;
};

#endif //R_TYPE_SERVER_IGRAPHICLIB_H
