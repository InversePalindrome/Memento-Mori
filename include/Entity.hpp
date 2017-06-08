/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Entity.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <memory>
#include <bitset>
#include <vector>
#include <cstddef>


class EntityManager;

class Entity
{
public:
	using BitMask = std::bitset<32u>;
	using ComponentPtr = std::unique_ptr<Component>;

	Entity(std::size_t id, const BitMask& entityComposition, EntityManager& entityManager);

	std::size_t getID() const;
	BitMask getEntityComposition() const;

	template<typename T>
	T* getComponent(Component::ID componentID);

	void addComponent(ComponentPtr& component);
	void removeComponent(Component::ID componentID);

private:
	std::size_t id;
	BitMask entityComposition;
	std::vector<ComponentPtr> components;
};


template<typename T>
T* Entity::getComponent(Component::ID componentID)
{
	auto componentItr = std::find_if(std::begin(this->components), std::end(this->components),
		[componentID](const auto& component) { return component->getID() == componentID; });

	return (componentItr != std::end(this->components) ? dynamic_cast<T*>(componentItr->get()) : nullptr);
}