#include "Background.h"

#include <iostream>

Background::Background(float width, float height, View& view)
    : m_width(width), m_height(height), m_gradient(sf::PrimitiveType::TriangleFan, 4), m_time(0.f)
{
    viewRef = &view;
}

void Background::update(float deltaTime)
{
    m_time += deltaTime;

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

    sf::Vector2f viewSize = viewRef->getView().getSize();
    sf::Vector2f viewPos = viewRef->getView().getCenter();

    int x1 = viewPos.x - (viewSize.x / 1.9f);
    int x2 = viewPos.x + (viewSize.x / 1.9f);
    int y1 = viewPos.y + (viewSize.y / 1.9f);
    int y2 = viewPos.y - (viewSize.y / 1.9f);

    m_gradient[0].position = sf::Vector2f(x1, y1);
    m_gradient[1].position = sf::Vector2f(x2, y1);
    m_gradient[2].position = sf::Vector2f(x2, y2);
    m_gradient[3].position = sf::Vector2f(x1, y2);
}

void Background::draw(sf::RenderTarget& target) const
{
    target.draw(m_gradient);
}
