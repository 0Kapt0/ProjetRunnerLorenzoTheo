#pragma once
#include <SFML/Graphics.hpp>
#include "pente.h"

class Player
{
private:
	//camera
	sf::View cameraPlayer;
	sf::Vector2f cameraTarget;
	float cameraSmoothness;
	sf::Vector2f cameraOffset;

	//player shape and sprite
	sf::RectangleShape shape;
	sf::VertexArray body;
	sf::VertexArray bottomEdge;
	float rgbTimer;

	//Player pos and mov
	sf::Vector2f velocity;
	sf::Vector2f position;
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
	void moveForward(float dt);
	void applyGravity(float dt);
	void handleInput(float dt);
	void checkGroundCollision(Pente* pente);
	void updateCoyoteTimer(float dt);
	void updateCamera(float dt);

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

public:
	Player(sf::Vector2f startPos, float pspeed = 250.f);

	void update(float dt, Pente* pente);
	void draw(sf::RenderWindow& window);

	void applyFlipBoost();

	sf::Vector2f getPosition() const { return position; }
	sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
	sf::View getView() { return cameraPlayer; }
	bool getIsGrounded() const { return isGrounded; }
	float getRotationDeg() const { return shape.getRotation().asDegrees(); }
	void setHasBoost(bool state) { hasBoost = state; }
	bool isUsingBoost() const { return isCharging && hasBoost; }

};

