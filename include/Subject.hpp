/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Subject.hpp
InversePalindrome.com
*/


#pragma once

#include "Observer.hpp"

#include <vector>


class Subject
{
public:
	void addObserver(Observer& observer);
	void removeObserver(Observer& observer);

	void notifyObservers(const Message& message);

private:
	std::vector<Observer*> observers;
};
