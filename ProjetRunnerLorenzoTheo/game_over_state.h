#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "state.h"

class GameOverState : public State {
private:
    sf::Font font;
    sf::RectangleShape overlay;
    std::optional<sf::Text> titleText;
    std::vector<sf::Text> options;
    
    int selectedItem = -1;
    View view;

public:
    bool restartGame = false;
    bool quitToMenu = false;
    
    GameOverState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float deltaTime) override;
    void draw() override;
};
