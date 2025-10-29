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
#include "score_Manager.h"
#include "audio_settings.h"

class StateManager {
private:
    sf::RenderWindow& window;
    sf::Clock clock;

    OptionsState optionsState;
    GameState gameState;
    GameOverState gameOverState;
    PauseState pauseState;
    StatsState statsState;
    Menu menuState;

    float timePaused = 0;

public:
    enum States
    {
        menu,
        options,
        stats,
        play,
        gameover,
        pause
    };

    States currentState = menu;

    StateManager(sf::RenderWindow& win);

    State* getState();
    void run();
};