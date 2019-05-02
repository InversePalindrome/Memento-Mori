/*
Copyright (c) 2017 InversePalindrome
Memento Mori - SettingsState.cpp
InversePalindrome.com
*/


#include "SettingsState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>


SettingsState::SettingsState(StateMachine& stateMachine, SharedData& sharedData) :
    State(stateMachine, sharedData),
    background(sharedData.textures[Textures::ID::MainBackground]),
    controlCenter(sharedData.textures[Textures::ID::SettingsBackground]),
    backButton(sfg::Button::Create()),
    volumeLabel(sfg::Label::Create("Volume")),
    soundLabel(sfg::Label::Create("Sound")),
    musicLabel(sfg::Label::Create("Music")),
    soundSwitch(sfg::ToggleButton::Create()),
    musicSwitch(sfg::ToggleButton::Create()),
    moveUpButton(sfg::ToggleButton::Create()),
    moveDownButton(sfg::ToggleButton::Create()),
    moveRightButton(sfg::ToggleButton::Create()),
    moveLeftButton(sfg::ToggleButton::Create()),
    attackButton(sfg::ToggleButton::Create()),
    volumeBar(sfg::Scrollbar::Create()),
    volumeScale(sfg::Scale::Create(sfg::Scale::Orientation::VERTICAL)),
    volumeAdjustment(sfg::Adjustment::Create(sharedData.soundManager.getSoundProperties().volume, 0.f, 100.f, 1.f, 5.f, 2.5f)),
    actionKeys()
{
    background.setScale(static_cast<float>(sharedData.window.getSize().x) / background.getLocalBounds().width,
        static_cast<float>(sharedData.window.getSize().y) / background.getLocalBounds().height);

    controlCenter.setScale(1.1f, 1.1f);
    controlCenter.setPosition(690.f, 200.f);

    backButton->SetPosition(sf::Vector2f(30.f, 70.f));
    backButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::BackButton]));
    backButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToMenu(); });

    soundLabel->SetPosition(sf::Vector2f(880.f, 725.f));

    soundSwitch->SetPosition(sf::Vector2f(1075.f, 750.f));
    soundSwitch->SetActive(sharedData.soundManager.isSoundEnabled());
    soundSwitch->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { switchSounds(); });
    switchSounds();

    musicLabel->SetPosition(sf::Vector2f(1380.f, 725.f));

    musicSwitch->SetPosition(sf::Vector2f(1565.f, 750.f));
    musicSwitch->SetActive(sharedData.soundManager.isMusicEnabled());
    musicSwitch->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { switchMusic(); });
    switchMusic();

    moveUpButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::MoveUp]));
    moveUpButton->SetPosition(sf::Vector2f(767.f, 500.f));

    moveDownButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::MoveDown]));
    moveDownButton->SetPosition(sf::Vector2f(967.f, 500.f));

    moveRightButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::MoveRight]));
    moveRightButton->SetPosition(sf::Vector2f(1167.f, 500.f));

    moveLeftButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::MoveLeft]));
    moveLeftButton->SetPosition(sf::Vector2f(1367.f, 500.f));

    attackButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::Attack]));
    attackButton->SetPosition(sf::Vector2f(1567.f, 500.f));

    volumeLabel->SetPosition(sf::Vector2f(1160.f, 922.f));

    volumeBar->SetRequisition(sf::Vector2f(1000.f, 75.f));
    volumeBar->SetPosition(sf::Vector2f(788.f, 850.f));
    volumeBar->SetAdjustment(volumeAdjustment);

    volumeScale->SetAdjustment(volumeAdjustment);

    volumeAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect([this] { adjustVolume(); });

    actionKeys.emplace(ActionID::MoveUp, moveUpButton);
    actionKeys.emplace(ActionID::MoveDown, moveDownButton);
    actionKeys.emplace(ActionID::MoveRight, moveRightButton);
    actionKeys.emplace(ActionID::MoveLeft, moveLeftButton);
    actionKeys.emplace(ActionID::Attack, attackButton);

    sharedData.hud.SetProperty("Label", "FontSize", 80.f);
    sharedData.hud.SetProperty("Label", "FontName", "Resources/Fonts/WolfsBane.ttf");
    sharedData.hud.SetProperty("Label", "Color", sf::Color(14u, 208u, 78u, 255u));
    sharedData.hud.SetProperty("ToggleButton", "BackgroundColor", sf::Color::Transparent);
    sharedData.hud.SetProperty("ToggleButton", "BorderColor", sf::Color::Transparent);
    sharedData.hud.SetProperty("ToggleButton:PRELIGHT", "BackgroundColor", sf::Color::Transparent);
    sharedData.hud.SetProperty("Scrollbar", "BackgroundColor", sf::Color(14u, 208u, 78u, 255u));
    sharedData.hud.Add(backButton);
    sharedData.hud.Add(volumeLabel);
    sharedData.hud.Add(soundLabel);
    sharedData.hud.Add(musicLabel);
    sharedData.hud.Add(soundSwitch);
    sharedData.hud.Add(musicSwitch);
    sharedData.hud.Add(moveUpButton);
    sharedData.hud.Add(moveDownButton);
    sharedData.hud.Add(moveRightButton);
    sharedData.hud.Add(moveLeftButton);
    sharedData.hud.Add(attackButton);
    sharedData.hud.Add(volumeBar);
}

