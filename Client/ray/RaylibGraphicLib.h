//
// Created by evans on 18/01/2023.
//

#ifndef R_TYPE_SERVER_RAYLIBGRAPHICLIB_H
#define R_TYPE_SERVER_RAYLIBGRAPHICLIB_H

#include "Engine/Graphic/IGraphicLib.h"
#include "RaylibWindow.h"
#include "Engine/Graphic/ColorCodes.h"
#include "RaylibMouse.h"

class RaylibGraphicLib : public IGraphicLib {
private:
    std::unordered_map<ColorCodes, ray::Color> colors;
    std::unordered_map<KeyCodes, ray::KeyboardKey> keys;
    RaylibWindow window;
    RaylibMouse mouse;

public:
    RaylibGraphicLib();

    IWindow &createWindow(int width, int height, std::string title) override;

    void drawText(std::string string, int x, int y, int size, ColorCodes color) override;

    IWindow &getWindow() override;

    void closeWindow() override;

    std::shared_ptr<ITexture> createTexture(const std::string &texturePath) override;

    void drawTexture(std::shared_ptr<ITexture> texture, int x, int y, ColorCodes codes) override;

    bool isKeyDown(KeyCodes codes) override;

    std::vector<std::any> retrieveEvents() override;

    std::shared_ptr<IAnimation> createAnimation(const std::string &texturePath) override;

    void drawAnimation(std::shared_ptr<IAnimation> animation, int x, int y, ColorCodes codes) override;

    IMouse &getMouse() override;
};


#endif //R_TYPE_SERVER_RAYLIBGRAPHICLIB_H
