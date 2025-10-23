#include "game.h"


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

void Game::updateNiveau()
{
    if (blocNiveauList[blocNiveauList.size() - 1].getEndPosition().x < player.getPosition().x + 1500)
    {
        addBlocNiveau(std::rand()%6);
    }
    if (blocNiveauList.size() > 5)
    {
        blocNiveauList.erase(blocNiveauList.begin());
    }
}

void Game::update(float dt)
{
    updateNiveau();
    player.update(dt, getCurrentPente());
    bg.update(dt);
  
    view.updateCamera(dt, player.getPosition());
}

void Game::render(sf::RenderWindow& window)
{
    view.setView(window);
    bg.draw(window);
    drawBlocNiveau(window);
    player.draw(window);
}

sf::Vector2f Game::getPlayerPosition() const {
    return player.getPosition();
}