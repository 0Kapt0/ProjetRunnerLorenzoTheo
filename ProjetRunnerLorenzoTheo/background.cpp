#include "Background.h"
#include <random>
#include <iostream>

Background::Background(float width, float height, View& view)
    : m_width(width), m_height(height),
    m_gradient(sf::PrimitiveType::TriangleFan, 4),
    m_time(0.f), viewRef(&view)
{
    generateMountains();

    //Lune
    moon.setRadius(110.f);
    moon.setOrigin({ 60.f, 60.f });
    moon.setFillColor(sf::Color(240, 240, 255));
    moon.setPosition({ m_width - 250.f, 180.f });

    //Halo lumineux autour
    moonGlow = sf::VertexArray(sf::PrimitiveType::TriangleFan);
    const int glowPoints = 40;
    float glowRadius = 140.f;

    moonGlow.append({ moon.getPosition(), sf::Color(255, 255, 255, 70) });

    for (int i = 0; i <= glowPoints; ++i)
    {
        float angle = i * 2 * 3.14159f / glowPoints;
        float r = glowRadius + std::sin(angle * 3.f) * 15.f;
        sf::Vector2f pos = moon.getPosition() + sf::Vector2f(std::cos(angle), std::sin(angle)) * r;
        moonGlow.append({ pos, sf::Color(255, 255, 255, 0) });
    }
}

void Background::generateMountains()
{
    std::mt19937 rng(42);
    std::uniform_real_distribution<float> offsetY(250.f, 500.f);
    std::uniform_real_distribution<float> peakWidth(400.f, 750.f);

    const int layerCount = 4;
    m_layers.clear();

    for (int i = 0; i < layerCount; ++i)
    {
        MountainLayer layer;
        layer.triangles = sf::VertexArray(sf::PrimitiveType::Triangles);
        layer.parallaxFactor = 1.0f - (i * 0.2f);
        layer.opacity = static_cast<float>(255 * (1.f - i * 0.18f));

        float baseY = m_height * (0.5f + i * 0.08f);

        float x = -m_width * 0.7f;
        while (x < m_width * 1.7f)
        {
            float w = peakWidth(rng) * (1.1f + i * 0.2f);
            float h = offsetY(rng) * (1.1f + i * 0.3f);
            float xMid = x + w * 0.5f;

            sf::Color color(
                static_cast<uint8_t>(50 + i * 40),
                static_cast<uint8_t>(60 + i * 35),
                static_cast<uint8_t>(90 + i * 30),
                static_cast<uint8_t>(layer.opacity)
            );

            layer.triangles.append(sf::Vertex(sf::Vector2f{ x, baseY }, color));
            layer.triangles.append(sf::Vertex(sf::Vector2f{ x + w, baseY }, color));
            layer.triangles.append(sf::Vertex(sf::Vector2f{ xMid, baseY - h }, color));

            x += w * 0.6f;
        }

        m_layers.push_back(layer);
        layerOffsets.push_back(0.f);
    }
}

void Background::update(float deltaTime, float playerVel)
{

    float speed = std::max(50.f, std::abs(playerVel));
    float speedFactor = std::clamp(speed / 800.f, 0.5f, 4.f);


    m_time += deltaTime * speedFactor * 0.25f;

    auto hsvToRgb = [](float h, float s, float v)
        {
            float c = v * s;
            float x = c * (1 - std::fabs(std::fmod(h / 60.f, 2.f) - 1));
            float m = v - c;
            float r, g, b;
            if (h < 60) { r = c; g = x; b = 0; }
            else if (h < 120) { r = x; g = c; b = 0; }
            else if (h < 180) { r = 0; g = c; b = x; }
            else if (h < 240) { r = 0; g = x; b = c; }
            else if (h < 300) { r = x; g = 0; b = c; }
            else { r = c; g = 0; b = x; }
            return sf::Color(
                static_cast<uint8_t>((r + m) * 255),
                static_cast<uint8_t>((g + m) * 255),
                static_cast<uint8_t>((b + m) * 255)
            );
        };

    float hueTop = std::fmod(m_time * 120.f, 360.f);
    float hueBottom = std::fmod(m_time * 120.f + 180.f, 360.f);
    float saturation = 0.9f;
    float brightnessTop = 0.95f;
    float brightnessBottom = 0.75f;

    sf::Color topColor = hsvToRgb(hueTop, saturation, brightnessTop);
    sf::Color bottomColor = hsvToRgb(hueBottom, saturation, brightnessBottom);

    m_gradient[0].color = topColor;
    m_gradient[1].color = topColor;
    m_gradient[2].color = bottomColor;
    m_gradient[3].color = bottomColor;

    m_gradient[0].position = { 0.f, m_height };
    m_gradient[1].position = { m_width, m_height };
    m_gradient[2].position = { m_width, 0.f };
    m_gradient[3].position = { 0.f, 0.f };

    for (std::size_t i = 0; i < m_layers.size(); ++i)
    {
        auto& layer = m_layers[i];

        layerOffsets[i] += speed * 0.02f * layer.parallaxFactor * deltaTime;

        if (layerOffsets[i] > m_width)
            layerOffsets[i] -= m_width;
    }


    uint8_t glowAlpha = static_cast<uint8_t>(70 + 30 * std::sin(m_time * 2.f));
    moonGlow[0].color.a = glowAlpha;
}
void Background::draw(sf::RenderTarget& target) const {

    sf::View oldView = target.getView();
    target.setView(target.getDefaultView());
    target.draw(m_gradient);
    target.draw(moon);
    target.draw(moonGlow);

    for (int i = static_cast<int>(m_layers.size()) - 1; i >= 0; --i)
    {
        const auto& layer = m_layers[i];
        sf::RenderStates states;

        float baseYOffset = m_height * (0.55f + i * 0.08f) - 800;

        float scrollX = layerOffsets[i];
        states.transform.translate(sf::Vector2f{ -scrollX, baseYOffset });

        states.transform.scale({ 2.5f, 2.5f });

        target.draw(layer.triangles, states);
    }
    target.setView(oldView);
}
