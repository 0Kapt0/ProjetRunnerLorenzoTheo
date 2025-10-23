#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "AudioSettings.h"

int main() {
    AudioSettings::load();

    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Runner test");
    StateManager manager(window);
    manager.run();
}
