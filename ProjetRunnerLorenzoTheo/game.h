#pragma once
#include "player.h"
#include "bloc_niveau.h"

#include "background.h"

class Game
{
private:
	Player player;
	sf::Clock clock;
	Background bg;

	int bonusX = 0;
	std::vector<BlocNiveau> blocNiveauList;

	void drawBlocNiveau(sf::RenderWindow& window);
	Pente* getCurrentPente();

public:
	Game():player({0.f, 300.f}), bg(1920.f, 1080.f) {};

	void addBlocNiveau(int idBloc);
	void render(sf::RenderWindow& window);
	void update(float dt);

	sf::Vector2f getPlayerPosition() const;
};

