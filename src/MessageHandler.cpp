/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MessageHandler.cpp
InversePalindrome.com
*/


#include "MessageHandler.hpp"


void MessageHandler::subscribe(Message::Type messageType, Observer& observer)
{
	this->subjects[messageType].addObserver(observer);
}

void MessageHandler::unsubscribe(Message::Type messageType, Observer& observer)
{
	this->subjects[messageType].removeObserver(observer);
}

void MessageHandler::dispatch(const Message& message)
{
	auto observerItr = this->subjects.find(message.type);

	if (observerItr != std::end(this->subjects))
	{
		observerItr->second.notifyObservers(message);
	}
}