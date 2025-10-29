#pragma once
#include <SFML/Graphics.hpp>
#include "pente.h"

class Player
{
private:
	//player shape and sprite
	sf::RectangleShape shape;
	sf::VertexArray body;
	sf::VertexArray bottomEdge;
	float rgbTimer;

	//Player pos and mov
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f startPosition;
	float moveSpeed;
	float jumpForce;
	float gravity;

	//Player state
	bool isDead;
	bool isJumping;
	bool isGrounded;

	//Jump fonction
	bool isCharging;
	float chargeTime;
	float maxChargeTime;
	bool hasBoost;
	float coyoteTimer;
	float maxCoyoteTime;

	//Boost temporaire apres un flip reussi
	bool speedBoostActive = false;
	float speedBoostTimer = 0.f;
	float speedBoostDuration = 1.3f;
	float speedBoostMultiplier = 2.5f;

	//methode interne
	void moveForward(float dt, Pente* pente);
	void applyGravity(float dt);
	void handleInput(float dt);
	void checkGroundCollision(Pente* pente);
	void updateCoyoteTimer(float dt);
	void explodeOnDeath();

	void updateGradient(float dt);
	void drawCube(sf::RenderWindow& window);

	void updateFlipBoost(float dt);

	//methode particules
	void createJumpPoof();
	void spawnParticles(float dt);
	void updateParticles(float dt);
	void drawParticles(sf::RenderWindow& window);

	//effects visuels
	struct Particle
	{
		sf::Vector2f pos;
		sf::Vector2f vel;
		float lifetime;
	};

	std::vector<Particle> particles;
	float particleSpawnTimer;

	int maxSpeed = 0;

public:
	Player(sf::Vector2f startPos, float pspeed = 250.f);

	void update(float dt, Pente* pente);
	void draw(sf::RenderWindow& window);

	void applyFlipBoost();

	sf::Vector2f getPosition() const { return position; }
	sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
	bool getIsGrounded() const { return isGrounded; }
	float getRotationDeg() const { return shape.getRotation().asDegrees(); }
	void setHasBoost(bool state) { hasBoost = state; }
	bool isUsingBoost() const { return isCharging && hasBoost; }
	bool getIsDead() const { return isDead; }
	float getSpeed() const { return velocity.x; }
	int getMaxSpeed() { return maxSpeed; };
	void isDeadReset();
};