#pragma once
#include "state.h"
#include "view.h"
#include "ScoreManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class GameOverState : public state {
private:
    View view;

    sf::Font font;
    sf::RectangleShape overlay;
    std::optional<sf::Text> titleText;
    std::optional<sf::Text> scoreText;
    std::vector<sf::Text> options;

    int selectedItem = -1;

public:
    bool restartGame = false;
    bool quitToMenu = false;
    

    GameOverState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float deltaTime) override;
    void draw() override;
};
