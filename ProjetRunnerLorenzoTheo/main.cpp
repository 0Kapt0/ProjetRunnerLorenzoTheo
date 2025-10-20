#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

#include "pente.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920u, 800u }), "Pentes SFML 3");

    sf::Clock clock;
    const float SPEED = 200.f;

    Pente pente(1000, 1, 10, sf::degrees(90), sf::degrees(0), 400, 200, 0);
    Pente pente2(500, 0, 150, sf::degrees(0), sf::degrees(90), 200, 600, 1000);
    

    // --- Joueur ---
    sf::CircleShape player(3.f);
    /*player.setOrigin({ 20.f, 10.f });*/
    player.setFillColor(sf::Color::Cyan);

    float playerX = 0.f;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        float delta = dt.asSeconds();

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // --- Déplacement gauche/droite ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            playerX += SPEED * delta;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            playerX -= SPEED * delta;

        playerX = std::clamp(playerX, 0.f, 800.f);

        // --- Trouver position sur la courbe ---

        player.setPosition({ playerX, float(pente.getSurfaceHeight(playerX)) });

        // --- Calcul orientation ---
        player.setRotation(pente.getOrientation(playerX));

        // --- Affichage ---
        window.clear(sf::Color::Black);
        pente.draw(window);
        pente2.draw(window);
        window.draw(player);
        window.display();
    }
}
