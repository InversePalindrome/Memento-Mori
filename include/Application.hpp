/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Application.hpp
InversePalindrome.com
*/


#pragma once

#include "SharedData.hpp"
#include "StateMachine.hpp"
#include "SoundManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Application
{
public:
    Application();

    void run();

private:
    static const sf::Time timePerFrame;

    sf::RenderWindow window;
    sfg::SFGUI gui;
    sfg::Desktop hud;

    TextureHolder textures;
    ImageHolder images;
    SoundHolder sounds;
    FontHolder fonts;

    SoundManager soundManager;

    KeyBindings keyBindings;

    SharedData sharedData;
    StateMachine stateMachine;

    void processInput();
    void update(sf::Time deltaTime);
    void render();

    void loadTextures();
};
