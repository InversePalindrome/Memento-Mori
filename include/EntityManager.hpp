/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EntityManager.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"

#include <bitset>
#include <vector>
#include <functional>
#include <unordered_map>


using EntityID = std::size_t;
using EntityComposition = std::bitset<32>;

class SystemManager;

class EntityManager
{
public:
    using ComponentPtr = std::unique_ptr<Component>;
    using EntityData = std::pair<EntityComposition, std::vector<ComponentPtr>>;

    EntityManager(SystemManager& systemManager, TextureHolder& textures);

    template<typename T>
    T* getComponent(EntityID entityID, Component::ID componentID);

    std::size_t getEntityCount() const;
    std::size_t getCurrentEntityID() const;
    std::size_t getDeadEntityCount() const;

    void addEntity(const EntityComposition& entityComposition);
    void addEntity(const std::string& fileName);

    void addComponent(EntityID entityID, Component::ID componentID);

    void removeEntity(EntityID entityID);
    void removeComponent(EntityID entityID, Component::ID componentID);

    void setDeadEntityCount(std::size_t deadEntityCount);

    static EntityID getPlayerID();

private:
    std::size_t entityCount;
    std::size_t currentEntityID;
    std::size_t deadEntityCount;
    std::unordered_map<EntityID, EntityData> entities;
    std::unordered_map<Component::ID, std::function<ComponentPtr()>> componentFactory;

    SystemManager* systemManager;
    TextureHolder* textures;

    template<typename T>
    void registerComponent(Component::ID componentID);
};


template<typename T>
T* EntityManager::getComponent(EntityID entityID, Component::ID componentID)
{
    auto entityItr = this->entities.find(entityID);

    if (entityItr != std::end(this->entities) &&
        entityItr->second.first[static_cast<std::size_t>(componentID)])
    {
        auto& components = entityItr->second.second;

        auto component = std::find_if(std::begin(components), std::end(components),
            [componentID](const ComponentPtr & component) { return component->getID() == componentID; });

        return (component != std::end(components) ? dynamic_cast<T*>(component->get()) : nullptr);
    }
    else
    {
        return nullptr;
    }
}

template<typename T>
void EntityManager::registerComponent(Component::ID componentID)
{
    this->componentFactory[componentID] = []()
    {
        return std::make_unique<T>();
    };
}