void SettingsState::handleEvent(const sf::Event & event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        this->changeKey(event.key.code);
        break;
    }
}

void SettingsState::update(sf::Time deltaTime)
{
    this->backButton->Show(true);
}

void SettingsState::draw()
{
    this->sharedData.window.draw(this->background);
    this->sharedData.window.draw(this->controlCenter);
}

bool SettingsState::isTransparent()
{
    return false;
}

void SettingsState::switchSounds()
{
    if (this->soundSwitch->IsActive())
    {
        this->sharedData.soundManager.setSoundStatus(true);
        this->sharedData.soundManager.playAllSounds();

        soundSwitch->SetImage(sfg::Image::Create(sharedData.images[Images::ID::ToggleButtonOn]));
    }
    else
    {
        this->sharedData.soundManager.setSoundStatus(false);
        this->sharedData.soundManager.pauseAllSounds();

        soundSwitch->SetImage(sfg::Image::Create(sharedData.images[Images::ID::ToggleButtonOff]));
    }
}

void SettingsState::switchMusic()
{
    if (this->musicSwitch->IsActive())
    {
        this->sharedData.soundManager.setMusicStatus(true);
        this->sharedData.soundManager.playAllMusic();

        musicSwitch->SetImage(sfg::Image::Create(sharedData.images[Images::ID::ToggleButtonOn]));
    }
    else
    {
        this->sharedData.soundManager.setMusicStatus(false);
        this->sharedData.soundManager.pauseAllMusic();

        musicSwitch->SetImage(sfg::Image::Create(sharedData.images[Images::ID::ToggleButtonOff]));
    }
}

void SettingsState::adjustVolume()
{
    this->sharedData.soundManager.changeVolume(volumeScale->GetValue());
}

void SettingsState::changeKey(sf::Keyboard::Key key)
{
    for (auto& actionKey : this->actionKeys)
    {
        if (actionKey.second->IsActive())
        {
            this->sharedData.keyBindings.changeKey(actionKey.first, thor::Action(key));

            actionKey.second->SetActive(false);
        }
    }
}

void SettingsState::transitionToMenu()
{
    this->backButton->Show(false);
    this->volumeLabel->Show(false);
    this->soundLabel->Show(false);
    this->musicLabel->Show(false);
    this->soundSwitch->Show(false);
    this->musicSwitch->Show(false);
    this->moveUpButton->Show(false);
    this->moveDownButton->Show(false);
    this->moveRightButton->Show(false);
    this->moveLeftButton->Show(false);
    this->attackButton->Show(false);
    this->volumeBar->Show(false);

    this->stateMachine.popState();
}