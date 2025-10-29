#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include "view.h"
#include "pente.h"

class Background
{
public:
    Background(float width, float height, View& view);

    void update(float deltaTime, float playerVel);
    void draw(sf::RenderTarget& target) const;

private:
    struct MountainLayer {
        sf::VertexArray triangles;
        float parallaxFactor = 0;
        float opacity = 1;
    };

    sf::CircleShape moon;
    sf::VertexArray moonGlow;

    float m_width;
    float m_height;
    sf::VertexArray m_gradient;
    float m_time;
    View* viewRef;

    std::vector<MountainLayer> m_layers;
    std::vector<float> layerOffsets;

    void generateMountains();
};
