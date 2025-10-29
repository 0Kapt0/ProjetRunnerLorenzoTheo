#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "state.h"
#include "menu.h"
#include "game_state.h"
#include "pause_state.h"
#include "options_state.h"
#include "game_over_state.h"
#include "stats_state.h"

class StateManager {
private:
    sf::RenderWindow& window;
    sf::Clock clock;

    OptionsState optionsState;
    GameState gameState;
    GameOverState gameOverState;
    PauseState pauseState;
    StatsState statsState;
    menu menuState;

    float timePaused = 0;
    /*bool isPaused = false;*/
public:
    enum State
    {
        menu,
        options,
        stats,
        play,
        gameover,
        pause
    };

    State currentState = menu;

    StateManager(sf::RenderWindow& win);

    state* getState();
    void run();
};
