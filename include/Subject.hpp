/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Subject.hpp
InversePalindrome.com
*/


#pragma once

#include "Observer.hpp"

#include <unordered_set>


class Subject
{
public:
    void addObserver(Observer* observer);

    void removeObserver(Observer* observer);

    void broadcast(const Message& message);

private:
    std::unordered_set<Observer*> observers;
};