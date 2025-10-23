#include "game.h"
#include <iostream>

Game::Game()
    : player({ 0.f, 300.f }), bg(1920.f, 1080.f)
{
    if (!uiFont.openFromFile("src/fonts/font.ttf")) {
        std::cerr << "Erreur: police introuvable\n";
    }

    scoreManager = std::make_unique<ScoreManager>(uiFont, sf::Vector2f(30.f, 30.f));
    scoreManager->start(player.getPosition().x);
}

Pente* Game::getCurrentPente()
{
    int pPosX = player.getPosition().x;
    for (auto& bloc : blocNiveauList)
    {
        float blocStartX = bloc.getEndPosition().x - bloc.getLength();
        float blocEndX = bloc.getEndPosition().x;

        if (pPosX >= blocStartX && pPosX <= blocEndX)
            return bloc.getPente(pPosX);
    }
    return nullptr;
}

void Game::drawBlocNiveau(sf::RenderWindow& window)
{
    for (int i = 0; i < blocNiveauList.size(); i++)
    {
        blocNiveauList[i].draw(window);
    }
}

void Game::addBlocNiveau(int idBloc)
{
    if (blocNiveauList.empty())
    {
        blocNiveauList.push_back(BlocNiveau(sf::Vector2f(), idBloc));
    }
    else
    {
        blocNiveauList.push_back(BlocNiveau(sf::Vector2f(blocNiveauList[blocNiveauList.size()-1].getEndPosition()), idBloc));
    }
}

void Game::update(float dt)
{
    player.update(dt, getCurrentPente());
    bg.update(dt, player.getView());

    scoreManager->update(dt,
        player.getPosition().x,
        player.getRotationDeg(),
        player.getIsGrounded()
    );
}

void Game::render(sf::RenderWindow& window)
{
    bg.draw(window);
    drawBlocNiveau(window);
    player.draw(window);

    scoreManager->draw(window, player.getView());
}

sf::Vector2f Game::getPlayerPosition() const {
    return player.getPosition();
}