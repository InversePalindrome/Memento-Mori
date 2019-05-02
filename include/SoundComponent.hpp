/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SoundComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Component.hpp"
#include "SoundManager.hpp"
#include "ResourceIdentifiers.hpp"


class SoundComponent : public Component
{
public:
    SoundComponent();

    virtual std::istringstream& readStream(std::istringstream& iStream) override;

    SoundID getSoundID() const;

    void setSoundID(SoundID soundID);

private:
    SoundID soundID;
};