//
// Created by aaama on 17/01/2023.
//

#ifndef B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H
#define B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H


#include <unordered_map>
#include <typeindex>
#include <any>
#include <cstddef>

class Entity {
     std::unordered_map<std::type_index, std::any> components;
     size_t id;
};


#endif //B_CPP_500_REN_5_2_RTYPE_AUDREY_AMAR_ENTITY_H
