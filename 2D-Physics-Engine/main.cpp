#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define VECTOR2_H
#define PARTICLE_H
#include "./vector2.h";
#include "./particle.h"

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


    Vector2 initialPos = Vector2(100,200);
    Vector2 velocity = Vector2(0,1);
    Particle particle(initialPos, velocity);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));

        particle.Draw(window);

        window.display();
    }

    return 0;
}
