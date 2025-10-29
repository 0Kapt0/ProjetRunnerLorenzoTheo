#include "menu.h"

Menu::Menu(sf::RenderWindow& window)
    : State(window), selectedItemIndex(-1) {
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


    if (!menuMusic.openFromFile("src/music/menuMusic.mp3")) {
        std:: cerr << "Erreur de chargement du fond d'écran du menu\n";
    }
    else {
        menuMusic.setLooping(true);
        AudioSettings::applyTo(menuMusic);
        menuMusic.play();
    }
    
    initMenu();
}

Menu::~Menu() {
    menuMusic.stop();
}

void Menu::initMenu() {
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

    sf::Text stats(font);
    stats.setCharacterSize(65);
    stats.setString("Stats");
    stats.setPosition({ 100, 250 });
    menuOptions.push_back(stats);

    sf::Text quit(font);
    quit.setCharacterSize(65);
    quit.setString("Quit");
    quit.setPosition({ 100, 325 });
    menuOptions.push_back(quit);

    for (auto& option : menuOptions) {
        option.setFillColor(sf::Color::White);
    }
}

void Menu::handleInput() {
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selectedItemIndex != -1) {
        auto text = menuOptions[selectedItemIndex].getString();
        if (text == "Play") {
            startGame = true;
        }
        else if (text == "Options") {
            openOptions = true;
        }
        else if (text == "Stats")
        {
            openStats = true;
        }
        else if (text == "Quit") {
            window.close();
        }
    }

}

void Menu::update(float) {
    for (std::size_t i = 0; i < menuOptions.size(); i++) {
        menuOptions[i].setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
    }
}

void Menu::draw() {
    window.setView(window.getDefaultView());
    window.draw(backgroundShape);
    for (auto& option : menuOptions) {
        window.draw(option);
    }
}