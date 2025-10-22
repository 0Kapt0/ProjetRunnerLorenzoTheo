#pragma once
#include "state.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>

class OptionsState : public state {
private:
    sf::Font font;
    std::vector<sf::Text> options;
    sf::RectangleShape background;

    sf::RectangleShape musicBar, musicHandle;
    sf::RectangleShape sfxBar, sfxHandle;
    bool draggingMusic = false;
    bool draggingSFX = false;

    int selectedIndex = -1;
    float musicVolume = 100.f;
    float sfxVolume = 100.f;

    sf::Music* currentMusic = nullptr;
public:
    bool backToMenu = false;

    OptionsState(sf::RenderWindow& window);

    void handleInput() override;
    void update(float dt) override;
    void draw() override;

    float getMusicVolume() const { return musicVolume; }
    float getSfxVolume() const { return sfxVolume; }
};
