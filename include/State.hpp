/*
Copyright (c) 2017 InversePalindrome
Memento Mori - State.hpp
InversePalindrome.com
*/


#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>


struct SharedData;
class StateMachine;

class State
{
public:
    State(StateMachine& stateMachine, SharedData& sharedData);

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw() = 0;

    virtual bool isTransparent() = 0;

protected:
    StateMachine& stateMachine;
    SharedData& sharedData;
};