#include <cstdint>
#include "player.h"
#include <cmath>

Player::Player(sf::Vector2f startPos, float pspeed)
    : position(startPos),
    moveSpeed(pspeed),
    jumpForce(400.f),
    gravity(1400.f),
    isJumping(false),
    isGrounded(false),
    isDead(false),
    isCharging(false),
    chargeTime(0.f),
    maxChargeTime(0.4f),
    hasBoost(true),
    coyoteTimer(0.f),
    maxCoyoteTime(0.12f)
{
    particleSpawnTimer = 0.f;

    rgbTimer = 0.f;

    const float size = 40.f;

    body = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 4);
    
    body[0].position = { -size / 2.f, -size / 2.f };
    body[1].position = { -size / 2.f,  size / 2.f };
    body[2].position = { size / 2.f, -size / 2.f };
    body[3].position = { size / 2.f,  size / 2.f };

    const sf::Color topColor(180, 255, 255);
    const sf::Color bottomColor(255, 120, 120);

    body[0].color = topColor;
    body[1].color = bottomColor;
    body[2].color = topColor;
    body[3].color = bottomColor;

    bottomEdge = sf::VertexArray(sf::PrimitiveType::Lines, 2);

    bottomEdge[0].position = { -size / 2.f,  size / 2.f };
    bottomEdge[1].position = { size / 2.f,  size / 2.f };

    const sf::Color edgeColor(255, 80, 80, 220);
    bottomEdge[0].color = edgeColor;
    bottomEdge[1].color = edgeColor;
}

void Player::moveForward(float dt, Pente* pente)
{
    const float accel = 300.f;
    const float decel = 400.f;
    const float maxSpeed = 10000.f;
    const float minSpeed = 100.f;

    // ---- Récupérer l’angle de la pente ----
    float slopeAngle = pente->getOrientation(static_cast<int>(position.x)).asDegrees();

    // On limite un peu pour éviter des extrêmes
    slopeAngle = std::clamp(slopeAngle, -45.f, 45.f);

    // ---- Influence de la pente ----
    // Descente (angle positif) → accélère
    // Montée (angle négatif) → ralentit
    float slopeFactor = std::sin(slopeAngle * 3.14159f / 180.f);
    float slopeInfluence = slopeFactor * 600.f; // force de l’effet (à ajuster)

    // ---- Boost manuel (si le joueur charge) ----
    float baseDelta = (isCharging && hasBoost) ? accel : -decel;

    // ---- Calcul final ----
    float delta = baseDelta + slopeInfluence;

    if (!isGrounded)
    {
        // Moins de frottement dans l’air
        delta *= 0.3f; // 30% de la décélération au sol
    }

    moveSpeed = std::clamp(moveSpeed + delta * dt, minSpeed, maxSpeed);

    velocity.x = moveSpeed;
    position.x += velocity.x * dt;
}


void Player::applyGravity(float dt)
{
    if (!isGrounded)
        velocity.y += gravity * dt;

    position += velocity * dt;
}

void Player::handleInput(float dt)
{
    const bool canJump = (isGrounded || coyoteTimer > 0.f);
    const bool jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    //CHARGE DU SAUT
    if (jumpPressed && canJump)
    {
        isCharging = true;
        chargeTime = std::min(chargeTime + dt, maxChargeTime);

        if (hasBoost) {
            rgbTimer += 2.f * dt;
        }

        return;
    }

    //RELACHEMENT DU SAUT
    if (isCharging && canJump)
    {
        const float ratio = chargeTime / maxChargeTime;
        const float jumpStrength = 300.f + (750.f - 300.f) * (ratio * ratio);

        velocity.y = -jumpStrength;
        isGrounded = false;
        isJumping = true;
        coyoteTimer = 0.f;
        isCharging = false;
        chargeTime = 0.f;

        //Effet visuel
        createJumpPoof();
    }
    else
    {
        isCharging = false;
        chargeTime = 0.f;
    }

    //ROTATION EN L’AIR
    if (!isGrounded && jumpPressed)
    {
        shape.rotate(sf::degrees(-300.f * dt));
    }
}


