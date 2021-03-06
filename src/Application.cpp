/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <Thor/Resources/SfmlLoaders.hpp>


const sf::Time Application::timePerFrame(sf::seconds(1.f / 60.f));

Application::Application() :
    window(sf::VideoMode(2560u, 1440u), "Memento Mori", sf::Style::Close | sf::Style::Titlebar),
    gui(),
    hud(),
    textures(),
    images(),
    sounds(),
    fonts(),
    soundManager(sounds),
    keyBindings(),
    sharedData(window, gui, hud, textures, images, sounds, fonts, soundManager, keyBindings),
    stateMachine(sharedData)
{
    loadTextures();

    stateMachine.pushState(StateMachine::StateID::Splash);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time elapsedTime = sf::Time::Zero;

    while (this->window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        elapsedTime += deltaTime;

        while (elapsedTime > timePerFrame)
        {
            elapsedTime -= timePerFrame;

            this->processInput();
            this->update(timePerFrame);
        }

        this->render();
    }
}

void Application::processInput()
{
    sf::Event event;

    this->keyBindings.clearEvents();

    while (this->window.pollEvent(event))
    {
        this->hud.HandleEvent(event);
        this->stateMachine.handleEvent(event);

        this->keyBindings.pushEvent(event);

        switch (event.type)
        {
        case sf::Event::Closed:
            this->window.close();
        }
    }
}

void Application::update(sf::Time deltaTime)
{
    this->stateMachine.update(deltaTime);
    this->hud.Update(deltaTime.asMicroseconds());
    this->keyBindings.update(this->window);
}

void Application::render()
{
    this->window.clear(sf::Color::White);

    this->stateMachine.draw();
    this->gui.Display(this->window);
    this->window.display();
}

void Application::loadTextures()
{
    this->textures.acquire(Textures::ID::Logo, thor::Resources::fromFile<sf::Texture>("Resources/Images/InversePalindromeLogo.png"));
    this->textures.acquire(Textures::ID::MainBackground, thor::Resources::fromFile<sf::Texture>("Resources/Images/MainBackground.png"));
    this->textures.acquire(Textures::ID::MenuBackground, thor::Resources::fromFile<sf::Texture>("Resources/Images/MenuBackground.png"));
    this->textures.acquire(Textures::ID::SettingsBackground, thor::Resources::fromFile<sf::Texture>("Resources/Images/SettingsBackground.png"));
    this->textures.acquire(Textures::ID::LeaderboardBackground, thor::Resources::fromFile<sf::Texture>("Resources/Images/HighScoresBackground.png"));
    this->textures.acquire(Textures::ID::GameOverBackground, thor::Resources::fromFile<sf::Texture>("Resources/Images/GameOverBackground.png"));
    this->textures.acquire(Textures::ID::DecoAttackingSkeleton, thor::Resources::fromFile<sf::Texture>("Resources/Images/DecoAttackingSkeleton.png"));
    this->textures.acquire(Textures::ID::DecoJumpingSkeleton, thor::Resources::fromFile<sf::Texture>("Resources/Images/DecoJumpingSkeleton.png"));
    this->textures.acquire(Textures::ID::StarParticle, thor::Resources::fromFile<sf::Texture>("Resources/Images/StarParticle.png"));
    this->textures.acquire(Textures::ID::PauseMenu, thor::Resources::fromFile<sf::Texture>("Resources/Images/PauseMenu.png"));
    this->textures.acquire(Textures::ID::TileMap, thor::Resources::fromFile<sf::Texture>("Resources/Images/TileMap.png"));
    this->textures.acquire(Textures::ID::ObjectsSheet, thor::Resources::fromFile<sf::Texture>("Resources/Images/ObjectsSheet.png"));
    this->textures.acquire(Textures::ID::Skeleton, thor::Resources::fromFile<sf::Texture>("Resources/Images/Skeleton.png"));
    this->textures.acquire(Textures::ID::Goblin, thor::Resources::fromFile<sf::Texture>("Resources/Images/Goblin.png"));
    this->textures.acquire(Textures::ID::Wizard, thor::Resources::fromFile<sf::Texture>("Resources/Images/Wizard.png"));
    this->textures.acquire(Textures::ID::Heart, thor::Resources::fromFile<sf::Texture>("Resources/Images/Heart.png"));
    this->textures.acquire(Textures::ID::Fireball, thor::Resources::fromFile<sf::Texture>("Resources/Images/Fireball.png"));

    this->images.acquire(Images::ID::PlayButton, thor::Resources::fromFile<sf::Image>("Resources/Images/PlayButton.png"));
    this->images.acquire(Images::ID::SettingsButton, thor::Resources::fromFile<sf::Image>("Resources/Images/SettingsButton.png"));
    this->images.acquire(Images::ID::LeaderboardButton, thor::Resources::fromFile<sf::Image>("Resources/Images/LeaderboardButton.png"));
    this->images.acquire(Images::ID::BackButton, thor::Resources::fromFile<sf::Image>("Resources/Images/BackButton.png"));
    this->images.acquire(Images::ID::MenuButton, thor::Resources::fromFile<sf::Image>("Resources/Images/MenuButton.png"));
    this->images.acquire(Images::ID::ResumeButton, thor::Resources::fromFile<sf::Image>("Resources/Images/ResumeButton.png"));
    this->images.acquire(Images::ID::RestartButton, thor::Resources::fromFile<sf::Image>("Resources/Images/RestartButton.png"));
    this->images.acquire(Images::ID::SettingsButton2, thor::Resources::fromFile<sf::Image>("Resources/Images/SettingsButton2.png"));
    this->images.acquire(Images::ID::QuitButton, thor::Resources::fromFile<sf::Image>("Resources/Images/QuitButton.png"));
    this->images.acquire(Images::ID::ToggleButtonOn, thor::Resources::fromFile<sf::Image>("Resources/Images/ToggleButtonOn.png"));
    this->images.acquire(Images::ID::ToggleButtonOff, thor::Resources::fromFile<sf::Image>("Resources/Images/ToggleButtonOff.png"));
    this->images.acquire(Images::ID::MoveUp, thor::Resources::fromFile<sf::Image>("Resources/Images/MoveUp.png"));
    this->images.acquire(Images::ID::MoveDown, thor::Resources::fromFile<sf::Image>("Resources/Images/MoveDown.png"));
    this->images.acquire(Images::ID::MoveRight, thor::Resources::fromFile<sf::Image>("Resources/Images/MoveRight.png"));
    this->images.acquire(Images::ID::MoveLeft, thor::Resources::fromFile<sf::Image>("Resources/Images/MoveLeft.png"));

    this->images.acquire(Images::ID::Attack, thor::Resources::fromFile<sf::Image>("Resources/Images/AttackButton.png"));

    this->fonts.acquire(Fonts::ID::WolfsBane, thor::Resources::fromFile<sf::Font>("Resources/Fonts/WolfsBane.ttf"));

    this->sounds.acquire(SoundBuffers::ID::Footstep, thor::Resources::fromFile<sf::SoundBuffer>("Resources/Sounds/Footsteps.wav"));
    this->sounds.acquire(SoundBuffers::ID::Fireball, thor::Resources::fromFile<sf::SoundBuffer>("Resources/Sounds/Fireball.wav"));
    this->sounds.acquire(SoundBuffers::ID::RoundStarted, thor::Resources::fromFile<sf::SoundBuffer>("Resources/Sounds/RoundStarted.wav"));
    this->sounds.acquire(SoundBuffers::ID::Pickup, thor::Resources::fromFile<sf::SoundBuffer>("Resources/Sounds/Pickup.ogg"));
}