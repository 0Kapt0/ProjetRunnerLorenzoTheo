#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "bloc_niveau.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920u, 800u }), "Pentes SFML 3");

    sf::Clock clock;
    const float SPEED = 200.f;

    BlocNiveau b1(sf::Vector2f(0, 400), 0);
    BlocNiveau b2(b1.getEndPosition(), 0);

    std::cout << b1.getEndPosition().x << ", " << b1.getEndPosition().y << "\n";
    

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

        //player.setPosition({ playerX, float(pente.getSurfaceHeight(playerX)) });

        // --- Calcul orientation ---
        //player.setRotation(pente.getOrientation(playerX));

        // --- Affichage ---
        window.clear(sf::Color::Black);
        b1.draw(window);
        b2.draw(window);
        window.draw(player);
        window.display();
    }
}
