/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Message.hpp
InversePalindrome.com
*/


#pragma once

#include <cstddef>


struct Message
{
	enum class Type {};

	Message(Type type);

	Type type;
	std::size_t senderID;
	std::size_t receiverID;
};
