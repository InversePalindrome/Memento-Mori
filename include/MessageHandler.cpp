/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MessageHandler.cpp
InversePalindrome.com
*/


#include "MessageHandler.hpp"


void MessageHandler::subscribe(EntityMessage message, Observer* observer)
{
	this->subjects[message].addObserver(observer);
}

void MessageHandler::unsubscribe(EntityMessage message, Observer* observer)
{
	this->subjects[message].removeObserver(observer);
}

void MessageHandler::dispatch(const Message& message)
{
	auto messageItr = this->subjects.find(message.messageType);

	if (messageItr != std::end(this->subjects))
	{
		messageItr->second.broadcast(message);
	}
}