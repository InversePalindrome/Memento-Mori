/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EventQueue.cpp
InversePalindrome.com
*/


#include "EventQueue.hpp"


void EventQueue::addEvent(EntityEvent event)
{
	this->events.push(event);
}

bool EventQueue::processEvent(EntityEvent& event)
{
	if (this->events.empty())
	{
		return false;
	}
	else
	{
		event = this->events.front();
		this->events.pop();
		return true;
	}
}

void EventQueue::clearEvents()
{
	while (!this->events.empty())
	{
		this->events.pop();
	}
}