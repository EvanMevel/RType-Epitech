//
// Created by aaama on 24/01/2023.
//

#include "MainMenu.h"

std::shared_ptr<Scene> mainMenu(Engine &e)
{
    auto sc = e.createScene<Scene>();
    auto background = sc->createEntity();
    std::cout << "EntityId: " << background->getId() << std::endl;

    auto graph = e.getGraphicLib();
    auto height = graph->getWindow().getHeight();
    auto width = graph->getWindow().getWidth();
    auto texture = graph->createTexture("../Client/assets/img_1.png");
    background->addComponent<FixTextureComponent>()->setTexture(texture);
    auto pos = background->addComponent<PositionComponent>();
    pos->setX(0);
    pos->setY(0);

    auto title = createButton(e,sc,"../Client/assets/rtype.png",width/2-(800/2),height/3-(400/2));
    auto playButton = createButton(e,sc,"../Client/assets/img_3.png",width/2-(400/2),height*0.45-(100/2));
    auto optionButton = createButton(e,sc,"../Client/assets/img_3.png",width/2-(400/2),height*0.65-(100/2));
    auto quitButton = createButton(e,sc,"../Client/assets/img_3.png",width/2-(400/2),height*0.85-(100/2));

    return sc;
}