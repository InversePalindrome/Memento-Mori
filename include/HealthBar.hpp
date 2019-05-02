/*
Copyright (c) 2017 InversePalindrome
Memento Mori - HealthBar.hpp
InversePalindrome.com
*/


#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cstddef>


class HealthBar : public sf::Drawable
{
    using Health = std::size_t;

public:
    HealthBar(sf::Texture& texture);

    void setHealth(Health health);

private:
    sf::Sprite hearts;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};