//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H

#include <string>
#include <memory>

class Engine;

using EnginePtr = std::unique_ptr<Engine>&;

/**
 * @brief ISystem is the base class for all systems of the ECS
 * @details override the update method to define the behavior of the system
 */
class ISystem {
public:
    ISystem();
    ~ISystem();

    /**
     * @brief update is what will be called by the engine to use the system
     * @details override this method to define the behavior of the system
     * @param engine the engine that is calling the system
     */
    virtual void update(EnginePtr engine) = 0;

    virtual std::string getName();
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ISYSTEM_H
