/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EventQueue.cpp
InversePalindrome.com
*/


#include "EventQueue.hpp"


void EventQueue::addEvent(std::size_t eventID)
{
	this->eventQueue.push(eventID);
}

bool EventQueue::processEvent(std::size_t& eventID)
{
	if (!this->eventQueue.empty())
	{
		eventID = this->eventQueue.front();
		this->eventQueue.pop();

		return true;
	}
	else
	{
		return false;
	}
}

void EventQueue::clearEvents()
{
	while (!this->eventQueue.empty())
	{
		this->eventQueue.pop();
    }
}