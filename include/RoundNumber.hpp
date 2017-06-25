/*
Copyright (c) 2017 InversePalindrome
Memento Mori - RoundNumber.hpp
InversePalindrome.com
*/


#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <array>


class RoundNumber : public sf::Drawable
{
public:
	RoundNumber(const sf::Font& font);

	void update(std::size_t roundNumber);

private:
	sf::Text roundNumberText;
	std::size_t roundNumber;

	static const std::array<std::pair<std::size_t, std::string>, 13u> romanNumerals;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::string toRomanNumeral(std::size_t roundNumber);
};