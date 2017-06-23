/*
Copyright (c) 2017 InversePalindrome
Memento Mori - StateMachine.cpp
InversePalindrome.com
*/


#include "StateMachine.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "SplashState.hpp"
#include "SettingsState.hpp"
#include "LeaderboardState.hpp"
#include "GameOverState.hpp"


StateMachine::StateMachine(SharedData& sharedData) :
	stateStack(),
	stackRequests(),
	stateFactory()
{
	registerState<SplashState>(StateID::Splash, sharedData);
	registerState<MenuState>(StateID::Menu, sharedData);
	registerState<GameState>(StateID::Game, sharedData);
	registerState<SettingsState>(StateID::Settings, sharedData);
	registerState<LeaderboardState>(StateID::Leaderboard, sharedData);
	registerState<PauseState>(StateID::Pause, sharedData);
	registerState<GameOverState>(StateID::GameOver, sharedData);
}

void StateMachine::handleEvent(const sf::Event& event)
{
	if (!this->stateStack.empty())
	{
		this->stateStack.back()->handleEvent(event);
	}

	this->processRequests();
}

void StateMachine::update(sf::Time deltaTime)
{
	if (!this->stateStack.empty())
	{
		this->stateStack.back()->update(deltaTime);
	}
	
	this->processRequests();
}

void StateMachine::draw()
{
	if (!this->stateStack.empty())
	{
		if (this->stateStack.back()->isTransparent() && this->stateStack.size() > 1)
		{
			auto itr = std::end(this->stateStack);

			for (; itr != std::begin(this->stateStack); --itr)
			{
				if (itr != std::end(this->stateStack) && !(*itr)->isTransparent())
				{
					break;
				}
			}

			for (; itr != std::end(this->stateStack); ++itr)
			{
				(*itr)->draw();
			}
		}
		else
		{
			this->stateStack.back()->draw();
		}
	}
}

void StateMachine::pushState(StateID stateID)
{
	this->stackRequests.push_back(std::make_pair(StackAction::Push, stateID));
}

void StateMachine::popState()
{
	this->stackRequests.push_back(std::make_pair(StackAction::Pop, StateID::Undefined));
}

void StateMachine::clearStates()
{
	this->stackRequests.push_back(std::make_pair(StackAction::Clear, StateID::Undefined));
}

StateMachine::StatePtr StateMachine::getState(StateID stateID)
{
	return this->stateFactory.find(stateID)->second();
}

void StateMachine::processRequests()
{
	for (const auto& request : this->stackRequests)
	{
		switch (request.first)
		{
		case StackAction::Push:
			this->stateStack.push_back(this->getState(request.second));
			break;
		case StackAction::Pop:
			this->stateStack.pop_back();
			break;
		case StackAction::Clear:
			this->stateStack.clear();
			break;
		}
	}

	this->stackRequests.clear();
}