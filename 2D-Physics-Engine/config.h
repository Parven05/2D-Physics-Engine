#include <iostream>

// Game Window
struct GameWindow
{
	std::string WINDOW_TITLE = "2D Physics Engine";
	float WINDOW_HEIGHT = 800;
	float WINDOW_WIDTH = 800;
	bool VERTICAL_SYNC = true;
	float FRAME_RATE = 60;
	int ANTI_ALIASING = 8;
};

// Circle Radius
struct RandomRadius
{
	float EXTRA_LARGE_RADIUS = static_cast<float>(rand() % (80 - 60 + 1) + 60);
	float LARGE_RADIUS = static_cast<float>(rand() % (50 - 40 + 1) + 40);
	float MEDIUM_RADIUS = static_cast<float>(rand() % (30 - 20 + 1) + 20);
	float SMALL_RADIUS = static_cast<float>(rand() % (20 - 10 + 1) + 10);
	float EXTRA_SMALL_RADIUS = static_cast<float>(rand() % (10 - 5 + 1) + 5);
};

// IMGUI
// Default Values
struct DefaultValues
{
	float DAMPING = 0.0f;
	float GRAVITY_X = 0.0f;
	float GRAVITY_Y = 0.0f;
	float RESTITUTION = 1.0f;
};

// Range Values
struct RangeValues
{
	float MIN_DAMPING = 0.0f;
	float MAX_DAMPING = 200.0f;
	float MIN_GRAVITY_X = -100.0f;
	float MAX_GRAVITY_X = 100.0f;
	float MIN_GRAVITY_Y = -100.0f;
	float MAX_GRAVITY_Y = 100.0f;
	float MIN_RESTITUTION = 0.0f;
	float MAX_RESTITUTION = 1.0f;
	float MIN_TOTAL_BALLS = 2;
	float MAX_TOTAL_BALLS = 100;
};