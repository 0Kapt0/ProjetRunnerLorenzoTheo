#include "view.h"
View::View()
{
	view.setSize({ 1920.f, 1080.f });
	cameraSmoothness = 5.f;
	cameraOffset = { 200.f, -100.f };
}

void View::updateCamera(float dt, sf::Vector2f playerPos)
{
    // Position cible = position du joueur + offset
    cameraTarget = playerPos + cameraOffset;

    // Interpolation lissée (lerp)
    sf::Vector2f currentCenter = view.getCenter();

    currentCenter.x += (cameraTarget.x - currentCenter.x) * cameraSmoothness * dt;
    currentCenter.y += (cameraTarget.y - currentCenter.y) * cameraSmoothness * dt;

    view.setCenter(currentCenter);
}
void View::setView(sf::RenderWindow& window)
{
    window.setView(view);
}