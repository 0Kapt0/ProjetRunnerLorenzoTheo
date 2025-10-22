#include "StateManager.h"

StateManager::StateManager(sf::RenderWindow& win)
    : window(win)
{
    changeState<menu>();
}

state* StateManager::getState() {
    return currentState.get();
}

void StateManager::run() {
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();

        if (currentState)
            currentState->handleInput();

        //IN MENU
        if (auto* m = dynamic_cast<menu*>(currentState.get())) {
            if (m->startGame) {
                m->startGame = false;
                changeState<GameState>();
            }
        }

        //IN GAME
        else if (auto* g = dynamic_cast<GameState*>(currentState.get())) {
            if (pauseMenu) {
                pauseMenu->handleInput();
                if (pauseMenu->resumeGame) {
                    pauseMenu.reset();
                }
                else if (pauseMenu->quitToMenu) {
                    pauseMenu.reset();
                    changeState<menu>();
                    if (auto* g = dynamic_cast<GameState*>(currentState.get())) {
                        g->stopMusic();
                    }
                }
            }
            //IN PAUSE
            else {
                g->handleInput();
                if (g->wantPause) {
                    g->wantPause = false;
                    pauseMenu = std::make_unique<PauseState>(window, g->getGame().getPlayerPosition());
                }
                g->update(dt);
            }
        }

        window.clear();
        if (currentState)
            currentState->draw();
        if (pauseMenu)
            pauseMenu->draw();
        window.display();
    }
}
