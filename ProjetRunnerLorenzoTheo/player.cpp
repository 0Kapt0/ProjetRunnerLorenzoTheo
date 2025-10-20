#include "player.h"

Player::Player(sf::Vector2f startPos, float pspeed)
    : position(startPos),
    moveSpeed(pspeed),
    jumpForce(500.f),
    gravity(1000.f),
    isJumping(false),
    isGrounded(false),
    isDead(false)
{
    shape.setSize({ 40.f, 40.f });
    shape.setOrigin({ 20.f, 20.f });
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(position);
}

void Player::moveForward(float dt) {
    velocity.x = moveSpeed;
    position.x += velocity.x * dt;
}

void Player::applyGravity(float dt) {
    velocity.y += gravity * dt;
    position.y += velocity.y * dt;
}

void Player::handleJump() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded)
    {
        velocity.y = -jumpForce;
        isGrounded = false;
        isJumping = true;
    }
}

void Player::update(float deltatime) {
    shape.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
}