/*
Copyright (c) 2017 InversePalindrome
Memento Mori - GameState.hpp
InversePalindrome.com
*/


#pragma once

#include "Map.hpp"
#include "State.hpp"
#include "HealthBar.hpp"
#include "Direction.hpp"
#include "RoundNumber.hpp"
#include "SpawnManager.hpp"
#include "SoundManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"


class GameState : public State
{
public:
    GameState(StateMachine& stateMachine, SharedData& sharedData);

    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Time deltaTime) override;
    virtual void draw() override;

    virtual bool isTransparent() override;

private:
    EntityManager entityManager;
    SystemManager systemManager;
    Map map;
    SpawnManager spawnManager;
    HealthBar healthBar;
    RoundNumber roundNumber;

    void buildScene();

    void updateHealth();
    void movePlayer(Direction direction);
    void attack();

    void saveScore();

    void transitionToPause();
    void transitionToGameOver();
};
