/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MessageHandler.hpp
InversePalindrome.com
*/


#pragma once

#include "Subject.hpp"

#include <unordered_map>


class MessageHandler
{
public:
    void subscribe(EntityMessage message, Observer* observer);

    void unsubscribe(EntityMessage message, Observer* observer);

    void dispatch(const Message& message);

private:
    std::unordered_map<EntityMessage, Subject> subjects;
};