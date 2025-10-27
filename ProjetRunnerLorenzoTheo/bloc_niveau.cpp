#include "bloc_niveau.h"

#include <iostream>

BlocNiveau::BlocNiveau(sf::Vector2f posVal, int presetIdVal) : positionStart(posVal), presetId(presetIdVal)
{
	if (presetId == 0)
	{
		// Départ simple et plat — idéal pour le tuto
		penteList.push_back(Pente(700, 100, sf::degrees(0), sf::degrees(0), posVal.y, posVal.y, posVal.x));

		bonusList.push_back(std::make_unique<Piece>(sf::Vector2f(posVal.x + 400, posVal.y - 150)));
	}
	else if (presetId == 1)
	{
		// Descente douce puis plat
		penteList.push_back(Pente(500, 20, sf::degrees(0), sf::degrees(-10),
			posVal.y, posVal.y + 150, posVal.x));
		penteList.push_back(Pente(500, 20, sf::degrees(-10), sf::degrees(0),
			posVal.y + 150, posVal.y + 150, posVal.x + 500));

		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 300, posVal.y - 100)));
		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 700, posVal.y - 50)));
	}
	else if (presetId == 2)
	{
		// Grande descente rapide avec un creux
		penteList.push_back(Pente(600, 10, sf::degrees(0), sf::degrees(-20),
			posVal.y, posVal.y + 250, posVal.x));
		penteList.push_back(Pente(400, 10, sf::degrees(-20), sf::degrees(5),
			posVal.y + 250, posVal.y + 180, posVal.x + 600));

		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 400, posVal.y + 50)));
		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 800, posVal.y - 120)));
	}
	else if (presetId == 3)
	{
		// Série de vagues descendantes
		penteList.push_back(Pente(300, 10, sf::degrees(-5), sf::degrees(-15),
			posVal.y, posVal.y + 120, posVal.x));
		penteList.push_back(Pente(300, 10, sf::degrees(-15), sf::degrees(-5),
			posVal.y + 120, posVal.y + 180, posVal.x + 300));
		penteList.push_back(Pente(400, 10, sf::degrees(-5), sf::degrees(0),
			posVal.y + 180, posVal.y + 200, posVal.x + 600));

		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 200, posVal.y - 100)));
		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 500, posVal.y - 80)));
		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 800, posVal.y - 60)));
	}

	else if (presetId == 4)
	{
		// Longue descente progressive avec un petit saut
		penteList.push_back(Pente(700, 10, sf::degrees(-5), sf::degrees(-15),
			posVal.y, posVal.y + 250, posVal.x));
		penteList.push_back(Pente(200, 10, sf::degrees(-15), sf::degrees(0),
			posVal.y + 250, posVal.y + 200, posVal.x + 700));
		penteList.push_back(Pente(400, 100, sf::degrees(0), sf::degrees(0),
			posVal.y + 200, posVal.y + 200, posVal.x + 900));

		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 500, posVal.y + 50)));
		bonusList.push_back(std::make_unique<Piece>(
			sf::Vector2f(posVal.x + 850, posVal.y - 100)));
	}
	else if (presetId == 5)
	{
		// Terrain bosselé, alternance de pentes courtes
		penteList.push_back(Pente(150, 10, sf::degrees(0), sf::degrees(15), posVal.y, posVal.y - 40, posVal.x));
		penteList.push_back(Pente(150, 10, sf::degrees(15), sf::degrees(-15), posVal.y - 40, posVal.y + 40, posVal.x + 150));
		penteList.push_back(Pente(150, 10, sf::degrees(-15), sf::degrees(0), posVal.y + 40, posVal.y, posVal.x + 300));
	}
	else if (presetId == 6)
	{
		penteList.push_back(Pente(500, 10, sf::degrees(0), sf::degrees(-30), posVal.y, posVal.y + 200, posVal.x));
		penteList.push_back(Pente(300, 10, sf::degrees(-30), sf::degrees(-15), posVal.y + 200, posVal.y, posVal.x + 500));
		penteList.push_back(Pente(500, 10, sf::degrees(0), sf::degrees(0), posVal.y, posVal.y, posVal.x + 800));
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
	
	for (auto& bonus : bonusList)
	{
		bonus->draw(window);
	}
}
