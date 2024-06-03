#include "sandbox.h"

void Sandbox::InitializeBalls(int totalBalls, float radius, sf::RenderWindow& window) 
{
    balls.clear();
    for (int i = 0; i < totalBalls; ++i)
    {
        position.x = static_cast<float>(rand() % window.getSize().x);
        position.y = static_cast<float>(rand() % window.getSize().y);

        velocity.x = rand() % (200 - 100 + 1) + 100;
        velocity.y = rand() % (200 - 100 + 1) + 100;

        Circle ball(radius, Vector2(position.x, position.y), Vector2(velocity.x, velocity.y));

        balls.emplace_back(ball);
    }
}

void Sandbox::Simulate(Solver& solver, sf::RenderWindow& window, float dt)
{
    for (auto& ball : balls)
    {
        ball.Move(dt);
        solver.WindowCollision(window, ball);

        for (auto& balli : balls)
        {
            if (&ball != &balli)
            {
                solver.CircleCollision(ball, balli);
            }
        }
    }
}

void Sandbox::DrawBalls(sf::RenderWindow& window)
{
    for (auto& ball : balls)
    {
        sf::Color randomColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
        ballShape.setOrigin(ball.radius, ball.radius);
        ballShape.setRadius(ball.radius);
        ballShape.setFillColor(randomColor);
        ballShape.setPosition(ball.position.x, ball.position.y);
        window.draw(ballShape);
    }
}