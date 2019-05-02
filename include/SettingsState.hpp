/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SettingsState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "KeyBindings.hpp"

#include <SFGUI/Label.hpp>
#include <SFGUI/Scale.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Scrollbar.hpp>
#include <SFGUI/Adjustment.hpp>
#include <SFGUI/ToggleButton.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <unordered_map>


class SettingsState : public State
{
public:
    SettingsState(StateMachine& stateMachine, SharedData& sharedData);

    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Time deltaTime) override;
    virtual void draw() override;

    virtual bool isTransparent() override;

private:
    sf::Sprite background;
    sf::Sprite controlCenter;

    sfg::Button::Ptr backButton;
    sfg::Label::Ptr volumeLabel;
    sfg::Label::Ptr soundLabel;
    sfg::Label::Ptr musicLabel;
    sfg::ToggleButton::Ptr soundSwitch;
    sfg::ToggleButton::Ptr musicSwitch;
    sfg::ToggleButton::Ptr moveUpButton;
    sfg::ToggleButton::Ptr moveDownButton;
    sfg::ToggleButton::Ptr moveRightButton;
    sfg::ToggleButton::Ptr moveLeftButton;
    sfg::ToggleButton::Ptr attackButton;
    sfg::Scrollbar::Ptr volumeBar;
    sfg::Scale::Ptr volumeScale;
    sfg::Adjustment::Ptr volumeAdjustment;

    std::unordered_map<ActionID, sfg::ToggleButton::Ptr> actionKeys;

    void switchSounds();
    void switchMusic();

    void adjustVolume();

    void changeKey(sf::Keyboard::Key key);

    void transitionToMenu();
};
