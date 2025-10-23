#include "options_state.h"
#include "AudioSettings.h"
#include <iostream>
#include <algorithm>

OptionsState::OptionsState(sf::RenderWindow& window)
    : state(window)
{
    if (!font.openFromFile("src/fonts/font.ttf")) {
        std::cerr << "Erreur de chargement de la police\n";
    }

    background.setSize(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(0, 0, 0, 180));

    sf::Text title(font);
    title.setCharacterSize(80);
    title.setString("OPTIONS");
    title.setFillColor(sf::Color::Yellow);
    title.setPosition({ window.getSize().x / 2.f - title.getLocalBounds().size.x / 2.f, 100.f });
    options.push_back(title);

    sf::Text musicVol(font);
    musicVol.setCharacterSize(50);
    musicVol.setString("Music Volume");
    musicVol.setPosition({ 200.f, 280.f });
    options.push_back(musicVol);

    sf::Text sfxVol(font);
    sfxVol.setCharacterSize(50);
    sfxVol.setString("SFX Volume");
    sfxVol.setPosition({200.f, 420.f});
    options.push_back(sfxVol);

    sf::Text back(font);
    back.setCharacterSize(50);
    back.setString("Back");
    back.setPosition({ 200.f, 600.f });
    options.push_back(back);

	//SLIDER MUSIC
    musicBar.setSize({ 400.f, 8.f });
    musicBar.setFillColor(sf::Color(180, 180, 180));
    musicBar.setPosition({ 900.f, 320.f });

    musicHandle.setSize({ 20.f, 40.f });
    musicHandle.setFillColor(sf::Color::White);
    musicHandle.setOrigin({ 10.f, 20.f });
    musicHandle.setPosition({ musicBar.getPosition().x, musicBar.getPosition().y + 4.f });

    //SLIDER SFX
    sfxBar.setSize({ 400.f, 8.f });
    sfxBar.setFillColor(sf::Color(180, 180, 180));
    sfxBar.setPosition({ 900.f, 460.f });

    sfxHandle.setSize({ 20.f, 40.f });
    sfxHandle.setFillColor(sf::Color::White);
    sfxHandle.setOrigin({ 10.f, 20.f });
    sfxHandle.setPosition({ sfxBar.getPosition().x, sfxBar.getPosition().y + 4.f });

    musicVolume = AudioSettings::globalMusicVolume;
    sfxVolume = AudioSettings::globalSfxVolume;

    {
        float ratio = musicVolume / 100.f;
        musicHandle.setPosition({
            musicBar.getPosition().x + ratio * musicBar.getSize().x,
            musicHandle.getPosition().y
            });
    }

    {
        float ratio = sfxVolume / 100.f;
        sfxHandle.setPosition({
            sfxBar.getPosition().x + ratio * sfxBar.getSize().x,
            sfxHandle.getPosition().y
            });
    }
}

void OptionsState::handleInput()
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (musicHandle.getGlobalBounds().contains(mousePos) ||
            musicBar.getGlobalBounds().contains(mousePos)) {
            draggingMusic = true;
        }
        else if (sfxHandle.getGlobalBounds().contains(mousePos) ||
            sfxBar.getGlobalBounds().contains(mousePos)) {
            draggingSFX = true;
        }
    }
    else {
        draggingMusic = draggingSFX = false;
    }

    if (draggingMusic) {
        float ratio = (mousePos.x - musicBar.getPosition().x) / musicBar.getSize().x;
        ratio = std::clamp(ratio, 0.f, 1.f);
        musicVolume = ratio * 100.f;
        musicHandle.setPosition({ musicBar.getPosition().x + ratio * musicBar.getSize().x,
            musicHandle.getPosition().y });

        AudioSettings::globalMusicVolume = musicVolume;
        AudioSettings::save();
    }

    if (draggingSFX) {
        float ratio = (mousePos.x - sfxBar.getPosition().x) / sfxBar.getSize().x;
        ratio = std::clamp(ratio, 0.f, 1.f);
        sfxVolume = ratio * 100.f;
        sfxHandle.setPosition({ sfxBar.getPosition().x + ratio * sfxBar.getSize().x,
            sfxHandle.getPosition().y });

        AudioSettings::globalSfxVolume = sfxVolume;
        AudioSettings::save();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (options.back().getGlobalBounds().contains(mousePos)) {
            backToMenu = true;
        }
    }
}

void OptionsState::update(float) {}

void OptionsState::draw()
{
    window.setView(window.getDefaultView());
    window.draw(background);

    for (auto& opt : options)
        window.draw(opt);

    window.draw(musicBar);
    window.draw(musicHandle);

    window.draw(sfxBar);
    window.draw(sfxHandle);
}
