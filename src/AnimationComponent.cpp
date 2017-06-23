/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"

#include <Thor/Animations/FrameAnimation.hpp>

#include <fstream>


AnimationComponent::AnimationComponent() :
	Component(Component::ID::Animation),
	animationID(AnimationID::Idle),
	animationDirection(Direction::Up),
	animationFramesFile()
{
}

std::istringstream& AnimationComponent::readStream(std::istringstream& iStream)
{
	iStream >> this->animationFramesFile;

	this->addAnimations();

	return iStream;
}

AnimationID AnimationComponent::getAnimationID() const
{
	return this->animationID;
}

Direction AnimationComponent::getAnimationDirection() const
{
	return this->animationDirection;
}

void AnimationComponent::setAnimation(AnimationID animationID)
{
	this->animationID = animationID;
}

void AnimationComponent::setAnimationDirection(Direction animationDiretion)
{
	this->animationDirection = animationDiretion;
}

void AnimationComponent::setAnimationsFrameFile(const std::string& fileName)
{
	this->animationFramesFile = fileName;
}

void AnimationComponent::update(sf::Time deltaTime)
{
	this->animations.update(deltaTime);
}

void AnimationComponent::animate(sf::Sprite& sprite) const
{
	this->animations.animate(sprite);
}

void AnimationComponent::playAnimation(bool loop)
{
	this->animations.playAnimation(std::make_pair(this->getAnimationID(), this->getAnimationDirection()), loop);
}

void AnimationComponent::stopAnimation()
{
	this->animations.stopAnimation();
}

void AnimationComponent::addAnimation(AnimationID animationID, Direction direction, const thor::FrameAnimation& animation, sf::Time duration)
{
	this->animations.addAnimation(std::make_pair(animationID, direction), animation, duration);
}

void AnimationComponent::addAnimations()
{
	std::ifstream inFile(this->animationFramesFile);
	std::string line;

	std::getline(inFile, line);

	std::istringstream iStream(line);

	std::size_t iNumOfAnimations = 0;

	iStream >> iNumOfAnimations;

	for (std::size_t i = 0; i < iNumOfAnimations; ++i)
	{
		thor::FrameAnimation animation;

		std::getline(inFile, line);
		iStream.str(line);
		iStream.clear();
		
		std::string iCategory;
		
		iStream >> iCategory;

        if (iCategory != "Animation")
		{
			break;
		}

		std::size_t iAnimationID, iDirection, iNumOfFrames = 0;
		float iAnimationTime = 0.f;

		iStream >> iAnimationID >> iDirection >> iNumOfFrames >> iAnimationTime;
		
		for (std::size_t j = 0; j < iNumOfFrames; ++j)
		{
			std::getline(inFile, line);
			iStream.str(line);
			iStream.clear();

			iStream >> iCategory;

			if (iCategory == "Frame")
			{
				float iDuration = 0.f;

				iStream >> iDuration;
				
				std::size_t iLeft, iTop, iWidth, iHeight = 0u;

				iStream >> iLeft >> iTop >> iWidth >> iHeight;

				animation.addFrame(iDuration, sf::IntRect(iLeft, iTop, iWidth, iHeight));
			}
		}

		this->addAnimation(static_cast<AnimationID>(iAnimationID), static_cast<Direction>(iDirection), animation, sf::seconds(iAnimationTime));
	}
}

bool AnimationComponent::isPlayingAnimation() const
{
	return this->animations.isPlayingAnimation();
}