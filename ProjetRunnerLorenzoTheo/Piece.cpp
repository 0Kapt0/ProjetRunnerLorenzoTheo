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
	window.draw(circle);
}