#include "Background.h"
#include <cmath>

Background::Background(float width, float height)
    : m_width(width), m_height(height), m_gradient(sf::PrimitiveType::TriangleFan, 4), m_time(0.f)
{
    // Initialisation des positions
    m_gradient[0].position = { 0.f, 0.f };
    m_gradient[1].position = { m_width, 0.f };
    m_gradient[2].position = { m_width, m_height };
    m_gradient[3].position = { 0.f, m_height };
}

void Background::update(float deltaTime, sf::View view)
{
    m_time += deltaTime;


    // Couleurs du haut et du bas qui varient avec le temps
    sf::Color topColor(
        ((std::sin(m_time * 0.3f) * 0.5f + 0.5f) * 255),
        ((std::sin(m_time * 0.2f) * 0.5f + 0.5f) * 255),
        ((std::sin(m_time * 0.4f) * 0.5f + 0.5f) * 255)
    );

    sf::Color bottomColor(
        ((std::cos(m_time * 0.3f) * 0.5f + 0.5f) * 255),
        ((std::cos(m_time * 0.2f) * 0.5f + 0.5f) * 255),
        ((std::cos(m_time * 0.4f) * 0.5f + 0.5f) * 255)
    );

    m_gradient[0].color = topColor;
    m_gradient[1].color = topColor;
    m_gradient[2].color = bottomColor;
    m_gradient[3].color = bottomColor;

    int x1 = view.getCenter().x - (view.getSize().x / 2.f);
    int x2 = view.getCenter().x + (view.getSize().x / 2.f);
    int y1 = view.getCenter().y - (view.getSize().y / 2.f);
    int y2 = view.getCenter().y + (view.getSize().y / 2.f);

    // Top-left
    m_gradient[0].position = sf::Vector2f(x1, y1);
    // Top-right
    m_gradient[1].position = sf::Vector2f(x2, y1);
    // Bottom-left
    m_gradient[2].position = sf::Vector2f(x1, y2);
    // Bottom-right
    m_gradient[3].position = sf::Vector2f(x2, y2);

}

void Background::draw(sf::RenderTarget& target) const
{
    target.draw(m_gradient);
}
