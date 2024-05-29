#include <iostream>
#include <SFML/Graphics.hpp>
#include "./vector2.h"
#include "./object.h"

int main()
{
    // Settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window
    sf::RenderWindow window;
    window.create(sf::VideoMode(500, 500), "2D Physics Engine", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::CircleShape ballShape;
    Object ball(20, 5, Vector2(100,100), Vector2(300, 300));
    ballShape.setOrigin(ball.radius, ball.radius);
    ballShape.setRadius(ball.radius);


    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        ball.Simulate(deltaTime);
        ball.WindowCollision(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));

        window.draw(ballShape);
        ballShape.setPosition(ball.position.x, ball.position.y);

        window.display();
    }

    return 0;
}