void Player::checkGroundCollision(Pente* pente)
{
    const int x = static_cast<int>(position.x);
    const float surfaceY = static_cast<float>(pente->getSurfaceHeight(x) - 20.f);
    const float groundAngle = pente->getOrientation(x).asDegrees();
    constexpr float tolerance = 8.f;
    constexpr float crashAngle = 35.f;

    //collision sol
    if (velocity.y >= 0.f && position.y >= surfaceY - tolerance)
    {
        position.y = surfaceY;
        velocity.y = 0.f;
        isGrounded = true;
        isJumping = false;

        float playerAngle = shape.getRotation().asDegrees();
        playerAngle = std::fmod(playerAngle, 360.f);
        if (playerAngle < 0.f)
            playerAngle += 360.f;

        float diff = std::fabs(playerAngle - groundAngle);
        if (diff > 180.f)
            diff = 360.f - diff;

		//verif si l'angle d'atterrissage est bon
        if (diff > crashAngle)
        {
            isDead = true;
            isGrounded = false;
            explodeOnDeath();
            return;
        }

		//si atterissage reussi
        shape.setRotation(sf::degrees(groundAngle));
        shape.setFillColor(sf::Color::Cyan);
    }
    else
    {
        isGrounded = false;
    }
}

void Player::applyFlipBoost() {
    speedBoostActive = true;
    speedBoostTimer = speedBoostDuration;
}

void Player::updateCoyoteTimer(float dt)
{
    if (isGrounded)
        coyoteTimer = maxCoyoteTime;
    else
        coyoteTimer = std::max(0.f, coyoteTimer - dt);
}

void Player::createJumpPoof() {
    for (int i = 0; i < 25; ++i)
    {
        Particle p;
        p.pos = { position.x, position.y + 10.f };

        float angle = (rand() % 180 - 90) * 3.14159f / 180.f;
        float speed = (250.f + static_cast<float>(rand() % 150)) * 0.5f;
        p.vel = { std::cos(angle) * speed, std::sin(angle) * speed * 0.5f };
        p.lifetime = 1.0f + static_cast<float>(rand() % 40) / 100.f;

        particles.push_back(p);
    }
}

void Player::spawnParticles(float dt)
{
    const bool onGround = isCharging && isGrounded && hasBoost;
    const bool inAir = !isGrounded && isJumping && velocity.y < 0.f;
    if (!onGround && !inAir)
        return;

    particleSpawnTimer -= dt;

    const float baseRate = onGround ? 0.02f : 0.05f;
    const float spawnRate = baseRate * (1.f - (chargeTime / maxChargeTime));

    if (particleSpawnTimer > 0.f)
        return;

    particleSpawnTimer = spawnRate;

    Particle p;
    p.pos = { position.x - 10.f, position.y + 10.f };
    p.lifetime = 0.4f + static_cast<float>(rand() % 20) / 100.f;

    if (inAir)
        p.vel = { -70.f + static_cast<float>(rand() % 40),
                  -100.f + static_cast<float>(rand() % 50) };
    else
        p.vel = { -50.f + static_cast<float>(rand() % 30),
                  -30.f + static_cast<float>(rand() % 20) };

    particles.push_back(p);
}

void Player::explodeOnDeath()
{
    const int particleCount = 80;

    for (int i = 0; i < particleCount; ++i)
    {
        Particle p;
        p.pos = position;

        float angle = static_cast<float>(rand() % 360) * 3.1415926f / 180.f;
        float speed = 200.f + static_cast<float>(rand() % 300);

        p.vel = { std::cos(angle) * speed, std::sin(angle) * speed };
        p.lifetime = 1.0f + static_cast<float>(rand() % 100) / 100.f;

        particles.push_back(p);
    }

    for (int i = 0; i < 4; ++i)
        body[i].color = sf::Color(255, 50, 50);
}

void Player::updateParticles(float dt)
{
    for (auto& p : particles)
    {
        p.pos += p.vel * dt;
        p.lifetime -= dt;
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(),
        [](const Particle& p) { return p.lifetime <= 0.f; }),
        particles.end());
}

