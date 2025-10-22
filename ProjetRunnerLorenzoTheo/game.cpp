#include "game.h"

#include <iostream>
//Pente* Game::getCurrentPente()
//{
//    int pPosX = player.getPosition().x;
//    for (int i = 0; i < blocNiveauList.size(); i++)
//    {
//        if (pPosX <= blocNiveauList[i].getEndPosition().x && pPosX >= (blocNiveauList[i].getEndPosition().x - blocNiveauList[i].getLength()))
//        {
//            std::cout << "BlocNiveau . Hauteur : " << blocNiveauList[i].penteList[i].getSurfaceHeight(player.getPosition().x) << " -  Angle : " << blocNiveauList[i].penteList[i].getOrientation(player.getPosition().x).asDegrees() << "\n";
//            return blocNiveauList[i].getPente(pPosX);
//        }
//    }
//    //return &blocNiveauList[0].getPente(pPosX);
//}

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

void Game::update(sf::RenderWindow& window)
{
    
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();

        player.update(dt, getCurrentPente());

        window.clear(sf::Color::Black);
        
        drawBlocNiveau(window);

        player.draw(window);

        //tests
        for (unsigned x = 0; x < 2001; x += 500)
        {
            sf::RectangleShape bar({ 10, 800 }); // largeur = thickness, hauteur = pleine hauteur
            bar.setPosition({ float(x), 0.f });
            bar.setFillColor(sf::Color::Red);
            window.draw(bar);
        }

        window.display();
    }
}