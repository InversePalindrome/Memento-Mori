/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Map.hpp
InversePalindrome.com
*/


#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Transformable.hpp>


class Map : public sf::Drawable, sf::Transformable
{
public:
	Map(const sf::Texture& tileset, std::size_t rows, std::size_t columns, std::size_t tileSize, std::size_t numOfTiles, sf::Vector2f tileScale);

	sf::Vector2u getSize() const;

private:
	sf::VertexArray vertices;
	const sf::Texture tileset;
	const sf::Vector2f tileScale;
	const sf::Vector2u mapSize;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
