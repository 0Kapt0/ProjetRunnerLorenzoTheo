#pragma once
#include <iostream>
#include "player.h"
#include "bloc_niveau.h"
#include "ScoreManager.h"
#include "background.h"
#include "view.h"
#include "speedometer.h"

class Game
{
private:
	View view;
	Player player;
	float pickupRadius = 70.f;
	sf::Clock clock;
	Background bg;
	std::unique_ptr<Speedometer> speedometer;

	int bonusX = 0;
	std::vector<BlocNiveau> blocNiveauList;

	sf::Font uiFont;
	std::unique_ptr<ScoreManager> scoreManager;

	void drawBlocNiveau(sf::RenderWindow& window);
	Pente* getCurrentPente();

	void updatePiece();
	bool gameOver = false;
	bool wantGameOver = false;

	int nbPiecesRun;

public:
	Game();

	void addBlocNiveau(int idBloc);
	void updateNiveau();
	void render(sf::RenderWindow& window);
	void update(float dt);

	bool getWantGameOver() const { return wantGameOver; }
	sf::Vector2f getPlayerPosition() const;
	Player& getPlayer() { return player; };
	void isDeadReset();
	int getPiecesNb() { return nbPiecesRun; };
};

