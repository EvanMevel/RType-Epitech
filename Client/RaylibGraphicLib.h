//
// Created by evans on 18/01/2023.
//

#ifndef R_TYPE_SERVER_RAYLIBGRAPHICLIB_H
#define R_TYPE_SERVER_RAYLIBGRAPHICLIB_H

#include "Engine/Graphic/IGraphicLib.h"
#include "RaylibWindow.h"
#include "Engine/Graphic/ColorCodes.h"

class RaylibGraphicLib : public IGraphicLib {
private:
    std::unordered_map<ColorCodes, ray::Color> colors;
    RaylibWindow window;

public:
    RaylibGraphicLib();

    IWindow &createWindow(int width, int height, std::string title) override;

    void drawText(std::string string, int x, int y, int size, ColorCodes color) override;

    IWindow &getWindow() override;

    void closeWindow() override;

    ITexture createTexture(const std::string &texturePath) override;

    void drawTexture(ITexture texture, int x, int y, ColorCodes codes) override;

    std::vector<std::any> retrieveEvents() override;
};


#endif //R_TYPE_SERVER_RAYLIBGRAPHICLIB_H
