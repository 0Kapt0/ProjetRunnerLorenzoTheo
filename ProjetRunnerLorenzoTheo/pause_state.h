#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "state.h"
#include "view.h"

class PauseState : public State {
private:
    std::vector<sf::Text> options;
    sf::Font font;
    sf::RectangleShape overlay;
    int selectedItem = -1;
    View view;

public:
    bool resumeGame = false;
    bool restartGame = false;
    bool quitToMenu = false;

    PauseState(sf::RenderWindow& window);
    void handleInput() override;
    void update(float deltaTime) override;
    void draw() override;
};