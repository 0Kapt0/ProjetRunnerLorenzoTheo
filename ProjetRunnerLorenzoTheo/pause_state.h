#pragma once
#include "state.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PauseState : public state {
private:
    std::vector<sf::Text> options;
    sf::Font font;
    sf::RectangleShape overlay;
    int selectedItem = -1;

public:
    bool resumeGame = false;
    bool quitToMenu = false;

    PauseState(sf::RenderWindow& window, const sf::Vector2f& playerPos);
    void handleInput() override;
    void update(float deltaTime) override;
    void draw() override;
};
