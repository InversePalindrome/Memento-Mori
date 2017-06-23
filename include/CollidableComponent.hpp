/*
Copyright (c) 2017 InversePalindrome
Memento Mori - CollidableComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>


class CollidableComponent : public Component
{
public:
	CollidableComponent();

	virtual std::istringstream& readStream(std::istringstream& iStream) override;

	sf::FloatRect getBoundingBox() const;

	void setBoundingBox(const sf::FloatRect& boundingBox);
	void setPosition(sf::Vector2f position);

private:
	sf::FloatRect boundingBox;
};