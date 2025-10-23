#include "game.h"

Game::Game()
    : view(), player({ 1000.f, 300.f }), bg(1920.f, 1080.f, view), gameOverText(uiFont, "GAME OVER", 120)
{
    if (!uiFont.openFromFile("src/fonts/font.ttf")) {
        std::cerr << "Erreur: police introuvable\n";
    }

    scoreManager = std::make_unique<ScoreManager>(uiFont, sf::Vector2f(30.f, 30.f));
    scoreManager->start(player.getPosition().x);

    gameOverOverlay.setSize({ 1920.f, 1080.f });
    gameOverOverlay.setFillColor(sf::Color(0, 0, 0, 160));

    gameOverText.setFillColor(sf::Color::White);
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    gameOverText.setPosition({ 960.f, 400.f });

}

Pente* Game::getCurrentPente()
{
    int pPosX = player.getPosition().x;
    for (auto& bloc : blocNiveauList)
    {
        float blocStartX = bloc.getEndPosition().x - bloc.getLength();
        float blocEndX = bloc.getEndPosition().x;

        if (pPosX >= blocStartX && pPosX <= blocEndX)
            return bloc.getPente(pPosX);
    }
    return nullptr;
}

void Game::drawBlocNiveau(sf::RenderWindow& window)
{
    for (int i = 0; i < blocNiveauList.size(); i++)
    {
        blocNiveauList[i].draw(window);
    }
}

void Game::addBlocNiveau(int idBloc)
{
    if (blocNiveauList.empty())
    {
        blocNiveauList.push_back(BlocNiveau(sf::Vector2f(), idBloc));
    }
    else
    {
        blocNiveauList.push_back(BlocNiveau(sf::Vector2f(blocNiveauList[blocNiveauList.size()-1].getEndPosition()), idBloc));
    }
}

void Game::updateNiveau()
{
    if (blocNiveauList[blocNiveauList.size() - 1].getEndPosition().x < player.getPosition().x + 1500)
    {
        addBlocNiveau(std::rand()%6);
    }
    if (blocNiveauList.size() > 5)
    {
        blocNiveauList.erase(blocNiveauList.begin());
    }
}

void Game::update(float dt)
{
    if (player.getIsDead())
    {
        gameOver = true;
    }

    float currentBoost = scoreManager->getBoostCharge();

    player.setHasBoost(currentBoost > 0.f);

    if (player.isUsingBoost())
    {
        currentBoost -= 25.f * dt;
        if (currentBoost < 0.f) currentBoost = 0.f;
    }

    scoreManager->setBoostCharge(currentBoost);

    view.updateCamera(dt, player.getPosition());
    updateNiveau();
    player.update(dt, getCurrentPente());
    bg.update(dt);

    if (player.getIsGrounded() && scoreManager->getSpinCount() > 0) {
        player.applyFlipBoost();
    }

    scoreManager->update(dt,
        player.getPosition().x,
        player.getRotationDeg(),
        player.getIsGrounded()
    );
}

void Game::render(sf::RenderWindow& window)
{
    view.setView(window);
    bg.draw(window);
    drawBlocNiveau(window);
    player.draw(window);

    scoreManager->draw(window, view.getView(), player.getPosition());

    if (gameOver)
    {
        window.setView(window.getDefaultView());
        window.draw(gameOverOverlay);
        window.draw(gameOverText);
    }
}

sf::Vector2f Game::getPlayerPosition() const {
    return player.getPosition();
}