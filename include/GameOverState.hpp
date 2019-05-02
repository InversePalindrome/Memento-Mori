/*
Copyright (c) 2017 InversePalindrome
Memento Mori - GameOverState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFGUI/Button.hpp>
#include <SFML/Graphics/Sprite.hpp>


class GameOverState : public State
{
public:
    GameOverState(StateMachine& stateMachine, SharedData& sharedData);

    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Time deltaTime) override;
    virtual void draw() override;

    virtual bool isTransparent() override;

private:
    sf::Sprite background;

    sfg::Button::Ptr playButton;
    sfg::Button::Ptr menuButton;
    sfg::Button::Ptr leaderboardButton;

    void transitionToPlay();
    void transitionToMenu();
    void transitionToLeaderboard();
};