#include "bloc_niveau.h"

BlocNiveau::BlocNiveau(sf::Vector2f posVal, int presetIdVal) : positionStart(posVal), presetId(presetIdVal)
{
	if (presetId == 0)
	{
		penteList.push_back(Pente(500, 0, 10, sf::degrees(30), sf::degrees(0), posVal.y, posVal.y + 200, posVal.x));
		penteList.push_back(Pente(500, 0, 10, sf::degrees(0), sf::degrees(30), posVal.y + 200, posVal.y + 400, 500 + posVal.x));
	}
	else if (presetId == 1)
	{
		// Plateau horizontal avec petite descente
		penteList.push_back(Pente(300, 0, 5, sf::degrees(0), sf::degrees(0), posVal.y, posVal.y, posVal.x));
		penteList.push_back(Pente(300, 0, 10, sf::degrees(0), sf::degrees(-15), posVal.y, posVal.y + 100, posVal.x + 300));
		penteList.push_back(Pente(200, 0, 8, sf::degrees(-15), sf::degrees(0), posVal.y + 100, posVal.y + 150, posVal.x + 600));
	}
	else if (presetId == 2)
	{
		// Montée douce suivie d’un plateau
		penteList.push_back(Pente(400, 0, 10, sf::degrees(0), sf::degrees(20), posVal.y, posVal.y - 150, posVal.x));
		penteList.push_back(Pente(300, 0, 5, sf::degrees(20), sf::degrees(0), posVal.y - 150, posVal.y - 150, posVal.x + 400));
	}
	else if (presetId == 3)
	{
		// Enchaînement en "vague" : monte, descend, remonte
		penteList.push_back(Pente(300, 0, 10, sf::degrees(0), sf::degrees(25), posVal.y, posVal.y - 100, posVal.x));
		penteList.push_back(Pente(300, 0, 10, sf::degrees(25), sf::degrees(-25), posVal.y - 100, posVal.y + 100, posVal.x + 300));
		penteList.push_back(Pente(300, 0, 10, sf::degrees(-25), sf::degrees(0), posVal.y + 100, posVal.y, posVal.x + 600));
	}
	else if (presetId == 4)
	{
		// Descente raide puis légère montée
		penteList.push_back(Pente(400, 0, 10, sf::degrees(0), sf::degrees(-30), posVal.y, posVal.y + 250, posVal.x));
		penteList.push_back(Pente(400, 0, 8, sf::degrees(-30), sf::degrees(10), posVal.y + 250, posVal.y + 200, posVal.x + 400));
	}
	else if (presetId == 5)
	{
		// Terrain bosselé, alternance de pentes courtes
		penteList.push_back(Pente(150, 0, 10, sf::degrees(0), sf::degrees(15), posVal.y, posVal.y - 40, posVal.x));
		penteList.push_back(Pente(150, 0, 10, sf::degrees(15), sf::degrees(-15), posVal.y - 40, posVal.y + 40, posVal.x + 150));
		penteList.push_back(Pente(150, 0, 10, sf::degrees(-15), sf::degrees(0), posVal.y + 40, posVal.y, posVal.x + 300));
	}
	length = 0;
	for (auto& pente : penteList)
		length += pente.getLength();
	
}

int BlocNiveau::getLength()
{
	return length;
}

Pente* BlocNiveau::getPente(int x)
{
	for (auto& pente : penteList)
	{
		float startX = pente.getEndPosition().x - pente.getLength();
		float endX = pente.getEndPosition().x;

		if (x >= startX && x <= endX)
			return &pente;
	}
	return nullptr;
}

sf::Vector2f BlocNiveau::getEndPosition()
{
	return penteList[penteList.size()-1].getEndPosition();
}

void BlocNiveau::draw(sf::RenderWindow& window)
{
	for (auto& pente : penteList)
	{
		pente.draw(window);
	}
}