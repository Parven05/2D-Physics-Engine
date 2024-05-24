// Library
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

class Circle
{
private:

    const float speed = 30;
    const float mass = 0.5;
    const float time = 30;

public:

    sf::CircleShape circle;

    Circle(float radius, sf::Vector2f position)
    {
        circle.setRadius(radius);
        circle.setPosition(position);
    }

    sf::Vector2f GetPosition()
    {
        return circle.getPosition();
    }

    void ReadPosition() const
    {
        sf::Vector2f position = circle.getPosition();
        std::cout << position.x << position.y << std::endl;
    }

    float GetRadius()
    {
        return circle.getRadius();
    }

    sf::Vector2f Velocity(sf::Vector2f direction)
    {
        sf::Vector2f velocity = speed * direction / time;
        circle.move(velocity);
        return velocity;
    }

    sf::Vector2f Momentum(sf::Vector2f direction)
    {
        sf::Vector2f momentum = mass * Velocity(direction);
        circle.move(momentum);
        return momentum;
    }

    sf::Color SetColor(sf::Color color)
    {
        circle.setFillColor(color);
        return color;
    }

    void DrawCircle(sf::RenderWindow& window) const
    {
        window.draw(circle);
    }

};

class CircleCollision
{
public:
    float GetDistance(Circle A, Circle B);
    float TotalRadius(Circle A, Circle B);
    bool WindowCollision(Circle x);

};

float CircleCollision::GetDistance(Circle A, Circle B)
{
    float distance = sqrt(pow(B.GetPosition().x - A.GetPosition().x, 2) + pow(B.GetPosition().y - A.GetPosition().y, 2));
    return distance;
}

float CircleCollision::TotalRadius(Circle A, Circle B)
{
    float totalRadius = A.GetRadius() + B.GetRadius();
    return totalRadius;
}
bool CircleCollision::WindowCollision(Circle i)
{
    if (i.GetPosition().x + i.GetRadius() > 500 || //Width - RIGHT
        i.GetPosition().x - i.GetRadius() < 0 ||   //0 - LEFT
        i.GetPosition().y + i.GetRadius() > 500 || //Height - TOP
        i.GetPosition().y - i.GetRadius() < 0)     //0 - BOTTOM
    {
        return true;
    }

    return false;
}

int main()
{
    // Settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window
    sf::RenderWindow window;
    window.create(sf::VideoMode(500, 500), "Click Game", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    ///----------------------------------------------------------------------------------------------------

    // First Ball
    Circle ball_A(20, sf::Vector2f(20, 20));
    float ball_A_Radius = ball_A.GetRadius();
    sf::Vector2f ball_A_Position = ball_A.GetPosition();

    // Second Ball
    Circle ball_B(20, sf::Vector2f(40, 40));
    float ball_B_Radius = ball_B.GetRadius();
    sf::Vector2f ball_B_Position = ball_B.GetPosition();

    while (window.isOpen())
    {

        ball_A.Velocity(sf::Vector2f(1, 0));
        ball_B.Velocity(sf::Vector2f(0, 1));

        //ball_A.Momentum(x);
        //ball_B.Momentum(y);

        CircleCollision collision;
        //Circle Collision each other
        if (collision.GetDistance(ball_A, ball_B) < collision.TotalRadius(ball_A, ball_B))
        {
            std::cout << "Collision" << std::endl;
        }
        else
        {
            std::cout << "Not Collision" << std::endl;
        }
        //Circle Collision windows
        if (collision.WindowCollision(ball_A) || collision.WindowCollision(ball_B) == true)
        {
            std::cout << "Window Detected" << std::endl;
            sf::Color color;

            ball_A.SetColor(color.Cyan);
            ball_B.SetColor(color.Cyan);

        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));

        ball_A.DrawCircle(window);
        ball_B.DrawCircle(window);

        window.display();
    }
    return 0;
}