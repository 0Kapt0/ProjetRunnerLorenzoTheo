#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "state.h"
#include "audio_settings.h"

class Menu : public State {
private:
	std::vector<sf::Text> menuOptions;
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::RectangleShape backgroundShape;

	sf::Music menuMusic;

	void initMenu();
public:
	Menu(sf::RenderWindow& window);
	~Menu();

	int selectedItemIndex;

	bool startGame = false;
	bool openOptions = false;
	bool openStats = false;

	void handleInput() override;
	void update(float deltaTime) override;
	void draw() override;

	sf::Music& getMusic() { return menuMusic; }
};