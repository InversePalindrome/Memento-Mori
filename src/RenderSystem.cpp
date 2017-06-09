/*
Copyright (c) 2017 InversePalindrome
Memento Mori - RenderSystem.cpp
InversePalindrome.com
*/


#include "RenderSystem.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "SpriteComponent.hpp"
#include "PositionComponent.hpp"


RenderSystem::RenderSystem(SystemManager& systemManager) :
	System(System::ID::Render, systemManager)
{
	EntityManager::EntityComposition entityComposition;

	entityComposition[static_cast<std::size_t>(Component::ID::Sprite)] = true;
	entityComposition[static_cast<std::size_t>(Component::ID::Position)] = true;

	componentRequirements.push_back(entityComposition);
}

void RenderSystem::handleEvent(std::size_t eventID, EntityEvents event)
{

}

void RenderSystem::update(sf::Time deltaTime)
{
	auto* entityManager = this->systemManager->getEntityManager();
	
	for (auto& entity : this->entitiesIDs)
	{
		auto* position = entityManager->getComponent<PositionComponent>(entity, Component::ID::Position);
		auto* sprite = entityManager->getComponent<SpriteComponent>(entity, Component::ID::Sprite);

		sprite->updatePosition(position->getPosition());
	}
}

void RenderSystem::notify(const Message& message)
{

}

void RenderSystem::render(sf::RenderWindow& window)
{
	auto* entityManager = this->systemManager->getEntityManager();
	
	for (auto& entity : this->entitiesIDs)
	{
		auto* sprite = entityManager->getComponent<SpriteComponent>(entity, Component::ID::Sprite);
		sprite->draw(window);
	}
}