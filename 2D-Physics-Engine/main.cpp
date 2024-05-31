#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "./solver.h"
#include <ctime>

void initializeBalls(std::vector<Object>& balls, int totalBalls, float radius, sf::RenderWindow& window) {
    balls.clear();
    for (int i = 0; i < totalBalls; ++i)
    {
        sf::Vector2f position;
        position.x = static_cast<float>(rand() % window.getSize().x);
        position.y = static_cast<float>(rand() % window.getSize().y);

        sf::Vector2f velocity;
        velocity.x = rand() % (200 - 100 + 1) + 100;
        velocity.y = rand() % (200 - 100 + 1) + 100;

        Object ball(radius, Vector2(position.x, position.y), Vector2(velocity.x, velocity.y));

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

    int totalBalls = 2;
    float radius = static_cast<float>(rand() % (20 - 10 + 1) + 10);

    sf::CircleShape ballShape;
    std::vector<Object> balls;
    initializeBalls(balls, totalBalls, radius, window);

    Solver solver;
    sf::Clock clock;

    bool resetValues = false;
    bool enableGravityX = false;

    enum BallSize { ExtraLarge, Large, Medium, Small, ExtraSmall };
    BallSize currentSize = Medium;
    BallSize previousSize = currentSize;
    const char* sizes[] = { "ExtraLarge", "Large", "Medium", "Small", "ExtraSmall"};

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        for (auto& ball : balls)
        {
            ball.Simulate(deltaTime);
            solver.WindowCollision(window, ball);

            for (auto& balli : balls)
            {
                if (&ball != &balli)
                {
                    solver.CircleCollision(ball, balli);
                }
            }
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
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(280, 320), ImGuiCond_Once);

        ImGui::Begin("Dynamic Controller", nullptr, ImGuiWindowFlags_NoResize);
        ImGui::Text("FPS: %.1f", 1.0f / deltaTime);

        ImGui::Text("Adjust Simulation Parameters");
        ImGui::SliderFloat("Damping", &Object::damping, 0.0f, 200.0f);
        ImGui::Checkbox("Enable Gravity X", &enableGravityX);

        if (enableGravityX) {
            ImGui::SliderFloat("Gravity X", &Object::gravity.x, -100.0f, 100.0f);
        }

        ImGui::SliderFloat("Gravity Y", &Object::gravity.y, -100.0f, 100.0f);
        ImGui::SliderFloat("Mass", &Object::mass, 0.0f, 15.0f);
        ImGui::SliderFloat("Restitution", &Object::restitution, 0.0f, 1.0f);

        ImGui::Text("Adjust Ball Parameters");

        if (ImGui::Combo("Ball Size", (int*)&currentSize, sizes, IM_ARRAYSIZE(sizes))) {
            if (currentSize != previousSize) {
                switch (currentSize)
                {
                case ExtraLarge:
                    totalBalls = 20;
                    radius = static_cast<float>(rand() % (80 - 60 + 1) + 60);
                    break;
                case Large:
                    totalBalls = 50;
                    radius = static_cast<float>(rand() % (50 - 40 + 1) + 40);
                    break;
                case Medium:
                    totalBalls = 100;
                    radius = static_cast<float>(rand() % (30 - 20 + 1) + 20);
                    break;
                case Small:
                    totalBalls = 500;
                    radius = static_cast<float>(rand() % (20 - 10 + 1) + 10);
                    break;
                case ExtraSmall:
                    totalBalls = 1000;
                    radius = static_cast<float>(rand() % (10 - 5 + 1) + 5);
                    break;
                default:
                    Medium;
                    break;
                }
                initializeBalls(balls, totalBalls, radius, window);
                previousSize = currentSize;
            }
        }

        int maxBalls;
        switch (currentSize)
        {
        case ExtraLarge:
            maxBalls = 20;
            break;
        case Large:
            maxBalls = 50;
            break;
        case Medium:
            maxBalls = 100;
            break;
        case Small:
            maxBalls = 500;
            break;
        case ExtraSmall:
            maxBalls = 1000;
            break;
        }


        ImGui::SliderInt("Total Balls", &totalBalls, 1, maxBalls);

        ImGui::BeginGroup();

        if (ImGui::Button("Reset Values"))
        {
            resetValues = true;
        }

        if (resetValues) {
            Object::damping = 0.0f;
            Object::gravity.x = 0.0f;
            Object::gravity.y = 0.0f;
            Object::mass = 5;
            Object::restitution = 1.0f;
            totalBalls = 2;
            resetValues = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Reset Simulation"))
        {
            initializeBalls(balls, totalBalls, radius, window);
        }

        ImGui::EndGroup();

        ImGui::End();

        window.clear(sf::Color(0, 0, 0));

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
