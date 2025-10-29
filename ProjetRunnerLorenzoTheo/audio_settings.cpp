#include "audio_settings.h"

float AudioSettings::globalMusicVolume = 30.f;
float AudioSettings::globalSfxVolume = 30.f;

void AudioSettings::load()
{
    std::ifstream file("src/music/config/config_audio.txt");
    if (file.is_open()) {
        file >> globalMusicVolume >> globalSfxVolume;
        file.close();
    }
    else {
        globalMusicVolume = 50.f;
        globalSfxVolume = 50.f;
        std::cout << "[AudioSettings] No config found, using defaults.\n";
    }
}

void AudioSettings::save()
{
    std::ofstream file("config_audio.txt", std::ios::trunc);
    if (file.is_open()) {
        file << globalMusicVolume << " " << globalSfxVolume;
        file.close();
    }
    else {
        std::cerr << "[AudioSettings] Failed to save config_audio.txt\n";
    }
}

void AudioSettings::applyTo(sf::Music& music)
{
    music.setVolume(globalMusicVolume);
}
