//
// Created by evans on 18/01/2023.
//

#ifndef R_TYPE_SERVER_RAYLIBWINDOW_H
#define R_TYPE_SERVER_RAYLIBWINDOW_H

#include <unordered_map>
#include "Engine/Graphic/IWindow.h"
#include "raylib.h"

class RaylibWindow : public IWindow {
private:
    std::unordered_map<ColorCodes, Color> colors;
public:
    bool shouldClose() override;

    void beginDrawing() override;

    void endDrawing() override;

    void setTargetFPS(int i) override;

    void setBackground(ColorCodes code) override;

    void setColors(const std::unordered_map<ColorCodes, Color> &colors);
};


#endif //R_TYPE_SERVER_RAYLIBWINDOW_H
