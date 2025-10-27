#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "AudioSettings.h"

int main() {
    AudioSettings::load();
    
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Projet Runner", sf::State::Fullscreen);

    sf::Image icon;
    if (!icon.loadFromFile("src/assets/logo.jpg"))
    {
        return -1;
    }
    window.setIcon(icon.getSize(), icon.getPixelsPtr());

    StateManager manager(window);
    manager.run();
}
