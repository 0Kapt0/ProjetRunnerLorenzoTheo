#pragma once
#include "pente.h"
#include "piece.h"

class BlocNiveau
{
private:
	int length = 0;
	sf::Vector2f positionStart;
	int presetId;
	std::vector<Pente> penteList;
	std::vector<std::unique_ptr<Bonus>> bonusList;
	
public:
	BlocNiveau(sf::Vector2f posVal, int presetId);

	int getLength();
	Pente* getPente(int x);
	sf::Vector2f getEndPosition();
	
	std::vector<std::unique_ptr<Bonus>>& getBonusList() { return bonusList; }

	void draw(sf::RenderWindow& window);
};

