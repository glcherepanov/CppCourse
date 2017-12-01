#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void initArrow(sf::ConvexShape &arrow)
{
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    arrow.setPointCount(7);
    arrow.setPoint(0, {-40, 40});
    arrow.setPoint(1, {0, 0});
    arrow.setPoint(2, {40, 40});
    arrow.setPoint(3, {20, 40});
    arrow.setPoint(4, {20, 80});
    arrow.setPoint(5, {-20, 80});
    arrow.setPoint(6, {-20, 40});
    arrow.setOutlineColor(sf::Color(0, 0, 0));
    arrow.setOutlineThickness(2);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << " , y=" << event.y << std::endl;
    mousePosition = {float(event.x),
                     float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float dt)
{
    const sf::Vector2 delta = mousePosition - arrow.getPosition();
    float angle = atan2(delta.y, delta.x);
    angle = toDegrees(angel + M_PI / 2);
    pointer.setRotation(pointer.getRotation());

    sf::Vector2f moution = mousePosition - arrow.getPosition();
    sf::Vector2f direction = {moution.x / sqrt(moution.x * moution.x + moution.y * moution.y), moution.y / sqrt(moution.x * moution.x + moution.y * moution.y)};
    const float MaxSpeed = 20.f;
    const float speed = MaxSpeed * dt;
    arrow.setPosition(arrow.getPosition() + direction * speed);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    sf::Clock clock;

    arrow.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    initArrow(arrow);
    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, dt);
        redrawFrame(window, arrow);
    }
}