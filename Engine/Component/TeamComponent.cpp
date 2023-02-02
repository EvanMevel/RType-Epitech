//
// Created by aaama on 17/01/2023.
//

#include "TeamComponent.h"

size_t TeamComponent::getTeam() const {
    return team;
}

void TeamComponent::setTeam(size_t team) {
    TeamComponent::team = team;
}
