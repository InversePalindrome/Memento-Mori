/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AttackComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"

#include <SFML/Graphics/Rect.hpp>


class AttackComponent : public Component
{
public:
	AttackComponent();

	virtual std::istringstream& readStream(std::istringstream& iStream) override;

	sf::FloatRect getAttackArea() const;
	float getKnockback() const;

	void setAttackArea(const sf::FloatRect& attackArea);
	void setAttackPosition(sf::Vector2f attackPosition);
	
	void setKnockback(float knockback);

private:
	sf::FloatRect attackArea;
	float knockback;
};