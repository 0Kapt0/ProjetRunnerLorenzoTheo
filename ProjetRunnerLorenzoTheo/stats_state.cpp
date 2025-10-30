#include "stats_state.h"

StatsState::StatsState(sf::RenderWindow& window): State(window), back(font)
{
	if (!font.openFromFile("src/fonts/font.ttf")) {
		std::cerr << "Erreur de chargement de la police\n";
	}

	back.setCharacterSize(50);
	back.setString("Back");
	back.setPosition({ 200.f, 850.f });

    for (int i = 0; i < 7; i++)
    {
        statsTexts.push_back(sf::Text(font, "", 40));
        statsTexts[i].setPosition({ 250.f, 100.f + i*100 });
    }

    std::ifstream fichierStats("src/fichierStats.txt");
    if (fichierStats.is_open())
    {
        fichierStats >> nbRun >> nbPieces >> nbMetres >> nbPiecesRecord >> nbMetresRecord >> vitesseRecord >> scoreRecord;
        fichierStats.close();
    }
    else {
        std::cout << "Impossible d'ouvrir fichierStats.txt, valeurs par défaut utilisées.\n";
    }

    statsTexts[0].setString("Nombre de Parties                                                " + std::to_string(nbRun));
    statsTexts[1].setString("Nombre de Pieces recoltees               " + std::to_string(nbPieces));
    statsTexts[2].setString("Record de Pieces recoltees                 " + std::to_string(nbPiecesRecord));
    statsTexts[3].setString("Nombre de metres parcourus          " + std::to_string(nbMetres));
    statsTexts[4].setString("Record de distance                                              " + std::to_string(nbMetresRecord));
    statsTexts[5].setString("Record de Vitesse                                                  " + std::to_string(vitesseRecord));
    statsTexts[6].setString("Record de Points                                                  " + std::to_string(scoreRecord));
    
}

void StatsState::handleInput()
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (back.getGlobalBounds().contains(mousePos)) {
            backToMenu = true;
        }
    }
}

void StatsState::update(float dt) {}

void StatsState::draw()
{
    window.setView(window.getDefaultView());
    window.draw(back);
    for (int i = 0; i < 7; i++)
    {
        window.draw(statsTexts[i]);
    }
}

void StatsState::updateData(int newMetersNb, int newPiecesNb, int maxSpeed)
{
    nbRun += 1;
    nbPieces += newPiecesNb;
    nbMetres += newMetersNb;

    if (newPiecesNb > nbPiecesRecord)
    {
        nbPiecesRecord = newPiecesNb;
    }
    if (newMetersNb > nbMetresRecord)
    {
        nbMetresRecord = newMetersNb;
    }
    if (maxSpeed > vitesseRecord)
    {
        vitesseRecord = maxSpeed;
    }
    if (ScoreManager::highestScore > scoreRecord)
    {
        scoreRecord = ScoreManager::highestScore;
    }
   

    std::ofstream fichierOut("src/fichierStats.txt");
    if (fichierOut.is_open()) {
        fichierOut << nbRun << "\n" << nbPieces << "\n" << nbMetres << "\n" << nbPiecesRecord << "\n" << nbMetresRecord << "\n" << vitesseRecord << "\n" << scoreRecord << "\n";
        fichierOut.close();
        std::cout << "Ecriture réussie.\n";
    }
    else {
        std::cout << "Erreur : impossible d’écrire dans data.txt\n";
    }

    statsTexts[0].setString("Nombre de Parties                                                " + std::to_string(nbRun));
    statsTexts[1].setString("Nombre de Pieces recoltees               " + std::to_string(nbPieces));
    statsTexts[2].setString("Record de Pieces recoltees                 " + std::to_string(nbPiecesRecord));
    statsTexts[3].setString("Nombre de metres parcourus          " + std::to_string(nbMetres));
    statsTexts[4].setString("Record de distance                                              " + std::to_string(nbMetresRecord));
    statsTexts[5].setString("Record de Vitesse                                                  " + std::to_string(vitesseRecord));
    statsTexts[6].setString("Record de Points                                                  " + std::to_string(scoreRecord));
}