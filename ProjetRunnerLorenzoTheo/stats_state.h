#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "state.h"

class StatsState : public State
{
private:
    sf::Font font;
    sf::Text back;

    std::vector<sf::Text> statsTexts;

    unsigned int nbRun = 0;
    unsigned int nbPieces = 0;
    unsigned int nbMetres = 0;

    unsigned int nbPiecesRecord = 0;
    unsigned int nbMetresRecord = 0;
    unsigned int vitesseRecord = 0;

public:
	bool backToMenu = false;

    StatsState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float dt) override;
    void draw() override;
    void updateData(int newMetersNb, int newPiecesNb, int vitesseMax);
};