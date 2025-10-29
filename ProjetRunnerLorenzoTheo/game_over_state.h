#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "view.h"
#include "state.h"
#include "ScoreManager.h"

class GameOverState : public State {
private:
    View view;

    sf::Font font;
    sf::RectangleShape overlay;
    std::optional<sf::Text> titleText;
    std::optional<sf::Text> scoreText;
    std::optional<sf::Text> bestScoreText;
    std::vector<sf::Text> options;
    
    int selectedItem = -1;

public:
    bool restartGame = false;
    bool quitToMenu = false;
    bool scoreInitialized = false;
    
    GameOverState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float deltaTime) override;
    void draw() override;
};
