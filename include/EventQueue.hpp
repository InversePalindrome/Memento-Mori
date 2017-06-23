/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EventQueue.hpp
InversePalindrome.com
*/


#pragma once

#include <queue>


enum class EntityEvent 
{
	Spawned, Died, MoveUp, MoveDown, MoveRight, MoveLeft, Moved, BecameIdle, Collided
};

class EventQueue
{
public:
	void addEvent(EntityEvent event);

	bool processEvent(EntityEvent& event);

	void clearEvents();

private:
	std::queue<EntityEvent> events;
};
