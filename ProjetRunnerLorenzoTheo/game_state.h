#pragma once
#include "state.h"
#include "game.h"
#include <SFML/Audio.hpp>

class GameState : public state {
private:
    Game game;
    sf::Music gameMusic;
    bool isPaused = false;
public:
    bool wantPause = false;
    bool wantGameOver = false;

    GameState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float deltaTime) override;
    void draw() override;

    void reloadMusic();

    bool getIsPaused() const { return isPaused; }
    void setIsPaused(bool state) { isPaused = state; }

    Game& getGame() { return game; }
    void stopMusic() { gameMusic.stop(); }
    sf::Music& getMusic() { return gameMusic; }
};
