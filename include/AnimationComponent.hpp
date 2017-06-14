/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AnimationComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <Thor/Animations/Animator.hpp>


enum class AnimationID { Idle, Walking, Attacking };
enum class AnimationDirection { FaceUp, FaceDown, FaceRight, FaceLeft, None };

class AnimationComponent : public Component
{
public:
	AnimationComponent();

	AnimationDirection getAnimationDirection() const;

	void setAnimationDirection(AnimationDirection animationDirection);

	void update(sf::Time deltaTime);
	void animate(sf::Sprite& sprite) const;

	void playAnimation(AnimationID animationID, bool loop);
	void stopAnimation();

	void addAnimation(AnimationID animationID, AnimationDirection direction, const thor::Animator<sf::Sprite, std::pair<AnimationID, AnimationDirection>>::AnimationFunction& animation, sf::Time duration);

	bool isPlayingAnimation() const;

private:
	thor::Animator <sf::Sprite, std::pair<AnimationID, AnimationDirection>> animations;
	AnimationDirection animationDirection;
};