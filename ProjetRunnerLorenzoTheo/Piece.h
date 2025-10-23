#pragma once
#include "bonus.h"

class Piece :
    public Bonus
{
private:
    sf::CircleShape circle;
    float size = 20;

public:
    Piece(sf::Vector2f pos);
    
    void draw(sf::RenderWindow& window);
};

