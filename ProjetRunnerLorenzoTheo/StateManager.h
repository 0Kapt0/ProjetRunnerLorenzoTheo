#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "state.h"
#include "menu.h"
#include "game_state.h"
#include "pause_state.h"
#include "options_state.h"
#include "game_over_state.h"

class StateManager {
private:
    sf::RenderWindow& window;
    sf::Clock clock;

    std::unique_ptr<state> currentState;
    std::unique_ptr<PauseState> pauseMenu;
    std::unique_ptr<GameOverState> gameOverMenu;

    float timePaused = 0;
    bool isPaused;
public:
    StateManager(sf::RenderWindow& win);

    template<typename T, typename... Args>
    void changeState(Args&&... args) {
        currentState = std::make_unique<T>(window, std::forward<Args>(args)...);
    }

    state* getState();
    void run();
};
