#include <stdint.h>
#include <bitset>

// A simple type alias
using Entity = uint32_t;
// A simple type alias
using ComponentType = uint8_t;

// Used to define the size of arrays later on
const Entity MAX_ENTITIES = 5000;
// Used to define the size of arrays later on
const ComponentType MAX_COMPONENTS = 128;

// A simple type alias
using Signature = std::bitset<MAX_COMPONENTS>;