#include <algorithm>
#include <cmath>

#include <SFML/Graphics.hpp>

namespace
{
constexpr unsigned int kWindowWidth = 960;
constexpr unsigned int kWindowHeight = 540;
constexpr float kPlaneHalfWidth = 18.0f;
constexpr float kPlaneSpeed = 280.0f;
constexpr float kBaseScrollSpeed = 80.0f;
constexpr float kTerrainStep = 20.0f;
constexpr float kTerrainBase = 390.0f;

float terrainHeight(float worldX)
{
    return kTerrainBase +
           std::sin(worldX * 0.010f) * 34.0f +
           std::sin(worldX * 0.024f) * 18.0f;
}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "FlightSim");
    window.setFramerateLimit(60);

    sf::RectangleShape plane(sf::Vector2f(kPlaneHalfWidth * 2.0f, 3.0f));
    plane.setFillColor(sf::Color::White);
    plane.setOrigin(kPlaneHalfWidth, 1.5f);

    float planeX = kWindowWidth * 0.5f;
    const float planeY = kWindowHeight * 0.45f;
    float terrainOffset = 0.0f;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        int horizontalInput = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            horizontalInput -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            horizontalInput += 1;
        }

        planeX += static_cast<float>(horizontalInput) * kPlaneSpeed * dt;
        planeX = std::clamp(planeX, kPlaneHalfWidth + 6.0f, kWindowWidth - kPlaneHalfWidth - 6.0f);

        terrainOffset += (kBaseScrollSpeed + std::abs(static_cast<float>(horizontalInput)) * 70.0f) * dt;

        const int segmentCount = static_cast<int>(std::ceil(kWindowWidth / kTerrainStep));
        sf::ConvexShape terrain;
        terrain.setPointCount(static_cast<std::size_t>(segmentCount) + 3U);
        terrain.setPoint(0U, sf::Vector2f(0.0f, static_cast<float>(kWindowHeight)));
        for (int i = 0; i <= segmentCount; ++i)
        {
            const float x = static_cast<float>(i) * kTerrainStep;
            const float y = terrainHeight(x + terrainOffset);
            terrain.setPoint(static_cast<std::size_t>(i) + 1U, sf::Vector2f(x, y));
        }
        terrain.setPoint(static_cast<std::size_t>(segmentCount) + 2U,
                         sf::Vector2f(static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight)));
        terrain.setFillColor(sf::Color(30, 110, 45));

        plane.setPosition(planeX, planeY);

        window.clear(sf::Color(105, 165, 255));
        window.draw(terrain);
        window.draw(plane);
        window.display();
    }

    return 0;
}
