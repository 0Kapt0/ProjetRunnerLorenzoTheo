#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"

class menu : public state {
private:
	std::vector<sf::Text> menuOptions;
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::RectangleShape backgroundShape;

	void initMenu();
public:
	menu(sf::RenderWindow& window);
	~menu();

	int selectedItemIndex;

	void handleInput() override;
	void update(float deltaTime) override;
	void draw() override;
};

