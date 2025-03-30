#pragma once
#include <unordered_map>
#include <cassert>
#include "ecsDefinitions.h"

// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.
class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    void InsertData(Entity entity, T&& component) {
        assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

        // Insert data at the new index, and update the maps.
        size_t newIndex = mSize;
        mEntityToIndexMap[entity] = newIndex;
        mIndexToEntityMap[newIndex] = entity;
        mComponentArray[newIndex] = std::move(component);
        ++mSize;
    }

    void InsertData(Entity entity, T& component) {
        assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

        // Insert data at the new index, and update the maps.
        size_t newIndex = mSize;
        mEntityToIndexMap[entity] = newIndex;
        mIndexToEntityMap[newIndex] = entity;
        mComponentArray[newIndex] = component;
        ++mSize;
    }

    void RemoveData(Entity entity) {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

        // Copy element at end into the removed element's place to maintain density
        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastElement = mSize - 1;

        if (indexOfRemovedEntity != indexOfLastElement) {
            mComponentArray[indexOfRemovedEntity] = std::move(mComponentArray[indexOfLastElement]);

            // Update maps to point to the moved spot
            Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
            mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
        }

        // Erase the removed entity from the map
        mEntityToIndexMap.erase(entity);
        mIndexToEntityMap.erase(indexOfLastElement);

        --mSize;
    }

    T& GetData(Entity entity) {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return mComponentArray[mEntityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override {
        if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
            // Remove the entity's component if it exists
            RemoveData(entity);
        }
    }

private:
    // Use an unordered_map to store components by their dynamic index
    std::unordered_map<size_t, T> mComponentArray;

    // Map from an entity ID to an array index
    std::unordered_map<Entity, size_t> mEntityToIndexMap;

    // Map from an array index to an entity ID
    std::unordered_map<size_t, Entity> mIndexToEntityMap;

    // Total size of valid entries in the array
    size_t mSize = 0;
};
