#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"

class menu : public state {
private:
	std::vector<sf::Text> menuOptions;
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::RectangleShape backgroundShape;

	sf::Music menuMusic;

	void initMenu();
public:
	menu(sf::RenderWindow& window);
	~menu();

	int selectedItemIndex;

	bool startGame = false;
	bool openOptions = false;

	void handleInput() override;
	void update(float deltaTime) override;
	void draw() override;

	sf::Music& getMusic() { return menuMusic; }
};

