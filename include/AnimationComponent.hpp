/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AnimationComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"
#include "Direction.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <Thor/Animations/Animator.hpp>
#include <Thor/Animations/FrameAnimation.hpp>


enum class AnimationID { Idle, Walking, Attacking };

class AnimationComponent : public Component
{
public:
	AnimationComponent();

	virtual std::istringstream& readStream(std::istringstream& iStream) override;

	AnimationID getAnimationID() const;
	Direction getAnimationDirection() const;

	void setAnimation(AnimationID animationID);
	void setAnimationDirection(Direction animationDirection);

	void setAnimationsFrameFile(const std::string& fileName);

	void update(sf::Time deltaTime);
	void animate(sf::Sprite& sprite) const;

	void playAnimation(bool loop);
	void stopAnimation();

	void addAnimation(AnimationID animationID, Direction direction, const thor::FrameAnimation& animation, sf::Time duration);
	void addAnimations();

	bool isPlayingAnimation() const;

private:
	thor::Animator <sf::Sprite, std::pair<AnimationID, Direction>> animations;
	AnimationID animationID;
	Direction animationDirection;
	std::string animationFramesFile;
};