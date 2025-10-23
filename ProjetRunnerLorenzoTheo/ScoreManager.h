#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

class ScoreManager {
public:
    struct Config {
        float distancePointsPerPixel = 0.10f;
        int   landingTrickBaseBonus = 100;
        int   maxMultiplier = 10;
        float comboDuration = 5.f;
    };

    ScoreManager(const sf::Font& font, sf::Vector2f uiPos, const Config& cfg = {});

    void start(float startPlayerX);
    void update(float dt, float playerX, float playerAngleDeg, bool isGrounded);
    void draw(sf::RenderTarget& target, const sf::View& view) const;

    int   getScoreInt() const;
    float getScore() const;
    int   getCurrentMultiplier() const;
    int   getSpinCount() const;

private:
    Config cfg;
    sf::Vector2f uiPos;

    sf::Text scoreText;
    sf::Text multText;
    sf::RectangleShape comboBarBG;
    sf::RectangleShape comboBarFill;

    float startX = 0.f;
    float lastX = 0.f;

    bool  airborne = false;
    int   spins = 0;
    int   currentMultiplier = 1;

    float score = 0.f;
    float lastAngle = 0.f;
    float airUnwrappedAngle = 0.f;

    float comboTimer = 0.f;

    static float shortestAngleDelta(float a, float b);
    bool detectBackflip(float playerAngleDeg);
    void updateTexts();
};
