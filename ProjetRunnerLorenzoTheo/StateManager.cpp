#include "StateManager.h"
#include "AudioSettings.h"

//test
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
            else if (m->openOptions) {
                m->openOptions = false;
                changeState<OptionsState>();
            }
        }

        //IN OPTIONS
        else if (auto* o = dynamic_cast<OptionsState*>(currentState.get())) {
            if (o->backToMenu) {
                o->backToMenu = false;
                changeState<menu>();
            }
        }

        // IN GAME
        else if (auto* g = dynamic_cast<GameState*>(currentState.get())) {

            g->handleInput();

            if (!pauseMenu) {
                g->update(dt);
            }

            if (!pauseMenu && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                pauseMenu = std::make_unique<PauseState>(window, g->getGame().getPlayerPosition());
            }

            if (g->getGame().getWantGameOver() && !gameOverMenu) {
                g->stopMusic();
                gameOverMenu = std::make_unique<GameOverState>(window);
            }

            if (pauseMenu) {
                pauseMenu->handleInput();
                if (pauseMenu->resumeGame)
                    pauseMenu.reset();
                else if (pauseMenu->restartGame) {
                    pauseMenu.reset();
                    changeState<GameState>();
                    continue;
                }

                else if (pauseMenu->quitToMenu) {
                    pauseMenu.reset();
                    changeState<menu>();
                    if (auto* g = dynamic_cast<GameState*>(currentState.get()))
                        g->stopMusic();
                    continue;
                }
            }

            if (gameOverMenu) {
                gameOverMenu->handleInput();
                if (gameOverMenu->restartGame) {
                    gameOverMenu.reset();
                    changeState<GameState>();
                    continue;
                }
                else if (gameOverMenu->quitToMenu) {
                    gameOverMenu.reset();
                    changeState<menu>();
                    continue;
                }
            }
        }


        if (auto* m = dynamic_cast<menu*>(currentState.get())) {
            AudioSettings::applyTo(m->getMusic());
        }
        else if (auto* g = dynamic_cast<GameState*>(currentState.get())) {
            AudioSettings::applyTo(g->getMusic());
        }

        window.clear();
        if (currentState)
            currentState->draw();
        if (pauseMenu)
            pauseMenu->draw();
        if (gameOverMenu)
            gameOverMenu->draw();
        window.display();
    }
}
