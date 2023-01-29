//
// Created by audre on 29/01/2023.
//

#include "RaylibAnimation.h"
/**
 * @brief Set every parameter which is needed for the draw function
 */
RaylibAnimation::RaylibAnimation(const std::string &texturePath) {
    const char *c = texturePath.c_str();
    image = ray::LoadImageAnim(c,&frame);
    texture = ray::LoadTextureFromImage(std::any_cast<ray::Image>(image));
    width = std::any_cast<ray::Image>(image).width;
    height = std::any_cast<ray::Image>(image).height;
}
/**
 * @brief change the animation frame
 */
void RaylibAnimation::setAnimationFrame(int frame) {
    int nextFrameAnim = width * height * 4 * frame;
    ray::UpdateTexture(std::any_cast<ray::Texture2D>(texture), ((unsigned char *)std::any_cast<ray::Image>(image).data) + nextFrameAnim);
}
