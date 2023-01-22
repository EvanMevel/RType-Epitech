//
// Created by evans on 18/01/2023.
//

#ifndef IWINDOW_H
#define IWINDOW_H

#include <string>
#include "ITexture.h"
#include "ColorCodes.h"

/**
 * @brief Interface representing a window on the screen
 */
class IWindow {
public:
    virtual bool shouldClose() = 0;
    virtual void beginDrawing() = 0;
    virtual void endDrawing() = 0;
    virtual void setTargetFPS(int) = 0;
    virtual void setBackground(ColorCodes code) = 0;
};

#endif //IWINDOW_H
