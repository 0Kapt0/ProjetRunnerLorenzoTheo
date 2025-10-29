#include "StateManager.h"
#include "AudioSettings.h"

#include <iostream>
StateManager::StateManager(sf::RenderWindow& win): window(win), optionsState(win), gameState(win), gameOverState(win), pauseState(win), statsState(win), menuState(win) {}
/*
StateManager::State StateManager::getState() {
    return currentState;
}*/

state* StateManager::getState() {
    if (currentState == menu)
    {
        return &menuState;
    }
    else if (currentState == pause)
    {
        return &pauseState;
    }
    else if (currentState == play)
    {
        return &gameState;
    }
    else if (currentState == gameover)
    {
        return &gameOverState;
    }
    else if (currentState == stats)
    {
        return &statsState;
    }
    else if (currentState == options)
    {
        return &optionsState;
    }
}


void StateManager::run() {
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();

        getState()->handleInput();

        //IN MENU
        if (currentState == menu) {
            if (menuState.startGame) {
                menuState.startGame = false;
                menuState.getMusic().stop();
                gameState.reloadMusic();
                currentState = play;
            }
            else if (menuState.openOptions) {
                menuState.openOptions = false;
                currentState = options;
            }
            else if (menuState.openStats) {
                menuState.openStats = false;
                currentState = stats;
            }
        }

        //IN OPTIONS
        else if (currentState == options) {
            if (optionsState.backToMenu) {
                optionsState.backToMenu = false;
                currentState = menu;
            }
        }

        //IN STATS
        else if (currentState == stats) {
            if (statsState.backToMenu) {
                statsState.backToMenu = false;
                currentState = menu;
            }
        }

        // IN GAME
        else if (currentState == play) {

            gameState.handleInput();

            gameState.update(dt);

            if (gameState.getGame().getWantGameOver()) {
                gameState.stopMusic();
                currentState = gameover;
            }

            if (gameState.getIsPaused()) {
                currentState = pause;
            }
        }
        
		//IN PAUSE
        else if (currentState == pause) {
            gameState.draw();
            pauseState.handleInput();
            pauseState.update(dt);

            if (pauseState.resumeGame) {
                pauseState.resumeGame = false;
                gameState.setIsPaused(false);
                currentState = play;
            }
            else if (pauseState.restartGame) {
                pauseState.restartGame = false;
                gameState.setIsPaused(false);
                gameState.stopMusic();
                gameState.reloadMusic();
                gameState.getGame().isDeadReset();

                currentState = play;
                continue;
            }
            else if (pauseState.quitToMenu) {
                pauseState.quitToMenu = false;
                gameState.setIsPaused(false);
                gameState.stopMusic();
                menuState.getMusic().play();
                gameState.getGame().isDeadReset();

                currentState = menu;
                continue;
            }
        }

		//IN GAME OVER
        else if (currentState == gameover) {
            gameState.draw();
            gameOverState.handleInput();
            gameOverState.update(dt);
            gameState.update(dt);
            
            if (gameOverState.restartGame) {
                gameOverState.restartGame = false;
                statsState.updateData((gameState.getGame().getPlayerPosition().x - 1000) / 20, gameState.getGame().getPiecesNb(), gameState.getGame().getPlayer().getMaxSpeed()/10);
                gameState.reloadMusic();
                gameState.getGame().isDeadReset();
                
                currentState = play;
                gameOverState.scoreInitialized = false;
                continue;
            }
            else if (gameOverState.quitToMenu) {
                gameOverState.quitToMenu = false;
                statsState.updateData((gameState.getGame().getPlayerPosition().x - 1000)/20, gameState.getGame().getPiecesNb(), gameState.getGame().getPlayer().getMaxSpeed()/10);
                gameState.getGame().isDeadReset();
                gameState.stopMusic();

                menuState.getMusic().play();
                currentState = menu;
                gameOverState.scoreInitialized = false;
                continue;
            }
        }

        if (currentState == menu) {
            AudioSettings::applyTo(menuState.getMusic());
        }
        else if (currentState == play) {
            AudioSettings::applyTo(gameState.getMusic());
        }

        if (currentState != pause && currentState != gameover)
            window.clear();
        getState()->draw();
        window.display();
    }
}
