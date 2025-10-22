#pragma once
#include "pente.h"

class BlocNiveau
{
private:
	int length = 0;
	sf::Vector2f positionStart;
	int presetId;

	
public:
	std::vector<Pente> penteList;

	BlocNiveau(sf::Vector2f posVal, int presetId);

	int getLength();
	Pente* getPente(int x);
	sf::Vector2f getEndPosition();
	void draw(sf::RenderWindow& window);
};

