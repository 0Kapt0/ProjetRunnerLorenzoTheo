#include "game_state.h"
#include "pause_state.h"

GameState::GameState(sf::RenderWindow& window)
    : state(window)
{
    for (int i = 0; i < 11; ++i)
        game.addBlocNiveau(0);
}

void GameState::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        wantPause = true;
    }
}

void GameState::update(float dt)
{
    game.update(dt);
}

void GameState::draw()
{
    game.render(window);
}
