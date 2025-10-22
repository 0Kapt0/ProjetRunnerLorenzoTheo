#include "bloc_niveau.h"

BlocNiveau::BlocNiveau(sf::Vector2f posVal, int presetIdVal) : positionStart(posVal), presetId(presetIdVal)
{
	if (presetId == 0)
	{
		penteList.push_back(Pente(500, 0, 10, sf::degrees(30), sf::degrees(0), posVal.y, posVal.y + 200, posVal.x));
		penteList.push_back(Pente(510, 0, 10, sf::degrees(0), sf::degrees(30), posVal.y + 250, posVal.y + 400, 500 + posVal.x));
	}
	else if (presetId == 1)
	{
		 
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