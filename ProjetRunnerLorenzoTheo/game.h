#pragma once
#include <iostream>
#include "player.h"
#include "bloc_niveau.h"
#include "ScoreManager.h"
#include "background.h"
#include "view.h"
class Game
{
private:
	View view;
	Player player;
	float pickupRadius = 100.f;
	sf::Clock clock;
	Background bg;

	int bonusX = 0;
	std::vector<BlocNiveau> blocNiveauList;

	sf::Font uiFont;
	std::unique_ptr<ScoreManager> scoreManager;

	void drawBlocNiveau(sf::RenderWindow& window);
	Pente* getCurrentPente();

	void updatePiece();
public:
	Game();

	void addBlocNiveau(int idBloc);
	void updateNiveau();
	void render(sf::RenderWindow& window);
	void update(float dt);

	sf::Vector2f getPlayerPosition() const;
};

