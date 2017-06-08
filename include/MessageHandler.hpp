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
	using Subscriptions = std::unordered_map<Message::Type, Subject>;

public:
	void subscribe(Message::Type messageType, Observer& observer);

	void unsubscribe(Message::Type messageType, Observer& observer);

	void dispatch(const Message& message);

private:
	Subscriptions subjects;
};
