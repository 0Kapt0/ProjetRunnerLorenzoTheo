#include "bloc_niveau.h"

BlocNiveau::BlocNiveau(sf::Vector2f posVal, int presetId)
{
	positionStart = posVal;

	if (presetId == 0)
	{
		penteList.push_back(Pente(1000, 0, 10, sf::degrees(30), sf::degrees(0), posVal.y, posVal.y + 200, posVal.x));
		penteList.push_back(Pente(500, 0, 10, sf::degrees(0), sf::degrees(30), posVal.y + 200, posVal.y, 1000 + posVal.x));
	}
	else if (presetId == 1)
	{
		
	}

	for (int i = 0; i < penteList.size(); i++)
	{
		length += penteList[i].getLength();
	}
}

int BlocNiveau::getLength()
{
	return length;
}

sf::Vector2f BlocNiveau::getEndPosition()
{
	return penteList[penteList.size()-1].getEndPosition();
}

void BlocNiveau::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < penteList.size(); i++)
	{
		penteList[i].draw(window);
	}
}