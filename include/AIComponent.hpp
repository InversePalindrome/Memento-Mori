/*
Copyright (c) 2017 InversePalindrome
Memento Mori - AIComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"


enum class AI_ID { Goblin, AI_Count };

class AIComponent : public Component
{
public:
	AIComponent();

	virtual std::istringstream& readStream(std::istringstream& iStream) override;

	AI_ID getID() const;

	void setID(AI_ID ID);

private:
	AI_ID ID;
};
