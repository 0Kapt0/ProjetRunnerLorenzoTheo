#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "bloc_niveau.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720}), "Runner test");
    sf::Clock clock;

    BlocNiveau b1(sf::Vector2f(0, 400), 0);
    BlocNiveau b2(b1.getEndPosition(), 0);

    std::cout << b1.getEndPosition().x << ", " << b1.getEndPosition().y << "\n";
    

    Player player({ 0.f, 300.f });

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();

        player.update(dt, pente);

        window.clear(sf::Color::Black);
        b1.draw(window);
        b2.draw(window);
        player.draw(window);
        window.display();
    }
}
