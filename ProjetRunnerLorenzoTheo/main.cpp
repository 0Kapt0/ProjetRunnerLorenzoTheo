#include <SFML/Graphics.hpp>
#include "player.h"
#include "pente.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720}), "Runner test");
    sf::Clock clock;

    Pente pente(800, 0.f, 10, sf::degrees(0), sf::degrees(20), 500, 600, 0);

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
        pente.draw(window);
        player.draw(window);
        window.display();
    }
}
