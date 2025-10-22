#pragma once
#include "state.h"
#include "game.h"

class GameState : public state {
private:
    Game game;
    bool paused = false;

public:
    bool wantPause = false;

    GameState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float deltaTime) override;
    void draw() override;

    Game& getGame() { return game; }
};
