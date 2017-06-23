/*
Copyright (c) 2017 InversePalindrome
Memento Mori - StateMachine.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "SharedData.hpp"

#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>


class StateMachine
{
	using StatePtr = std::unique_ptr<State>;

public:
	enum class StateID { Undefined, Splash, Menu, Game, Settings, Leaderboard, Pause, GameOver };
	enum class StackAction { Undefined, Push, Pop, Clear };

	StateMachine(SharedData& data);

	void handleEvent(const sf::Event& event);
	void update(sf::Time deltaTime);
	void draw();

	void pushState(StateID stateID);
	void popState();
	void clearStates();

private:
	std::vector<StatePtr> stateStack;
	std::vector<std::pair<StackAction, StateID>> stackRequests;
	std::unordered_map<StateID, std::function<StatePtr()>> stateFactory;

	template<typename T>
	void registerState(StateID stateID, SharedData& data);

	StatePtr getState(StateID stateID);
	void processRequests();
};


template<typename T>
void StateMachine::registerState(StateID stateID, SharedData& sharedData)
{
	this->stateFactory[stateID] = [this, &sharedData]()
	{
		return std::make_unique<T>(*this, sharedData);
	};
}