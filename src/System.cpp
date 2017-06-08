/*
Copyright (c) 2017 InversePalindrome
Memento Mori - System.cpp
InversePalindrome.com
*/


#include "System.hpp"
#include "SystemManager.hpp"

#include <algorithm>


System::System(ID systemID, SystemManager& systemManager) :
	systemID(systemID),
	entitiesIDs(),
	componentRequirements(),
	systemManager(&systemManager)
{
}

System::ID System::getID() const
{
	return this->systemID;
}

void System::addEntity(std::size_t entityID)
{
	if (std::find(std::begin(this->entitiesIDs), std::end(this->entitiesIDs), entityID) != std::end(this->entitiesIDs))
	{
		this->entitiesIDs.push_back(entityID);
	}
}

void System::removeEntity(std::size_t entityID)
{
	this->entitiesIDs.erase(std::remove(std::begin(this->entitiesIDs), std::end(this->entitiesIDs), entityID), std::end(this->entitiesIDs));
}

bool System::hasEntity(std::size_t entityID) const
{
	return std::find(std::begin(this->entitiesIDs), std::end(this->entitiesIDs), entityID) != std::end(this->entitiesIDs);
}

bool System::passesRequirements(const Entity::BitMask& entityComposition) const
{
	return std::find_if(std::begin(this->componentRequirements), std::end(this->componentRequirements), 
		[&](const auto& entityRequirements) { return entityRequirements == entityComposition; }) != std::end(this->componentRequirements);
}