#pragma once
#include "state.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class StatsState : public state
{
private:
    sf::Font font;
    sf::Text back;
public:
	bool backToMenu = false;

    StatsState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float dt) override;
    void draw() override;
};

