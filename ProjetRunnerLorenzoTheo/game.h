#pragma once
#include "player.h"
#include "bloc_niveau.h"
#include "ScoreManager.h"
#include "background.h"

class Game
{
private:
	Player player;
	sf::Clock clock;
	Background bg;

	int bonusX = 0;
	std::vector<BlocNiveau> blocNiveauList;

	sf::Font uiFont;
	std::unique_ptr<ScoreManager> scoreManager;

	void drawBlocNiveau(sf::RenderWindow& window);
	Pente* getCurrentPente();

public:
	Game();

	void addBlocNiveau(int idBloc);
	void render(sf::RenderWindow& window);
	void update(float dt);

	sf::Vector2f getPlayerPosition() const;
};

