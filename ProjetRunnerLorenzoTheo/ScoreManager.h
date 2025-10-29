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
    void draw(sf::RenderTarget& target, const sf::View& view, const sf::Vector2f& playerPos);

    int   getScoreInt() const;
    float getScore() const;
    int   getCurrentMultiplier() const;
    int   getSpinCount() const;

    static int lastScore;
    static int highestScore;

    void addScore(float addscore);

    float getBoostCharge() const { return boostCharge; }
    void  setBoostCharge(float value) { boostCharge = std::clamp(value, 0.f, maxBoost); }

private:
    Config cfg;
    sf::Vector2f uiPos;

    sf::Text scoreText;
    sf::Text multText;
    sf::RectangleShape comboBarBG;
    sf::RectangleShape comboBarFill;
    sf::RectangleShape background;

    float startX = 0.f;
    float lastX = 0.f;

    bool  airborne = false;
    int   spins = 0;
    int   currentMultiplier = 1;

    float score = 0.f;
    float lastAngle = 0.f;
    float airUnwrappedAngle = 0.f;

    float comboTimer = 0.f;

    float boostCharge = 0.f;
    float boostGainPerFlip = 25.f;
    float maxBoost = 100.f;

    sf::RectangleShape boostBarBG;
    sf::RectangleShape boostBarFill;

    static float shortestAngleDelta(float a, float b);
    bool detectBackflip(float playerAngleDeg);
    void updateTexts();
};
