#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Runner test");

    Game game;
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.update(window);
}
