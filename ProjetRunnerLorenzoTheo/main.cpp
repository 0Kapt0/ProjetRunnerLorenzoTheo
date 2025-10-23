#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "AudioSettings.h"

int main() {
    AudioSettings::load();
    
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Runner test");
    StateManager manager(window);
    
    Game game;
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
    game.addBlocNiveau(0);
  
    manager.run();

    game.update(window);
}
