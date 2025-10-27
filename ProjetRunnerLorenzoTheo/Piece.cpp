#include "piece.h"

Piece::Piece(sf::Vector2f pos)
{
	position = pos;
	circle.setFillColor(sf::Color::Yellow);
	circle.setRadius(size);
	circle.setPosition(position);
}

void Piece::draw(sf::RenderWindow& window)
{
	window.draw(circle);
}