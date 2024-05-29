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

    int totalBalls = 20;

    sf::CircleShape ballShape;
    sf::Vector2f position;
    sf::Vector2f velocity;

    std::vector<Object>balls;
    for (int i = 0; i < totalBalls; ++i)
    {
        float radius = static_cast<float>(rand() % (30 - 10 + 1) + 10);
        float mass = static_cast<float>(rand() % (5 - 2 + 1) + 5);

        position.x = static_cast<float>(rand() % window.getSize().x);
        position.y = static_cast<float>(rand() % window.getSize().y);
        
        velocity.x = rand() % (200 - 100 + 100) + 100;
        velocity.y = rand() % (200 - 100 + 100) + 100;

        Object ball(radius, mass, Vector2(position.x, position.y), Vector2(velocity.x, velocity .y));

        balls.emplace_back(ball);
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        for (auto& ball : balls)
        {
            ball.Simulate(deltaTime);
            ball.WindowCollision(window);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));

        window.draw(ballShape);

        std::srand(std::time(nullptr));

        for (auto& ball : balls)
        {
            sf::Color randomColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
            ballShape.setOrigin(ball.radius, ball.radius);
            ballShape.setRadius(ball.radius);
            ballShape.setFillColor(randomColor);
            ballShape.setPosition(ball.position.x, ball.position.y);
            window.draw(ballShape);
        }

   

        window.display();
    }

    return 0;
}
