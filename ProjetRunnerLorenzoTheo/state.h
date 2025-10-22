#pragma once
#include <SFML/Graphics.hpp>

class state {
protected:
	sf::RenderWindow& window;

public:
    state(sf::RenderWindow& window) : window(window) {}
    virtual ~state() {}
    virtual void handleInput() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;
};

