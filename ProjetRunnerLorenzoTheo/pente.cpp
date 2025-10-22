#include "pente.h"

Pente::Pente(unsigned int lengthVal, float amplitudeVal, unsigned int precisionVal, sf::Angle angleDepart, sf::Angle angleArrivee, int startHeight, int endHeightVal, int positionXVal)
{
	precision = precisionVal;
    length = lengthVal;
    endHeight = endHeightVal;
    positionX = positionXVal;

    ground.setPrimitiveType(sf::PrimitiveType::TriangleStrip);

    for (float x = 0; x <= lengthVal; x += precision)
    {
        float y = startHeight; // ligne de base du sol

        // Points de contrôle codés en dur
        sf::Vector2f P0(0.f, startHeight);
        sf::Vector2f P3(lengthVal, endHeightVal);

        float tangentLength = lengthVal * 0.25f;

        // P1 basé sur l'angle de départ
        sf::Vector2f P1 = P0 + sf::Vector2f(
            tangentLength * std::cos(angleDepart.asRadians()),
            tangentLength * std::sin(angleDepart.asRadians())
        );

        // P2 basé sur l'angle d'arrivée
        sf::Vector2f P2 = P3 - sf::Vector2f(
            tangentLength * std::cos(angleArrivee.asRadians()),
            tangentLength * std::sin(angleArrivee.asRadians())
        );

        float tLow = 0.0f, tHigh = 1.0f, tMid;

        while (tHigh - tLow > 0.0001f) {
            tMid = (tLow + tHigh) / 2.0f;

            float u = 1 - tMid;
            float tt = tMid * tMid;
            float uu = u * u;
            float uuu = uu * u;
            float ttt = tt * tMid;

            float xMid = uuu * P0.x + 3 * uu * tMid * P1.x + 3 * u * tt * P2.x + ttt * P3.x;
            float yMid = uuu * P0.y + 3 * uu * tMid * P1.y + 3 * u * tt * P2.y + ttt * P3.y;

            if (xMid < x)
                tLow = tMid;
            else
                tHigh = tMid;

            if (std::abs(xMid - x) < 0.0001f)
                y = yMid;
        }

        tMid = (tLow + tHigh) / 2.0f;
        float u = 1 - tMid;
        float tt = tMid * tMid;
        float uu = u * u;
        float uuu = uu * u;
        float ttt = tt * tMid;
        y = uuu * P0.y + 3 * uu * tMid * P1.y + 3 * u * tt * P2.y + ttt * P3.y;

        points.push_back({ x, y });
    }

    for (auto& p : points)
    {
        ground.append({ {p.x + positionXVal, p.y}, sf::Color::Color(200, 255, 200) });
        ground.append({ {p.x + positionXVal, 800.f+endHeightVal}, sf::Color::Color(255, 255, 255)});
    }
};

int Pente::getSurfaceHeight(int x)
{
    float localX = x - positionX;
    localX = std::clamp(localX, 0.f, float(length - precision));

    int idx = std::clamp(int(localX / precision), 0, int(points.size()) - 2);
    sf::Vector2f p1 = points[idx];
    sf::Vector2f p2 = points[idx + 1];

    float t = (localX - p1.x) / (p2.x - p1.x);
    return p1.y + (p2.y - p1.y) * t;
}

int Pente::getLength()
{
    return length;
}

int Pente::getEndHeight()
{
    return endHeight;
}

sf::Vector2f Pente::getEndPosition()
{
    return sf::Vector2f(positionX + length, endHeight);
}

sf::Angle Pente::getOrientation(int x)
{
    float localX = x - positionX;
    localX = std::clamp(localX, 0.f, float(length - precision));

    int idx = std::clamp(int(localX / precision), 0, int(points.size()) - 2);
    sf::Vector2f p1 = points[idx];
    sf::Vector2f p2 = points[idx + 1];

    sf::Vector2f dir = p2 - p1;
    return sf::Angle(sf::radians(std::atan2(dir.y, dir.x)));
}

void Pente::draw(sf::RenderWindow& window)
{
    window.draw(ground);
}