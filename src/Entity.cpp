/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Entity.cpp
InversePalindrome.com
*/


#include "Entity.hpp"
#include "EntityManager.hpp"

#include <algorithm>


Entity::Entity(std::size_t id, const BitMask& entityComposition, EntityManager& entityManager) :
	id(id),
	entityComposition(entityComposition),
	components()
{
	for (std::size_t i = 0; i < entityComposition.size(); ++i)
	{
		if (entityComposition[i])
		{
			entityManager.addComponent(id, static_cast<Component::ID>(i));
		}
	}
}

std::size_t Entity::getID() const
{
	return this->id;
}

Entity::BitMask Entity::getEntityComposition() const
{
	return this->entityComposition;
}

void Entity::addComponent(ComponentPtr& component)
{
	if (!this->entityComposition[static_cast<std::size_t>(component->getID())])
	{
		this->components.push_back(std::move(component));
		this->entityComposition[static_cast<std::size_t>(component->getID())] = 1u;
	}
}

void Entity::removeComponent(Component::ID componentID)
{
	this->components.erase(std::remove_if(std::begin(this->components), std::end(this->components),
		[&](const auto& component) { return component->getID() == componentID; }), std::end(this->components));

	this->entityComposition[static_cast<std::size_t>(componentID)] = 0u;
}