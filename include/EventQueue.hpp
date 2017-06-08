/*
Copyright (c) 2017 InversePalindrome
Memento Mori - EventQueue.hpp
InversePalindrome.com
*/


#pragma once

#include <queue>


class EventQueue
{
public:
	void addEvent(std::size_t eventID);

	bool processEvent(std::size_t& eventID);

	void clearEvents();

private:
	std::queue<std::size_t> eventQueue;
};
