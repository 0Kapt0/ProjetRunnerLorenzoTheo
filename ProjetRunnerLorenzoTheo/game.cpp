#include "game.h"

Game::Game()
    : view(), player({ 1000.f, -20.f }), bg(1920.f, 1080.f, view)
{
    if (!uiFont.openFromFile("src/fonts/font.ttf")) {
        std::cerr << "Erreur: police introuvable\n";
    }

    speedometer = std::make_unique<Speedometer>(uiFont);
    scoreManager = std::make_unique<ScoreManager>(uiFont, sf::Vector2f(30.f, 30.f));
    scoreManager->start(player.getPosition().x);

}

Pente* Game::getCurrentPente()
{
    int pPosX = static_cast<int>(player.getPosition().x);
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
        addBlocNiveau(std::rand()%7);
    }
    if (blocNiveauList.size() > 8)
    {
        blocNiveauList.erase(blocNiveauList.begin());
    }
}

void Game::update(float dt)
{
    if (player.getIsDead())
    {
        gameOver = true;
        wantGameOver = true;
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
    updatePiece();
    bg.update(dt, player.getSpeed());

    if (player.getIsGrounded() && scoreManager->getSpinCount() > 0) {
        player.applyFlipBoost();
    }

    scoreManager->update(dt,
        player.getPosition().x,
        player.getRotationDeg(),
        player.getIsGrounded()
    );
    speedometer->setSpeedText(player.getSpeed());
}

void Game::render(sf::RenderWindow& window)
{
    view.setView(window);
    bg.draw(window);
    drawBlocNiveau(window);
    player.draw(window);
    speedometer->draw(window, view.getView(), player.getPosition());

    scoreManager->draw(window, view.getView(), player.getPosition());
}

sf::Vector2f Game::getPlayerPosition() const {
    return player.getPosition();
}

void Game::updatePiece()
{
    for (auto& bloc: blocNiveauList)
    {
        auto& bonusList = bloc.getBonusList();

        bonusList.erase(
            std::remove_if(
                bonusList.begin(),
                bonusList.end(),
                [&](std::unique_ptr<Bonus>& piece)
                {
                    sf::Vector2f diff = player.getPosition() - piece->getPosition();
                    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

                    if (distance < pickupRadius)
                    {
                        scoreManager->addScore(100);
                        return true;
                    }
                    return false;
                }
            ),
            bonusList.end()
        );
    }
}