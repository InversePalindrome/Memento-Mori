/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AnimationComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <Thor/Animations/Animator.hpp>
#include <Thor/Animations/FrameAnimation.hpp>


enum class AnimationID { Idle, Walking, Attacking };
enum class AnimationDirection { FaceUp, FaceDown, FaceRight, FaceLeft, None };

class AnimationComponent : public Component
{
public:
	AnimationComponent();

	virtual std::istringstream& readStream(std::istringstream& iStream) override;

	AnimationID getAnimationID() const;
	AnimationDirection getAnimationDirection() const;

	void setAnimation(AnimationID animationID);
	void setAnimationDirection(AnimationDirection animationDirection);

	void setAnimationsFrameFile(const std::string& fileName);

	void update(sf::Time deltaTime);
	void animate(sf::Sprite& sprite) const;

	void playAnimation(bool loop);
	void stopAnimation();

	void addAnimation(AnimationID animationID, AnimationDirection direction, const thor::FrameAnimation& animation, sf::Time duration);
	void addAnimations();

	bool isPlayingAnimation() const;

private:
	thor::Animator <sf::Sprite, std::pair<AnimationID, AnimationDirection>> animations;
	AnimationID animationID;
	AnimationDirection animationDirection;
	std::string animationFramesFile;
};