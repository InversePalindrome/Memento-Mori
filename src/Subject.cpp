/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Subject.cpp
InversePalindrome.com
*/


#include "Subject.hpp"

#include <algorithm>


void Subject::addObserver(Observer& observer)
{
	if (std::find(std::begin(this->observers), std::end(this->observers), &observer) == std::end(this->observers))
	{
		this->observers.push_back(&observer);
	}
}

void Subject::removeObserver(Observer& observer)
{
	this->observers.erase(std::remove(std::begin(this->observers), std::end(this->observers), &observer), std::end(this->observers));
}

void Subject::notifyObservers(const Message& message)
{
	for (auto& observer : this->observers)
	{
		observer->notify(message);
	}
}