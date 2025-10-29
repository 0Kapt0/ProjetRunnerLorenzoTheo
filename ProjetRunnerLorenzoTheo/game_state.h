#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include "state.h"
#include "game.h"
#include "pause_state.h"
#include "audio_settings.h"

class GameState : public State {
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
