#pragma once
#include "state.h"
#include "view.h"
#include <SFML/Graphics.hpp>
#include <vector>

class GameOverState : public state {
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
