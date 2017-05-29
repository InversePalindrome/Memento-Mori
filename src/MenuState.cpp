/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MenuState.cpp
InversePalindrome.com
*/


#include "MenuState.hpp"
#include "StateMachine.hpp"


MenuState::MenuState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData)
{
}

void MenuState::handleEvent(const sf::Event& event)
{

}

void MenuState::update(sf::Time deltaTime)
{

}

void MenuState::draw()
{

}