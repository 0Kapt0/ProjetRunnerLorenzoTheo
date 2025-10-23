#include "Piece.h"

Piece::Piece(sf::Vector2f pos)
{
	position = pos;
	circle.setFillColor(sf::Color::Yellow);
	circle.setRadius(size);
}

void Piece::draw(sf::RenderWindow& window)
{
	window.draw(circle);
}