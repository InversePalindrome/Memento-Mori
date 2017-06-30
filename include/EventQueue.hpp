/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EventQueue.hpp
InversePalindrome.com
*/


#pragma once

#include <queue>


enum class EntityEvent 
{
	Spawned, Died, OutOfMap, MoveUp, MoveDown, MoveRight, MoveLeft, Moved, BecameIdle, Collided, 
	ProjectileCollision, ShootProjectile, ReachedTarget, PickedUp, RoundStarted
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
