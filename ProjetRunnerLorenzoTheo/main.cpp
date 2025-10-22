#include <SFML/Graphics.hpp>
#include "StateManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Runner test");
    StateManager manager(window);
    manager.run();
}
