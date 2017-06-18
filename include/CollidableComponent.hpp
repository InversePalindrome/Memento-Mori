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

	sf::FloatRect getBoundingBox() const;

	void setBoundingBox(const sf::FloatRect& boundingBox);

private:
	sf::FloatRect boundingBox;
};