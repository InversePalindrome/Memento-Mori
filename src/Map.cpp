/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Map.cpp
InversePalindrome.com
*/


#include "Map.hpp"

#include <Thor/Math/Random.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <vector>


Map::Map(const sf::Texture& tileset, std::size_t rows, std::size_t columns, std::size_t tileSize, std::size_t numOfTiles, sf::Vector2f tileScale) :
	vertices(sf::Quads, rows * columns * 4u),
	tileset(tileset),
	tileScale(tileScale),
	mapSize(columns * tileSize * tileScale.x, rows * tileSize * tileScale.y)
{
	std::vector<std::vector<std::size_t>> map(rows, std::vector<std::size_t>(columns));

	for (std::size_t i = 0u; i < rows; ++i)
	{
		for (std::size_t j = 0u; j < columns; ++j)
		{
			map[i][j] = thor::random(0u, numOfTiles - 1);
		}
	}

	for (std::size_t i = 0u; i < rows; ++i)
	{
		for (std::size_t j = 0u; j < columns; ++j)
		{
			std::size_t tileNumber = map[i][j];

			std::size_t tu = tileNumber % (tileset.getSize().x / tileSize);
			std::size_t tv = tileNumber / (tileset.getSize().x / tileSize);

			auto* quad = &vertices[(i * columns + j) * 4];
			
			quad[0].position = sf::Vector2f(j * tileSize, i * tileSize);
			quad[1].position = sf::Vector2f((j + 1) * tileSize, i * tileSize);
			quad[2].position = sf::Vector2f((j + 1) * tileSize, (i + 1) * tileSize);
			quad[3].position = sf::Vector2f(j * tileSize, (i + 1) * tileSize);

			quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
			quad[3].texCoords = sf::Vector2f(tu* tileSize, (tv + 1) * tileSize);
		}
	}
}

sf::Vector2u Map::getSize() const
{
	return this->mapSize;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.transform.scale(this->tileScale);

	states.texture = &this->tileset;

	target.draw(this->vertices, states);
}