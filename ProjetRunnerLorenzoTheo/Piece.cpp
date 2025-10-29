#include "piece.h"

Piece::Piece(sf::Vector2f pos)
{
	position = pos;
	circle.setFillColor(sf::Color::Yellow);
	circle.setRadius(size);
	circle.setPosition(position);
	circle.setOrigin({size, size});
}

void Piece::draw(sf::RenderWindow& window)
{
    sf::CircleShape outer(size);
    outer.setOrigin({ size, size });
    outer.setPosition(position);
    outer.setFillColor(sf::Color(255, 215, 0));
    outer.setOutlineThickness(-4.f);
    outer.setOutlineColor(sf::Color(180, 120, 0));
    window.draw(outer);

    sf::CircleShape inner(size * 0.6f);
    inner.setOrigin({ inner.getRadius(), inner.getRadius() });
    inner.setPosition(position - sf::Vector2f(0, size * 0.15f));
    inner.setFillColor(sf::Color(255, 240, 120, 180));
    window.draw(inner);
}