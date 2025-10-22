#include <cstdint>
#include "player.h"
#include <cmath>

Player::Player(sf::Vector2f startPos, float pspeed)
    : position(startPos),
    moveSpeed(pspeed),
    jumpForce(400.f),
    gravity(1000.f),
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
    shape.setSize({ 40.f, 40.f });
    shape.setOrigin({ 20.f, 20.f });
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(position);
    particleSpawnTimer = 0.f;
}

void Player::moveForward(float dt)
{
    const float accel = 300.f;
    const float decel = 200.f;
    const float maxSpeed = 600.f;
    const float minSpeed = 250.f;

    float delta = (isCharging && hasBoost) ? accel : -decel;
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
    if (jumpPressed && canJump && hasBoost)
    {
        isCharging = true;
        chargeTime = std::min(chargeTime + dt, maxChargeTime);
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
        shape.rotate(sf::degrees(-250.f * dt));
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
            shape.setFillColor(sf::Color::Red);
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
    const bool onGround = isCharging && isGrounded;
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

//VERSION AVEC GRAVITE SUR LES PARTICULES
//void Player::updateParticles(float dt)
//{
//    const float particleGravity = 600.f; // gravité locale
//
//    for (size_t i = 0; i < particles.size();)
//    {
//        auto& p = particles[i];
//
//        // Physique simple : gravité + déplacement
//        p.vel.y += particleGravity * dt;
//        p.pos += p.vel * dt;
//        p.lifetime -= dt;
//
//        // Suppression en remplaçant par la dernière (O(1))
//        if (p.lifetime <= 0.f)
//        {
//            particles[i] = particles.back();
//            particles.pop_back();
//        }
//        else
//        {
//            ++i;
//        }
//    }
//}

void Player::update(float dt, Pente* pente) {
	//mort du joueur
    if (isDead)
        return;

    //cameraPlayer.setCenter(position);
    /*cameraPlayer.move(position);*/

	//MECANIQUE DE JEU
    updateCoyoteTimer(dt);
    handleInput(dt);

	//PHYSIQUE
    applyGravity(dt);
    moveForward(dt);
    checkGroundCollision(pente);

	//EFFETS VISUELS
    spawnParticles(dt);
    updateParticles(dt);

    shape.setPosition(position);

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

void Player::draw(sf::RenderWindow& window) {
    drawParticles(window);
    /*window.setView(cameraPlayer);*/
	window.draw(shape);

	//debug pour voir le cote du joueur
    sf::RectangleShape bottomLine;
    bottomLine.setSize({ 40.f, 2.f });
    bottomLine.setOrigin({ 20.f, -20.f });
    bottomLine.setFillColor(sf::Color::Yellow);
    bottomLine.setPosition(shape.getPosition());
    bottomLine.setRotation(shape.getRotation());
    window.draw(bottomLine);


    //debug pour le saut
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