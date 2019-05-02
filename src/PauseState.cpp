/*
Copyright (c) 2017 InversePalindrome
Memento Mori - PauseState.cpp
InversePalindrome.com
*/


#include "PauseState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>


PauseState::PauseState(StateMachine& stateMachine, SharedData& sharedData) :
    State(stateMachine, sharedData),
    pauseMenu(sharedData.textures[Textures::ID::PauseMenu]),
    resumeButton(sfg::Button::Create()),
    restartButton(sfg::Button::Create()),
    settingsButton(sfg::Button::Create()),
    quitButton(sfg::Button::Create())
{
    pauseMenu.setPosition(sf::Vector2f(1020.f, 280.f));

    resumeButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::ResumeButton]));
    resumeButton->SetPosition(sf::Vector2f(1078.f, 428.f));
    resumeButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToGame(); });

    restartButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::RestartButton]));
    restartButton->SetPosition(sf::Vector2f(1078.f, 578.f));
    restartButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { restartGame(); });

    settingsButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::SettingsButton2]));
    settingsButton->SetPosition(sf::Vector2f(1078.f, 728.f));
    settingsButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToSettings(); });

    quitButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::QuitButton]));
    quitButton->SetPosition(sf::Vector2f(1078.f, 878.f));
    quitButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToMenu(); });

    sharedData.hud.Add(resumeButton);
    sharedData.hud.Add(restartButton);
    sharedData.hud.Add(settingsButton);
    sharedData.hud.Add(quitButton);
}

void PauseState::handleEvent(const sf::Event& event)
{

}

void PauseState::update(sf::Time deltaTime)
{
    this->resumeButton->Show(true);
    this->restartButton->Show(true);
    this->settingsButton->Show(true);
    this->quitButton->Show(true);
}

void PauseState::draw()
{
    this->sharedData.window.draw(this->pauseMenu);
}

bool PauseState::isTransparent()
{
    return true;
}

void PauseState::transitionToGame()
{
    this->resumeButton->Show(false);
    this->restartButton->Show(false);
    this->settingsButton->Show(false);
    this->quitButton->Show(false);

    this->stateMachine.popState();
}

void PauseState::restartGame()
{
    this->resumeButton->Show(false);
    this->restartButton->Show(false);
    this->settingsButton->Show(false);
    this->quitButton->Show(false);

    this->stateMachine.clearStates();
    this->stateMachine.pushState(StateMachine::StateID::Game);
}

void PauseState::transitionToSettings()
{
    this->resumeButton->Show(false);
    this->restartButton->Show(false);
    this->settingsButton->Show(false);
    this->quitButton->Show(false);

    this->stateMachine.pushState(StateMachine::StateID::Settings);
}

void PauseState::transitionToMenu()
{
    this->resumeButton->Show(false);
    this->restartButton->Show(false);
    this->settingsButton->Show(false);
    this->quitButton->Show(false);

    this->stateMachine.clearStates();
    this->stateMachine.pushState(StateMachine::StateID::Menu);
}