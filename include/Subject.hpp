/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Subject.hpp
InversePalindrome.com
*/


#pragma once

#include "Observer.hpp"

#include <set>


class Subject
{
public:
	void addObserver(Observer* observer);

	void removeObserver(Observer* observer);

	void broadcast(const Message& message);

private:
	std::set<Observer*> observers;
};