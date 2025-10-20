#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	//player shape and sprite
	sf::RectangleShape shape;

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

	//methode interne
	void moveForward(float dt);
	void applyGravity(float dt);
	void handleJump();
	void checkGroundCollision();
public:
	Player(sf::Vector2f startPos, float pspeed = 250.f);

	void update(float dt);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const { return position; }
	sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};

