#pragma once
#include "player.h"
#include "bloc_niveau.h"

#include "background.h"

class Game
{
private:
	Player player;
	sf::Clock clock;

	int bonusX = 0;
	std::vector<BlocNiveau> blocNiveauList;

	void drawBlocNiveau(sf::RenderWindow& window);
	Pente* getCurrentPente();

public:
	Game():player({0.f, 300.f}) {};

	void addBlocNiveau(int idBloc);
	void update(sf::RenderWindow& window);
};

