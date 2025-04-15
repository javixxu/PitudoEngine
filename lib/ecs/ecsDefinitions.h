#pragma once
#include <stdint.h>
#include <bitset>
#include <unordered_map>
#include <string>

// A simple type alias
using Entity = uint32_t;
// A simple type alias
using ComponentType = uint8_t;

// Used to define the size of arrays later on
const Entity MAX_ENTITIES = 2048;
// Used to define the size of arrays later on
const ComponentType MAX_COMPONENTS = 128;

// A simple type alias
using Signature = std::bitset<MAX_COMPONENTS>;

class Component {
public:
    std::string m_tag = "default";
    Component() {};
    virtual ~Component() {};
    virtual void ReadData(const std::unordered_map<std::string,std::string>& values,Entity e) {};
};
