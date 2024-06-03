#include "game.h"

int main()
{
    sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();
    Game game(deltaTime);
    game.Start();

}
