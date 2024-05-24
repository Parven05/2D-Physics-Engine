// Library
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

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

    void SetVelocity(sf::Vector2f newVelocity)
    {
        velocity = newVelocity;
    }

    void UpdatePosition()
    {
        circle.move(velocity * speed / time);
    }

    float GetRadius()
    {
        return circle.getRadius();
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
    float distance = c.GetDistance(a,b);
    float totalRadius = c.TotalRadius(a,b);
    sf::Vector2f velocityA = a.GetVelocity();
    sf::Vector2f velocityB = b.GetVelocity();

    bool collision = true;

    if (distance < totalRadius)
    {
        // Ball A
        velocityA.x = -velocityA.x;
        velocityA.y = -velocityA.y;

        // Ball B
        velocityB.x = -velocityB.x;
        velocityB.y = -velocityB.y;

        collision = true;   
    }

    if (collision)
    {
        a.SetVelocity(velocityA);
        b.SetVelocity(velocityB);
    }

    return collision;
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
    
    Circle ball_A(20, sf::Vector2f(100,100), sf::Vector2f(1,0));          // First Ball
    Circle ball_B(20, sf::Vector2f(100, 300), sf::Vector2f(0, 1));        // Second Ball
    

    while (window.isOpen())
    {
        ball_A.UpdatePosition();
        ball_B.UpdatePosition();

        CircleCollision collision;
        //Circle Collision each other
        if (collision.ElasticCollision(collision, ball_A, ball_B))
        {
            sf::Color color;
            ball_A.SetColor(color.Yellow);
            ball_B.SetColor(color.Green);
        }

        //Circle Collision windows
        if (collision.WindowCollision(ball_A, window) || collision.WindowCollision(ball_B, window))
        {
            std::cout << "Window Detected" << std::endl;
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