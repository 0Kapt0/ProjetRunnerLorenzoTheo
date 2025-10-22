#include "menu.h"
#include <iostream>

menu::menu(sf::RenderWindow& window)
    : state(window), selectedItemIndex(-1) {
    if (!font.openFromFile("src/fonts/font.ttf")) {
        std::cerr << "Erreur de chargement de la police" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("src/assets/backgrounds/menu_background.png")) {
        std::cerr << "Erreur de chargement du fond d'écran du menu\n";
    }

    backgroundShape.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)
    ));
    backgroundShape.setTexture(&backgroundTexture);


    /*if (!menuMusic.openFromFile("assets/music/Music_jeu.ogg")) {
        cerr << "Erreur de chargement du fond d'écran du menu\n";
    }
    else {
        menuMusic.setLoop(true);
        menuMusic.setVolume(10.f);
        menuMusic.play();
    }*/
    
    initMenu();
}

menu::~menu() {
    /*menuMusic.stop();*/
}

void menu::initMenu() {
    sf::Text startGame(font);
    startGame.setCharacterSize(65);
    startGame.setString("Play");
    startGame.setPosition({ 100, 100 });
    menuOptions.push_back(startGame);

    sf::Text options(font);
    options.setCharacterSize(65);
    options.setString("Options");
    options.setPosition({ 100, 175 });
    menuOptions.push_back(options);

    sf::Text quit(font);
    quit.setCharacterSize(65);
    quit.setString("Quit");
    quit.setPosition({ 100, 250 });
    menuOptions.push_back(quit);

    for (auto& option : menuOptions) {
        option.setFillColor(sf::Color::White);
    }
}

void menu::handleInput() {
    sf::Vector2f mousePosF = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    bool mouseOverOption = false;

    for (int i = 0; i < menuOptions.size(); ++i) {
        if (menuOptions[i].getGlobalBounds().contains(mousePosF)) {
            menuOptions[i].setFillColor(sf::Color::Red);
            mouseOverOption = true;
            selectedItemIndex = i;
        }
        else {
            menuOptions[i].setFillColor(sf::Color::White);
        }
    }

    if (!mouseOverOption) {
        selectedItemIndex = -1; 
    }
}


void menu::update(float) {
    for (std::size_t i = 0; i < menuOptions.size(); i++) {
        menuOptions[i].setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
    }
}


void menu::draw() {
    window.draw(backgroundShape);
    for (auto& option : menuOptions) {
        window.draw(option);
    }
}