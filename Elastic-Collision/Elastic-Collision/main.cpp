// Library
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <algorithm>

class Circle
{
private:

    const float speed = 80;
    const float mass = 0.5;
    const float time = 30;

public:

    sf::CircleShape circle;
    sf::Vector2f velocity;

    Circle(float radius, sf::Vector2f position, sf::Vector2f initialVelocity)
    {
        circle.setRadius(radius);
        circle.setPosition(position);
        circle.setOrigin(radius, radius);
        this->velocity = initialVelocity;
    }

    sf::Vector2f GetPosition() const
    {
        return circle.getPosition();
    }

    sf::Vector2f GetVelocity() const
    {
        return velocity;
    }

    float GetRadius() const
    {
        return circle.getRadius();
    }

    float GetMass() const
    {
        return mass;
    }

    void SetVelocity(sf::Vector2f newVelocity)
    {
        velocity = newVelocity;
    }

    void UpdatePosition()
    {
        circle.move(velocity * speed / time);
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
    bool WindowCollision(Circle& x, sf::RenderWindow& window) const;
    bool ElasticCollision(CircleCollision& c, Circle& a, Circle& b) const;
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

bool CircleCollision::WindowCollision(Circle& i, sf::RenderWindow& window) const
{
    sf::Vector2f position = i.GetPosition();
    float radius = i.GetRadius();
    sf::Vector2f velocity = i.GetVelocity();

    bool collision = false;

    if (position.x - radius < 0 || position.x + radius > window.getSize().x)
    {
        velocity.x = -velocity.x;
        collision = true;
    }
    if (position.y - radius < 0 || position.y + radius > window.getSize().y)
    {
        velocity.y = -velocity.y;
        collision = true;
    }
    
    if (collision)
    {
        i.SetVelocity(velocity);
    }

    return collision;
}

bool CircleCollision::ElasticCollision(CircleCollision& c, Circle& a, Circle& b) const
{
    float distance = c.GetDistance(a, b);
    float totalRadius = c.TotalRadius(a,b);

    if (distance < totalRadius)
    {
        // Relative Velocity
        sf::Vector2f relativeVelocity = b.GetVelocity() - a.GetVelocity();

        // Normal Vector
        sf::Vector2 normal = (b.GetPosition() - a.GetPosition()) / distance;

        // Impulse along normal 
        float impluse = 2.0f * (relativeVelocity.x * normal.x + relativeVelocity.y * normal.y) / (a.GetMass() + b.GetMass());

        // Update Velocity
        a.SetVelocity(a.GetVelocity() + impluse * b.GetMass() * normal);
        b.SetVelocity(b.GetVelocity() - impluse * a.GetMass() * normal);

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

    window.create(sf::VideoMode(800, 800), "Click Game", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    ///----------------------------------------------------------------------------------------------------

    int totalBalls = 100;

    std::vector<Circle> balls;
    for (int i = 0; i < totalBalls; i++)
    {
        float radius = static_cast<float>(rand() % (20 - 10 + 1) + 10);
        sf::Vector2f position;
        position.x = static_cast<float>(rand() % window.getSize().x);
        position.y = static_cast<float>(rand() % window.getSize().y);
        sf::Vector2f velocity;
        velocity.x = rand() % (2 - 1 + 1) + 1;
        velocity.y = rand() % (2 - 1 + 1) + 1;
        balls.emplace_back(radius, position, velocity);

    }

    while (window.isOpen())
    {

       for (auto& ball : balls)
       {
            ball.UpdatePosition();
       }

       CircleCollision collision;

        for (auto& ball1 : balls)
       {
           for (auto& ball2 : balls)
           {
               if (&ball1 != &ball2)
               {
                   collision.ElasticCollision(collision, ball1, ball2);
               };
           }
       }
      
        // Circle Collision windows
        for (auto& ball : balls)
        {
            if (collision.WindowCollision(ball, window))
            {
                std::cout << "Window Detected" << std::endl;
            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));

        std::srand(std::time(nullptr));

        for (auto& ball : balls)
        {
            sf::Color randomColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
            ball.SetColor(randomColor);
            ball.DrawCircle(window);

        }
        window.display();
    }
    return 0;
}