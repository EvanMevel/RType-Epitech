//
// Created by aaama on 28/02/2023.
//

#ifndef R_TYPE_CLIENT_MUSICS_H
#define R_TYPE_CLIENT_MUSICS_H

#include "Engine/Graphic/IGraphicLib.h"

enum class Musics {
    MAIN_MENU_MUSIC= 0,
    GAME_MUSIC = 1,
    BOSS_MUSIC = 2
};

void loadMusics(const std::shared_ptr<IGraphicLib> &lib);


#endif //R_TYPE_CLIENT_MUSICS_H
