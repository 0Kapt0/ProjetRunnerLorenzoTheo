#include "pente.h"

Pente::Pente(unsigned int length, float amplitude, unsigned int p, std::string slopeType)
{
	precision = p;

	ground.setPrimitiveType(sf::PrimitiveType::TriangleStrip);

    for (float x = 0; x <= length; x += precision)
    {
        float y = 0;
        if (slopeType == "upward")
        {
            y = 400.f - x * amplitude;
        }
        if (slopeType == "downward")
        {
            y = 400.f + x * amplitude;
        }
        points.push_back({ x, y });
    }

    for (auto& p : points)
    {
        ground.append({ p, sf::Color::Color(200, 255, 200)});
        ground.append({ {p.x, 800.f}, sf::Color::Color(255, 255, 255)});
    }
};

int Pente::getSurfaceHeight(int x)
{
    int idx = std::clamp(int(x / precision), 0, int(points.size()) - 2);
    sf::Vector2f p1 = points[idx];
    sf::Vector2f p2 = points[idx + 1];

    float t = (x - p1.x) / (p2.x - p1.x);
    
    return p1.y + (p2.y - p1.y) * t;
}

sf::Angle Pente::getOrientation(int x)
{
    int idx = std::clamp(int(x / 10), 0, int(points.size()) - 2);
    sf::Vector2f p1 = points[idx];
    sf::Vector2f p2 = points[idx + 1];

    sf::Vector2f dir = p2 - p1;
    return sf::Angle(sf::radians(std::atan2(dir.y, dir.x)));
}

void Pente::draw(sf::RenderWindow& window)
{
    window.draw(ground);
}