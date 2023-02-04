//
// Created by audre on 02/02/2023.
//

#ifndef R_TYPE_SERVER_SCENEHOLDER_H
#define R_TYPE_SERVER_SCENEHOLDER_H


#include "Scene.h"

class SceneHolder {
private:
    std::unordered_map<int,std::shared_ptr<Scene>> scenes;

public:
    void addScene(int index, std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getScene(int index);

};


#endif //R_TYPE_SERVER_SCENEHOLDER_H
