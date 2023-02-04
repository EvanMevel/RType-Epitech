//
// Created by audre on 29/01/2023.
//

#ifndef R_TYPE_SERVER_IANIMATION_H
#define R_TYPE_SERVER_IANIMATION_H


#include <any>
/**
 * @brief Interface representing an animation
 */
class IAnimation {
public:
    std::any texture;
    std::any image;
    int frame;
    int width;
    int height;

    virtual void setAnimationFrame(int frame){};
};


#endif //R_TYPE_SERVER_IANIMATION_H
