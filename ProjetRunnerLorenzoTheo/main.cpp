#include <SFML/Graphics.hpp>
#include "state_manager.h"
#include "audio_settings.h"

int main() {
    AudioSettings::load();
    
    /*sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Projet Runner", sf::State::Fullscreen);*/
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Projet Runner", sf::State::Windowed);

    sf::Image icon;
    if (!icon.loadFromFile("src/assets/logo.jpg"))
    {
        return -1;
    }
    window.setIcon(icon.getSize(), icon.getPixelsPtr());

    StateManager manager(window);
    manager.run();
}
