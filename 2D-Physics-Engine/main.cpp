#include <iostream>
#include <SFML/Graphics.hpp>
#include "./vector2.h"
#include "./object.h"
#include "imgui.h"
#include "imgui-SFML.h"

void initializeBalls(std::vector<Object>& balls, int totalBalls, sf::RenderWindow& window) {
    balls.clear();
    for (int i = 0; i < totalBalls; ++i)
    {
        float radius = static_cast<float>(rand() % (30 - 10 + 1) + 10);
        float mass = static_cast<float>(rand() % (5 - 2 + 1) + 5);

        sf::Vector2f position;
        position.x = static_cast<float>(rand() % window.getSize().x);
        position.y = static_cast<float>(rand() % window.getSize().y);

        sf::Vector2f velocity;
        velocity.x = rand() % (200 - 100 + 1) + 100;
        velocity.y = rand() % (200 - 100 + 1) + 100;

        Object ball(radius, mass, Vector2(position.x, position.y), Vector2(velocity.x, velocity.y));

        balls.emplace_back(ball);
    }
}

int main()
{
    // Settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 800), "2D Physics Engine", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);


    int totalBalls = 20;

    sf::CircleShape ballShape;
    sf::Vector2f position;
    sf::Vector2f velocity;

    std::vector<Object>balls;
    initializeBalls(balls, totalBalls, window);

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
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, sf::milliseconds(static_cast<int>(deltaTime * 1000)));

        // IMGUI window;
        ImGui::SetNextWindowPos(ImVec2(0,0), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(280, 180), ImGuiCond_Once);
        ImGui::Begin("Dynamic Controller", nullptr, ImGuiWindowFlags_NoResize);
        ImGui::Text("FPS: %.1f", 1.0f / deltaTime);
        ImGui::Text("Adjust Simulation Parameters");
        ImGui::SliderFloat("Damping", &Object::damping, 0.0f, 200.0f);
        ImGui::SliderFloat("Gravity Y", &Object::gravity.y, 0.0f, 400.0f);
        ImGui::Spacing();
        ImGui::SliderInt("Balls", &totalBalls, 1, 200);
        if (ImGui::Button("Restart Simulation"))
        {
            initializeBalls(balls, totalBalls, window);
        }
        ImGui::End();

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

   
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
