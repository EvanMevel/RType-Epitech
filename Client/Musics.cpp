//
// Created by aaama on 28/02/2023.
//

#include "Musics.h"


void loadMusics(const std::shared_ptr<IGraphicLib> &lib){
    lib->registerMusic(Musics::MAIN_MENU_MUSIC,"menu r-type.mp3");
    lib->registerMusic(Musics::GAME_MUSIC,"r-type game.mp3");
    lib->registerMusic(Musics::BOSS_MUSIC, "boss_r-type.ogg");
}