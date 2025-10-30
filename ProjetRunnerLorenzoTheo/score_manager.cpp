#include "score_manager.h"

int ScoreManager::lastScore = 0;
int ScoreManager::highestScore = 0;

ScoreManager::ScoreManager(const sf::Font& font, sf::Vector2f uiPos, const Config& cfg)
    : cfg(cfg),
    uiPos(uiPos),
    scoreText(font, "", 28),
    multText(font, "", 22)
{
    scoreText.setFillColor(sf::Color::White);
    multText.setFillColor(sf::Color(200, 230, 255));

    comboBarBG.setSize({ 200.f, 10.f });
    comboBarBG.setFillColor(sf::Color(0, 0, 0, 120));

    comboBarFill.setSize({ 200.f, 10.f });
    comboBarFill.setFillColor(sf::Color(0, 200, 255));

    boostBarBG.setSize({ 200.f, 15.f });
    boostBarBG.setFillColor(sf::Color(0, 0, 0, 150));
    boostBarBG.setOutlineThickness(1);
    boostBarBG.setOutlineColor(sf::Color::White);

    boostBarFill.setSize({ 200.f, 15.f });
    boostBarFill.setFillColor(sf::Color(255, 200, 0));

    background.setSize({ 310.f, 90.f });
    background.setFillColor(sf::Color(0, 0, 0, 150));
}

void ScoreManager::start(float startPlayerX)
{
    startX = lastX = startPlayerX;
    score = 0;
    airborne = false;
    spins = 0;
    airUnwrappedAngle = 0.f;
    currentMultiplier = 1;
    comboTimer = 0.f;

    updateTexts();
}

bool ScoreManager::detectBackflip(float playerAngleDeg)
{
    float delta = shortestAngleDelta(lastAngle, playerAngleDeg);
    airUnwrappedAngle += delta;
    lastAngle = playerAngleDeg;

    if (airUnwrappedAngle <= -310.f) {
        airUnwrappedAngle += 360.f;
        return true;
    }

    if (airUnwrappedAngle > 720.f || airUnwrappedAngle < -720.f)
        airUnwrappedAngle = 0.f;

    return false;
}

void ScoreManager::update(float dt, float playerX, float playerAngleDeg, bool isGrounded)
{
    float dx = playerX - lastX;
    lastX = playerX;

    if (!airborne && !isGrounded) {
        airborne = true;
        spins = 0;
        airUnwrappedAngle = 0.f;
        lastAngle = playerAngleDeg;
    }
    else if (airborne && isGrounded) {
        if (spins > 0) {
            score += cfg.landingTrickBaseBonus * spins * currentMultiplier;
        }
        airborne = false;
        spins = 0;
        airUnwrappedAngle = 0.f;
    }

    if (airborne) {
        bool didFlip = detectBackflip(playerAngleDeg);

        if (didFlip) {
            spins++;
            currentMultiplier = std::min(cfg.maxMultiplier, currentMultiplier + 1);
            comboTimer = cfg.comboDuration;

            boostCharge = std::min(maxBoost, boostCharge + boostGainPerFlip);
        }
    }

    if (comboTimer > 0.f) {
        comboTimer -= dt;
        if (comboTimer <= 0.f) {
            comboTimer = 0.f;
            currentMultiplier = 1;
        }
    }

    if (dx > 0.f) {
        score += dx * cfg.distancePointsPerPixel * currentMultiplier;
    }

    updateTexts();

    ScoreManager::lastScore = getScoreInt();
    if (ScoreManager::lastScore > ScoreManager::highestScore)
        ScoreManager::highestScore = ScoreManager::lastScore;
}

void ScoreManager::draw(sf::RenderTarget& target, const sf::View& view, const sf::Vector2f& playerPos)
{
    sf::View oldView = target.getView();
    target.setView(view);

    sf::Vector2f topLeft = view.getCenter() - view.getSize() / 2.f;
    sf::Vector2f basePos = topLeft + sf::Vector2f(30.f, 30.f);

    sf::Text score = scoreText;
    sf::Text mult = multText;

    score.setPosition(basePos);
    mult.setPosition(basePos + sf::Vector2f(0.f, 35.f));

    sf::RectangleShape barBG = comboBarBG;
    sf::RectangleShape barFill = comboBarFill;


    float ratio = comboTimer / cfg.comboDuration;
    barBG.setPosition(basePos + sf::Vector2f(0.f, 65.f));
    barFill.setSize({ 200.f * ratio, 10.f });
    barFill.setPosition(basePos + sf::Vector2f(0.f, 65.f));

    sf::Vector2f topRight = view.getCenter() + view.getSize() / 2.f;
    sf::Vector2f barSize = { 200.f, 15.f };
    sf::Vector2f barPos = topRight - sf::Vector2f(barSize.x + 30.f, view.getSize().y - 30.f);

    sf::RectangleShape bg = boostBarBG;
    sf::RectangleShape fill = boostBarFill;

    background.setPosition(basePos - sf::Vector2f(10.f, 10.f));
    target.draw(background);

    float boostRatio = boostCharge / maxBoost;
    bg.setPosition(barPos);
    fill.setPosition(barPos);
    fill.setSize({ barSize.x * boostRatio, barSize.y });

    target.draw(bg);
    target.draw(fill);

    target.draw(score);
    target.draw(mult);
    if (currentMultiplier > 1) {
        target.draw(barBG);
        target.draw(barFill);
    }

    {
        sf::Vector2f center = playerPos;
        const float radius = 60.f; 
        const int points = 50;
        const float arcAngle = 120.f;
        const float startAngle = -arcAngle / 2.f;
        const float ratio = boostCharge / maxBoost; 
        const float visibleAngle = arcAngle * ratio;

        sf::VertexArray arc(sf::PrimitiveType::TriangleStrip);

        const float baseRotation = -70.f;
        const sf::Vector2f offset(0.f, 0.f);

        for (int i = 0; i <= points; ++i)
        {
            float t = static_cast<float>(i) / points;
            float angle = startAngle + t * visibleAngle + baseRotation;;
            float rad = angle * 3.14159265f / 180.f;

            sf::Vector2f outer(
                center.x + std::cos(rad) * radius + offset.x,
                center.y + std::sin(rad) * radius + offset.y
            );

            sf::Vector2f inner(
                center.x + std::cos(rad) * (radius - 6.f) + offset.x,
                center.y + std::sin(rad) * (radius - 6.f) + offset.y
            );

            sf::Color c = sf::Color(
                static_cast<uint8_t>(100 + 155 * ratio),
                200,
                255,
                200
            );

            arc.append(sf::Vertex(outer, c));
            arc.append(sf::Vertex(inner, c));
        }
        target.draw(arc);
    }
    target.setView(oldView);
}

void ScoreManager::addScore(float addscore) {
    score += addscore * currentMultiplier;
}

int ScoreManager::getScoreInt() const { return static_cast<int>(score + 0.5f); }
float ScoreManager::getScore() const { return score; }
int ScoreManager::getCurrentMultiplier() const { return currentMultiplier; }
int ScoreManager::getSpinCount() const { return spins; }

float ScoreManager::shortestAngleDelta(float a, float b)
{
    float d = std::fmod(b - a, 360.f);
    if (d > 180.f)  d -= 360.f;
    if (d < -180.f) d += 360.f;
    return d;
}

void ScoreManager::updateTexts()
{
    scoreText.setString("Score  " + std::to_string(int(ScoreManager::score)));
    multText.setString("x" + std::to_string(currentMultiplier));
}