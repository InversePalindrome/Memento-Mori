/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Subject.cpp
InversePalindrome.com
*/


#include "Subject.hpp"


void Subject::addObserver(Observer* observer)
{
    this->observers.insert(observer);
}

void Subject::removeObserver(Observer* observer)
{
    this->observers.erase(observer);
}

void Subject::broadcast(const Message& message)
{
    for (auto& observer : this->observers)
    {
        observer->notify(message);
    }
}