/*
Copyright (c) 2017 InversePalindrome
Memento Mori - GameState.cpp
InversePalindrome.com
*/


#include "GameState.hpp"
#include "StateMachine.hpp"
#include "SoundSystem.hpp"
#include "StateComponent.hpp"
#include "CollisionSystem.hpp"
#include "HealthComponent.hpp"

#include <fstream>


GameState::GameState(StateMachine& stateMachine, SharedData& sharedData) :
    State(stateMachine, sharedData),
    entityManager(systemManager, sharedData.textures),
    systemManager(),
    map(sharedData.textures[Textures::ID::TileMap], 18u, 32u, 32u, 6u, sf::Vector2f(2.5f, 2.5f)),
    spawnManager(map, entityManager),
    healthBar(sharedData.textures[Textures::ID::Heart]),
    roundNumber(sharedData.fonts[Fonts::ID::WolfsBane], &systemManager)
{
    systemManager.setEntityManager(entityManager);

    systemManager.getSystem<CollisionSystem>(System::ID::Collision)->setMap(map);
    systemManager.getSystem<SoundSystem>(System::ID::Sound)->setSoundManager(sharedData.soundManager);

    buildScene();
}

void GameState::handleEvent(const sf::Event& event)
{
    if (sharedData.keyBindings.isActive(ActionID::Pause))
    {
        this->transitionToPause();
    }
    else if (sharedData.keyBindings.isActive(ActionID::MoveUp))
    {
        this->movePlayer(Direction::Up);
    }
    else if (sharedData.keyBindings.isActive(ActionID::MoveDown))
    {
        this->movePlayer(Direction::Down);
    }
    else if (sharedData.keyBindings.isActive(ActionID::MoveRight))
    {
        this->movePlayer(Direction::Right);
    }
    else if (sharedData.keyBindings.isActive(ActionID::MoveLeft))
    {
        this->movePlayer(Direction::Left);
    }
    else if (sharedData.keyBindings.isActive(ActionID::Attack))
    {
        this->attack();
    }
    else
    {
        this->systemManager.addEvent(this->entityManager.getPlayerID(), EntityEvent::BecameIdle);
    }
}

void GameState::update(sf::Time deltaTime)
{
    this->systemManager.update(deltaTime);
    this->spawnManager.update(deltaTime);

    this->updateHealth();
    this->roundNumber.update(this->spawnManager.getRoundNumber());
}

void GameState::draw()
{
    this->sharedData.window.draw(this->map);
    this->systemManager.draw(this->sharedData.window);
    this->sharedData.window.draw(this->healthBar);
    this->sharedData.window.draw(this->roundNumber);
}

bool GameState::isTransparent()
{
    return true;
}

void GameState::buildScene()
{
    entityManager.addEntity("Resources/Files/Player.txt");
    entityManager.addEntity("Resources/Files/BlueCauldron.txt");
    entityManager.addEntity("Resources/Files/GreenCauldron.txt");
    entityManager.addEntity("Resources/Files/RedCauldron.txt");
    entityManager.addEntity("Resources/Files/PurpleCauldron.txt");
    entityManager.addEntity("Resources/Files/SmallEmptyChest.txt");
    entityManager.addEntity("Resources/Files/SmallLoadedChest.txt");
    entityManager.addEntity("Resources/Files/BigEmptyChest.txt");
    entityManager.addEntity("Resources/Files/BigLoadedChest.txt");
    entityManager.addEntity("Resources/Files/Barrel.txt");
}

void GameState::updateHealth()
{
    auto* health = this->entityManager.getComponent<HealthComponent>(this->entityManager.getPlayerID(), Component::ID::Health);

    if (health)
    {
        this->healthBar.setHealth(health->getHealth());
    }
    else
    {
        this->healthBar.setHealth(0u);
        this->saveScore();
        this->transitionToGameOver();
    }
}

void GameState::movePlayer(Direction direction)
{
    Message message(EntityMessage::Move);
    message.receiverID = this->entityManager.getPlayerID();
    message.data[DataID::Direction] = static_cast<std::size_t>(direction);

    this->systemManager.getMessageHandler()->dispatch(message);
}

void GameState::attack()
{
    Message message(EntityMessage::ChangeState);
    message.receiverID = this->entityManager.getPlayerID();
    message.data[DataID::State] = static_cast<std::size_t>(EntityState::Attacking);

    this->systemManager.getMessageHandler()->dispatch(message);

    this->systemManager.addEvent(this->entityManager.getPlayerID(), EntityEvent::ShootProjectile);
}

void GameState::saveScore()
{
    std::ifstream inFile("Resources/Files/HighScores.txt");

    std::size_t score1 = 1u, score2 = 1u, score3 = 1u;

    inFile >> score1 >> score2 >> score3;

    std::array<std::size_t, 4u> scores = { score1, score2, score3, this->spawnManager.getRoundNumber() };

    inFile.close();

    std::sort(std::rbegin(scores), std::rend(scores));

    std::ofstream outFile("Resources/Files/HighScores.txt", std::ios::out | std::ios::trunc);

    outFile << scores.at(0) << std::endl << scores.at(1) << std::endl << scores.at(2);

    outFile.close();
}

void GameState::transitionToPause()
{
    this->sharedData.soundManager.stopAllSounds();

    this->stateMachine.pushState(StateMachine::StateID::Pause);
}

void GameState::transitionToGameOver()
{
    this->sharedData.soundManager.stopAllSounds();

    this->stateMachine.pushState(StateMachine::StateID::GameOver);
}