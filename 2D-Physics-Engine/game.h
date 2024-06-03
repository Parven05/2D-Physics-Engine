#include "sandbox.h"
#include "config.h"

class Game
{
public:
    Game(float dt);
    void InitializeImGui();
    void HandleEvents();
    void UpdateImGui();
    void Start();
    void RenderImGui();

private:
    bool enableGravityX = false;
    int totalBalls = 2;
    float deltaTime;
    std::unique_ptr<sf::RenderWindow> CreateWindow(const GameWindow& win);
    std::unique_ptr<sf::RenderWindow> gameWindow;
    sf::Clock clock; 

private:
    Solver solver;
    Sandbox sandbox;
    GameWindow window;
    RandomRadius random;
    RangeValues range;
};

