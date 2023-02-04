//
// Created by evans on 18/01/2023.
//

#ifndef R_TYPE_SERVER_RAYLIBWINDOW_H
#define R_TYPE_SERVER_RAYLIBWINDOW_H

#include <unordered_map>
#include "Engine/Graphic/IWindow.h"
namespace ray {
#include "raylib.h"
}

class RaylibWindow : public IWindow {
private:
    std::unordered_map<ColorCodes, ray::Color> colors;
public:
    bool shouldClose() override;

    void beginDrawing() override;

    void endDrawing() override;

    void setTargetFPS(int i) override;

    void setBackground(ColorCodes code) override;

    void setColors(const std::unordered_map<ColorCodes, ray::Color> &colors);

    int getWidth() override;

    int getHeight() override;

    void setFullScreen() override;
};


#endif //R_TYPE_SERVER_RAYLIBWINDOW_H
