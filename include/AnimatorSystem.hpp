/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AnimatorSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "System.hpp"
#include "AnimationComponent.hpp"


class AnimatorSystem : public System
{
public:
	AnimatorSystem(SystemManager& systemManager);

	virtual void handleEvent(EntityID entityID, EntityEvent event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void notify(const Message& message) override;

private:
	void changeAnimation(EntityID entityID, AnimationID animationID, bool loop);
	void changeAnimationDirection(EntityID entityID, AnimationDirection animationDirection);
};