void Player::updateGradient(float dt)
{
    if (isCharging && hasBoost)
    {
        rgbTimer += 2.f * dt;

        uint8_t r = static_cast<uint8_t>(std::sin(rgbTimer * 2.f) * 127 + 128);
        uint8_t g = static_cast<uint8_t>(std::sin(rgbTimer * 2.f + 2.f) * 127 + 128);
        uint8_t b = static_cast<uint8_t>(std::sin(rgbTimer * 2.f + 4.f) * 127 + 128);

        body[0].color = sf::Color(r, g, b);
        body[2].color = sf::Color(r, g, b);
        body[1].color = sf::Color(r / 2, g / 2, b / 2);
        body[3].color = sf::Color(r / 2, g / 2, b / 2);
        return;
    }

    const sf::Color normalTop(180, 255, 255);
    const sf::Color normalBottom(255, 120, 120);

    auto lerpColor = [](sf::Color from, sf::Color to, float t)
        {
            return sf::Color(
                static_cast<uint8_t>(from.r + (to.r - from.r) * t),
                static_cast<uint8_t>(from.g + (to.g - from.g) * t),
                static_cast<uint8_t>(from.b + (to.b - from.b) * t)
            );
        };

    for (int i = 0; i < 4; ++i)
    {
        sf::Color target = (i == 0 || i == 2) ? normalTop : normalBottom;
        body[i].color = lerpColor(body[i].color, target, dt * 6.f);
    }

    rgbTimer = 0.f; 
}

void Player::updateFlipBoost(float dt)
{
    if (!speedBoostActive) return;

    velocity.x *= speedBoostMultiplier;
    speedBoostTimer -= dt;
    if (speedBoostTimer <= 0.f)
        speedBoostActive = false;
}


void Player::update(float dt, Pente* pente) {
	//mort du joueur
    if (isDead == true) {
        static float slowTime = 0.f;
        slowTime += dt;
        float timeScale = std::max(0.1f, 1.f - slowTime * 0.8f);
        dt *= timeScale;

        updateParticles(dt);
        body.clear();
        bottomEdge.clear();
        return;
    }

	//MECANIQUE DE JEU
    updateCoyoteTimer(dt);
    handleInput(dt);

	//PHYSIQUE
    applyGravity(dt);
    moveForward(dt, pente);
    checkGroundCollision(pente);

	//EFFETS VISUELS
    updateGradient(dt);
    spawnParticles(dt);
    updateParticles(dt);

    shape.setPosition(position);

    updateFlipBoost(dt);

    //Couleur debug (bleu au sol, rouge en l’air)
    shape.setFillColor(isGrounded ? sf::Color::Cyan : sf::Color::Red);
}

void Player::drawParticles(sf::RenderWindow& window)
{
    for (auto& p : particles)
    {
        sf::CircleShape dot(3.f);
        dot.setFillColor(sf::Color(220, 220, 220, static_cast<uint8_t>(255 * (p.lifetime / 0.4f))));
        dot.setPosition(p.pos);
        window.draw(dot);
    }
}

void Player::drawCube(sf::RenderWindow& window)
{
    sf::RenderStates states;
    sf::Transform t;
    t.translate(shape.getPosition());
    t.rotate(shape.getRotation());
    states.transform = t;

    window.draw(body, states);
    window.draw(bottomEdge, states);
}

void Player::draw(sf::RenderWindow& window) {
    drawParticles(window);
	  drawCube(window);

	//debug pour voir le cote du joueur
    //sf::RectangleShape bottomLine;
    //bottomLine.setSize({ 40.f, 2.f });
    //bottomLine.setOrigin({ 20.f, -20.f });
    //bottomLine.setFillColor(sf::Color::Yellow);
    //bottomLine.setPosition(shape.getPosition());
    //bottomLine.setRotation(shape.getRotation());
    //window.draw(bottomLine);


    ////debug pour le saut
    if (isCharging)
    {
        sf::RectangleShape chargeBar;
        chargeBar.setSize({ 40.f * (chargeTime / maxChargeTime), 5.f });
        chargeBar.setFillColor(sf::Color::Yellow);
        chargeBar.setOrigin({ 20.f, 40.f });
        chargeBar.setPosition(position);
        window.draw(chargeBar);
    }

}