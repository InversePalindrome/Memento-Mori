/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SpriteComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class SpriteComponent : public Component
{
public:
	SpriteComponent();

	virtual std::istringstream& readStream(std::istringstream& iStream) override;

	sf::Sprite& getSprite();

	sf::Vector2f getPosition() const;
	sf::Vector2f getOrigin() const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void setPosition(sf::Vector2f position);
	void setOrigin(sf::Vector2f origin);

	void draw(sf::RenderWindow& window);

	void setTexture(const TextureHolder& textures);
	void setTextureRect(const sf::IntRect& rect);

	void setScale(sf::Vector2f scale);

private:
	sf::Sprite sprite;
	Textures::ID textureID;
};
