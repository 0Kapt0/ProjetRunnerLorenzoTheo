#pragma once
#include <SFML/Graphics.hpp>

class Background
{
public:
    Background(float width, float height);

    // Met � jour les couleurs du d�grad� selon le temps
    void update(float deltaTime, sf::View view);

    // Dessine le background dans la fen�tre
    void draw(sf::RenderTarget& target) const;

private:
    float m_width;
    float m_height;
    sf::VertexArray m_gradient; // 4 vertices pour le d�grad�

    float m_time; // compteur de temps pour animer le d�grad�

    sf::Vector2f position;
};
