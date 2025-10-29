#pragma once
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>

class AudioSettings {
public:
    static float globalMusicVolume;
    static float globalSfxVolume;

    static void load();
    static void save();
    static void applyTo(sf::Music& music);
};
