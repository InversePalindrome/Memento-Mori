/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"


AnimationComponent::AnimationComponent() :
	Component(Component::ID::Animation),
	animationDirection(AnimationDirection::FaceUp)
{
}

AnimationDirection AnimationComponent::getAnimationDirection() const
{
	return this->animationDirection;
}

void AnimationComponent::setAnimationDirection(AnimationDirection animationDiretion)
{
	this->animationDirection = animationDiretion;
}

void AnimationComponent::update(sf::Time deltaTime)
{
	this->animations.update(deltaTime);
}

void AnimationComponent::animate(sf::Sprite& sprite) const
{
	this->animations.animate(sprite);
}

void AnimationComponent::playAnimation(AnimationID animationID, bool loop)
{
	this->animations.playAnimation(std::make_pair(animationID, this->getAnimationDirection()), loop);
}

void AnimationComponent::stopAnimation()
{
	this->animations.stopAnimation();
}

void AnimationComponent::addAnimation(AnimationID animationID, AnimationDirection direction, const thor::Animator<sf::Sprite, std::pair<AnimationID, AnimationDirection>>::AnimationFunction& animation, sf::Time duration)
{
	this->animations.addAnimation(std::make_pair(animationID, direction), animation, duration);
}

bool AnimationComponent::isPlayingAnimation() const
{
	return this->animations.isPlayingAnimation();
}