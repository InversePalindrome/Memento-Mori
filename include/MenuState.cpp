/*
Copyright (c) 2017 InversePalindrome
Memento Mori - MenuState.cpp
InversePalindrome.com
*/


#include "MenuState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>
#include <Thor/Math/Distributions.hpp>
#include <Thor/Particles/Emitters.hpp>
#include <Thor/Particles/Affectors.hpp>
#include <Thor/Animations/FadeAnimation.hpp>
#include <Thor/Animations/FrameAnimation.hpp>


MenuState::MenuState(StateMachine& stateMachine, SharedData& sharedData) :
	State(stateMachine, sharedData),
	background(sharedData.textures[Textures::ID::MenuBackground]),
	attackingSkeleton(sharedData.textures[Textures::ID::DecoAttackingSkeleton]),
	jumpingSkeleton(sharedData.textures[Textures::ID::DecoJumpingSkeleton]),
	playButton(sfg::Button::Create()),
	settingsButton(sfg::Button::Create()),
	leaderboardButton(sfg::Button::Create()),
	attackAnimator(),
	jumpAnimator(),
	particleSystem(),
	animationCountdown(sf::seconds(3.f))
{
	background.setScale(static_cast<float>(sharedData.window.getSize().x) / background.getLocalBounds().width,
		static_cast<float>(sharedData.window.getSize().y) / background.getLocalBounds().height);

	attackingSkeleton.setPosition(sf::Vector2f(60.f, 700.f));
	jumpingSkeleton.setPosition(sf::Vector2f(2000.f, 700.f));

	playButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::PlayButton]));
	playButton->SetPosition(sf::Vector2f(1120.f, 1000.f));
	playButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToGame(); });

	settingsButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::SettingsButton]));
	settingsButton->SetPosition(sf::Vector2f(720.f, 1000.f));
	settingsButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToSettings(); });

	leaderboardButton->SetImage(sfg::Image::Create(sharedData.images[Images::ID::LeaderboardButton]));
	leaderboardButton->SetPosition(sf::Vector2f(1520.f, 1000.f));
	leaderboardButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToLeaderboard(); });

	thor::UniversalEmitter emitter;
	emitter.setEmissionRate(2.f);
	emitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(3.f), sf::seconds(8.f)));
	emitter.setParticlePosition(thor::Distributions::rect(sf::Vector2f(sharedData.window.getSize().x / 2.f,sharedData.window.getSize().y / 2.f - 400.f),
		sf::Vector2f(sharedData.window.getSize().x / 2.f, sharedData.window.getSize().y / 2.f - 400.f)));

	thor::FrameAnimation attackAnimation;
	attackAnimation.addFrame(1.f, sf::IntRect(0u, 0u, 518u, 512u));
	attackAnimation.addFrame(1.f, sf::IntRect(519u, 0u, 518u, 512u));
	attackAnimation.addFrame(1.f, sf::IntRect(1038u, 0u, 518u, 512u));
	attackAnimation.addFrame(1.f, sf::IntRect(0u, 513u, 518u, 512u));
	attackAnimation.addFrame(1.f, sf::IntRect(519u, 513u, 518u, 512u));
	attackAnimation.addFrame(1.f, sf::IntRect(1038u, 513u, 518u, 512u));
	attackAnimation.addFrame(1.f, sf::IntRect(0u, 0u, 518u, 512u));

	thor::FrameAnimation jumpAnimation;
	jumpAnimation.addFrame(1.f, sf::IntRect(0u, 0u, 446u, 544u));
	jumpAnimation.addFrame(1.f, sf::IntRect(447u, 0u, 446u, 544u));
	jumpAnimation.addFrame(1.f, sf::IntRect(894u, 0u, 446u, 544u));
	jumpAnimation.addFrame(1.f, sf::IntRect(1341u, 0u, 446u, 544u));
	jumpAnimation.addFrame(1.f, sf::IntRect(0u, 545u, 446u, 544u));
	jumpAnimation.addFrame(1.f, sf::IntRect(447u, 545u, 446u, 544u));
	jumpAnimation.addFrame(1.f, sf::IntRect(894u, 545u, 446u, 544u));
	jumpAnimation.addFrame(1.f, sf::IntRect(0u, 0u, 446u, 544u));

	attackAnimator.addAnimation("Attack", attackAnimation, sf::seconds(0.6f));
	attackAnimator.playAnimation("Attack");

	jumpAnimator.addAnimation("Jump", jumpAnimation, sf::seconds(0.6f));
	jumpAnimator.playAnimation("Jump");

	particleSystem.setTexture(sharedData.textures[Textures::ID::StarParticle]);
	particleSystem.addEmitter(emitter);
	particleSystem.addAffector(thor::AnimationAffector(thor::FadeAnimation(0.3f, 0.3f)));

	sharedData.hud.SetProperty("Button", "BackgroundColor", sf::Color::Transparent);
	sharedData.hud.SetProperty("Button", "BorderColor", sf::Color::Transparent);
	sharedData.hud.SetProperty("Button:PRELIGHT", "BackgroundColor", sf::Color::Transparent);
	
	sharedData.hud.Add(playButton);
	sharedData.hud.Add(settingsButton);
	sharedData.hud.Add(leaderboardButton);

	sharedData.soundManager.playMusic("SpookyMusic.wav", true);
}

void MenuState::handleEvent(const sf::Event& event)
{

}

void MenuState::update(sf::Time deltaTime)
{
	this->playButton->Show(true);
	this->settingsButton->Show(true);
	this->leaderboardButton->Show(true);

	this->animationCountdown -= deltaTime;

	this->attackAnimator.update(deltaTime);
	this->attackAnimator.animate(this->attackingSkeleton);

	if(!this->attackAnimator.isPlayingAnimation() && this->animationCountdown.asSeconds() <= 0.f)
	{
		this->attackAnimator.playAnimation("Attack");
		this->animationCountdown = sf::seconds(2.f);
	}

	this->jumpAnimator.update(deltaTime);
	this->jumpAnimator.animate(this->jumpingSkeleton);

	if (!this->jumpAnimator.isPlayingAnimation() && this->animationCountdown.asSeconds() <= 1.5f)
	{
		this->jumpAnimator.playAnimation("Jump");
	}

	this->particleSystem.update(deltaTime);
}

void MenuState::draw()
{
	this->sharedData.window.draw(this->background);
	this->sharedData.window.draw(this->attackingSkeleton);
	this->sharedData.window.draw(this->jumpingSkeleton);
	this->sharedData.window.draw(this->particleSystem);
}

bool MenuState::isTransparent()
{
	return false;
}

void MenuState::transitionToGame()
{
	this->playButton->Show(false);
	this->settingsButton->Show(false);
	this->leaderboardButton->Show(false);

	this->sharedData.soundManager.stopAllMusic();

	this->stateMachine.popState();
	this->stateMachine.pushState(StateMachine::StateID::Game);
}

void MenuState::transitionToSettings()
{
	this->playButton->Show(false);
	this->settingsButton->Show(false);
	this->leaderboardButton->Show(false);

	this->stateMachine.pushState(StateMachine::StateID::Settings);
}

void MenuState::transitionToLeaderboard()
{
	this->playButton->Show(false);
	this->settingsButton->Show(false);
	this->leaderboardButton->Show(false);

	this->stateMachine.pushState(StateMachine::StateID::Leaderboard);
}