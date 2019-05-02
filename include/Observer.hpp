/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Observer.hpp
InversePalindrome.com
*/


#pragma once

#include "Message.hpp"


class Observer
{
public:
    virtual void notify(const Message& message) = 0;
};
