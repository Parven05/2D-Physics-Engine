#define SANDBOX_H
#include "./sandbox.h"

sf::RenderWindow Window()
{
    //settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(800, 800), "2D Physics Engine", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    return window;
}*/

void Sandbox::Start()
{
	
   // ImGui::SFML::Init(window);
}

void Sandbox::Update()
{

}