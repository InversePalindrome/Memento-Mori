/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AttackComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"
#include "VelocityComponent.hpp"

#include <SFML/Graphics/Rect.hpp>


class AttackComponent : public Component
{
public:
	AttackComponent();

	virtual std::istringstream& readStream(std::istringstream& iStream) override;
	
	sf::Vector2f getPosition() const;
	Direction getAttackDirection() const;

	float getKnockback() const;
	bool hasAttacked() const;
	
	void setPosition(sf::Vector2f position);
	void setAttackDirection(Direction direction);

	void setKnockback(float knockback);

	void setAttackStatus(bool attackStatus);
	void setProjectileStatus(bool projectileStatus);

	bool isProjectile() const;

private:
	sf::Vector2f position;
	Direction attackDirection;
	float knockback;

	bool attackStatus;
	bool projectileStatus;
};