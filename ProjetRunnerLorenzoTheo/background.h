#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "view.h"

class Background
{
public:
    Background(float width, float height, View& view);

    // Met à jour les couleurs du dégradé selon le temps
    void update(float deltaTime);

    // Dessine le background dans la fenêtre
    void draw(sf::RenderTarget& target) const;

private:
    float m_width;
    float m_height;
    sf::VertexArray m_gradient; // 4 vertices pour le dégradé

    float m_time; // compteur de temps pour animer le dégradé

    sf::Vector2f position;
    View* viewRef;
};
