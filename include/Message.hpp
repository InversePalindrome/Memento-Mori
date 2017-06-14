/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Message.hpp
InversePalindrome.com
*/


#pragma once

#include <cstddef>
#include <unordered_map>


enum class EntityMessage { ChangeState, StateChanged, DirectionChanged, Move,  };
enum class DataID { State, Direction };

struct Message
{
	Message(EntityMessage messageType);

	EntityMessage messageType;

	std::size_t senderID;
	std::size_t receiverID;
	std::unordered_map<DataID, std::size_t> data;
};