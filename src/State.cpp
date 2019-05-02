/*
Copyright (c) 2017 InversePalindrome
Memento Mori - State.cpp
InversePalindrome.com
*/


#include "State.hpp"


State::State(StateMachine& stateMachine, SharedData& sharedData) :
    stateMachine(stateMachine),
    sharedData(sharedData)
{
}