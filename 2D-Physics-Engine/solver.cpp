#define SOLVER_H
#include "./solver.h"

void Solver::WindowCollision(sf::RenderWindow& window, Circle& circle)
{
    if (circle.position.x - circle.radius < 0 || circle.position.x + circle.radius > window.getSize().x) {
        circle.position.x = std::clamp (circle.position.x, circle.radius, window.getSize().x - circle.radius);
        circle.velocity.x = -circle.velocity.x;
    }

    if (circle.position.y - circle.radius < 0 || circle.position.y + circle.radius > window.getSize().y) {
        circle.position.y = std::clamp(circle.position.y, circle.radius, window.getSize().y - circle.radius);
        circle.velocity.y = -circle.velocity.y;
    }
}

void Solver::CircleCollision(Circle& a, Circle& b)
{
    float dx = b.position.x - a.position.x;
    float dy = b.position.y - a.position.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    float totalRadius = a.radius + b.radius;

    if (distance < totalRadius)
    {
        // Step 1: Calculate the collision angle
        float angle = std::atan2(dy, dx);

        // Step 2: Rotate the velocity vectors to the collision coordinate system
        float v1x = a.velocity.x * std::cos(angle) + a.velocity.y * std::sin(angle);
        float v1y = a.velocity.y * std::cos(angle) - a.velocity.x * std::sin(angle);
        float v2x = b.velocity.x * std::cos(angle) + b.velocity.y * std::sin(angle);
        float v2y = b.velocity.y * std::cos(angle) - b.velocity.x * std::sin(angle);

        // Step 3: Apply 1D collision equation along the x-axis
        float v1PrimeX = (v1x * (a.mass - b.mass) + 2 * b.mass * v2x) * a.restitution / (a.mass + b.mass);
        float v2PrimeX = (v2x * (b.mass - a.mass) + 2 * a.mass * v1x) * a.restitution / (a.mass + b.mass);

        // Step 4: Rotate the velocities back to the original coordinate system
        a.velocity.x = v1PrimeX * std::cos(-angle) + v1y * std::sin(-angle);
        a.velocity.y = v1y * std::cos(-angle) - v1PrimeX * std::sin(-angle);
        b.velocity.x = v2PrimeX * std::cos(-angle) + v2y * std::sin(-angle);
        b.velocity.y = v2y * std::cos(-angle) - v2PrimeX * std::sin(-angle);

        // Adjust positions to prevent sticking
        float overlap = 0.5f * (totalRadius - distance + 1.0f);  // Add a small value to avoid precision issues
        Vector2 displacement = Vector2(overlap * std::cos(angle), overlap * std::sin(angle));
        a.position = a.position.subVector(a.position, displacement.scaleVector(1.0f));
        b.position = b.position.addVector(b.position, displacement.scaleVector(1.0f));
    }
}


