#pragma once
#include "state.h"
#include "game.h"
#include <SFML/Audio.hpp>

class GameState : public state {
private:
    Game game;
    bool paused = false;
    sf::Music gameMusic;

    bool isPaused = true;
    float timeGame = 0;
    sf::Clock clock;
public:
    bool wantPause = false;
    bool wantGameOver = false;

    GameState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float deltaTime) override;
    void draw() override;

    Game& getGame() { return game; }
    void stopMusic() { gameMusic.stop(); }
    sf::Music& getMusic() { return gameMusic; }
};
