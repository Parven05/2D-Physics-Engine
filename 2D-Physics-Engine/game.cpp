#include "game.h"
#include "imgui.h"
#include "imgui-SFML.h"

Game::Game(float dt) : deltaTime(dt) {}

std::unique_ptr<sf::RenderWindow> Game::CreateWindow(const GameWindow& win)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = win.ANTI_ALIASING;

    auto window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(static_cast<int>(win.WINDOW_WIDTH), static_cast<int>(win.WINDOW_HEIGHT)),
        win.WINDOW_TITLE,
        sf::Style::Titlebar | sf::Style::Close,
        settings
    );

    window->setVerticalSyncEnabled(win.VERTICAL_SYNC);
    window->setFramerateLimit(static_cast<unsigned int>(win.FRAME_RATE));

    return window;
}

void Game::InitializeImGui()
{
    ImGui::SFML::Init(*gameWindow);
}

void Game::HandleEvents()
{
    sf::Event event;
    while (gameWindow->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
            gameWindow->close();
    }
}

void Game::UpdateImGui()
{
    ImGui::SFML::Update(*gameWindow, sf::milliseconds(static_cast<int>(deltaTime * 1000)));
}

void Game::RenderImGui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(280, 320), ImGuiCond_Once);
    ImGui::Begin("Dynamic Controller", nullptr, ImGuiWindowFlags_NoResize);

    // Display FPS
    ImGui::Text("FPS: %.1f", 1.0f / deltaTime);

    // Simulation Parameters
    ImGui::Text("Adjust Simulation Parameters");
    ImGui::SliderFloat("Damping", &Shape::damping, range.MIN_DAMPING, range.MAX_DAMPING);
    ImGui::Checkbox("Enable Gravity X", &enableGravityX);

    if (enableGravityX) {
        ImGui::SliderFloat("Gravity X", &Shape::gravity.x, range.MIN_GRAVITY_X, range.MAX_GRAVITY_X);
    }

    ImGui::SliderFloat("Gravity Y", &Shape::gravity.y, range.MIN_GRAVITY_Y, range.MAX_GRAVITY_Y);
    ImGui::SliderFloat("Restitution", &Shape::restitution, range.MIN_RESTITUTION, range.MAX_RESTITUTION);

    // Adjust total number of balls
    ImGui::SliderInt("Total Balls", &totalBalls, 2, 10000);

    if (ImGui::Button("Reset Simulation"))
    {
        sandbox.InitializeBalls(totalBalls, random.EXTRA_SMALL_RADIUS, *gameWindow);
    }

    ImGui::End();
}

void Game::Start()
{
    gameWindow = CreateWindow(window);
    InitializeImGui();
    sandbox.InitializeBalls(totalBalls, random.EXTRA_SMALL_RADIUS, *gameWindow);

    while (gameWindow->isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        HandleEvents();
        UpdateImGui();

        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        sandbox.Simulate(solver, *gameWindow, deltaTime);

        gameWindow->clear();
        sandbox.DrawBalls(*gameWindow);
        RenderImGui();
        ImGui::SFML::Render(*gameWindow);
        gameWindow->display();
    }

    ImGui::SFML::Shutdown();
}