#include "game_state.h"

GameState::GameState(sf::RenderWindow& window)
    : State(window)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < 3; ++i) {
        game.addBlocNiveau(0);
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int track = std::rand() % 4 + 1;

    std::string path = "src/music/inGameMusic" + std::to_string(track) + ".mp3";
    if (!gameMusic.openFromFile(path)) {
        std::cerr << "Erreur de chargement musique : " << path << "\n";
    }
    else {
        gameMusic.setLooping(true);
        AudioSettings::applyTo(gameMusic);
        gameMusic.play();
    }
}

void GameState::handleInput()
{
    if (!isPaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        isPaused = true;
    }
}

void GameState::update(float dt)
{
    game.update(dt);
}

void GameState::draw()
{
    game.render(window);
}
