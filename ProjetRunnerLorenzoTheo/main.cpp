#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "bloc_niveau.h"
#include "state.h"
#include "menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720}), "Runner test");
    sf::Clock clock;

    menu mainMenu(window);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();

        mainMenu.handleInput();
        mainMenu.update(dt);

        window.clear(sf::Color::Black);
        mainMenu.draw();
        window.display();
    }
}
