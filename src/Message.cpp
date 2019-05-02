/*
Copyright (c) 2017 InversePalindrome
Memento Mori - Message.hpp
InversePalindrome.com
*/


#include "Message.hpp"


Message::Message(EntityMessage messageType) :
    messageType(messageType),
    senderID(0),
    receiverID(0),
    data()
{
}