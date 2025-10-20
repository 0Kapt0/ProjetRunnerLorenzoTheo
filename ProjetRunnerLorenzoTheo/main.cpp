#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920u, 800u }), "Pentes SFML 3");

    sf::Clock clock;
    const float SPEED = 200.f;

    // --- Génération du terrain ---
    std::vector<sf::Vector2f> points;
    for (float x = 0; x <= 800; x += 10.f)
    {
        float y = 400.f + std::sin(x * 0.01f) * 80.f;
        points.push_back({ x, y });
    }

    // --- VertexArray du sol ---
    sf::VertexArray ground(sf::PrimitiveType::TriangleStrip);
    for (auto& p : points)
    {
        ground.append({ p, sf::Color::Green });
        ground.append({ {p.x, 800.f}, sf::Color::Green });
    }

    // --- Points rouges (visualisation sommets) ---
    std::vector<sf::CircleShape> redPoints;
    for (auto& p : points)
    {
        sf::CircleShape dot(3.f);
        dot.setFillColor(sf::Color::Red);
        dot.setOrigin({ 3.f, 3.f });
        dot.setPosition(p);
        redPoints.push_back(dot);
    }

    // --- Joueur ---
    sf::RectangleShape player({ 40.f, 20.f });
    player.setOrigin({ 20.f, 10.f });
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
        int idx = std::clamp(int(playerX / 10), 0, int(points.size()) - 2);
        sf::Vector2f p1 = points[idx];
        sf::Vector2f p2 = points[idx + 1];

        // Interpolation linéaire
        float t = (playerX - p1.x) / (p2.x - p1.x);
        float y = p1.y + (p2.y - p1.y) * t;
        player.setPosition({ playerX, y - 20.f });

        // --- Calcul orientation ---
        sf::Vector2f dir = p2 - p1;
        float angleDegrees = std::atan2(dir.y, dir.x) * 180.f / 3.14159f;
        player.setRotation(sf::degrees(angleDegrees)); // SFML 3: utilise sf::Angle

        // --- Affichage ---
        window.clear(sf::Color::Black);
        window.draw(ground);
        for (auto& dot : redPoints)
            window.draw(dot);
        window.draw(player);
        window.display();
    }
}
