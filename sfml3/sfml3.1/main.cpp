#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

// Иницифлизирует фигуру-указатель
void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

//переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

//Обрабатывает событие MOuseMove, обновляет позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    //std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле.
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

//Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float deltaTime)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float maxAngleInSecond = 15;
    float angle = atan2(delta.y, delta.x);
    const float maxRotationSpeed = maxAngleInSecond * deltaTime;
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }
    float rotationAngle = toDegrees(angle) - pointer.getRotation();
    float rotationSpeed = std::abs(rotationAngle) * deltaTime;
    if (rotationAngle != 0)
    {
        if (rotationAngle > 0)
        {
            if ((rotationAngle - 180) > 0)
            {
                pointer.setRotation(pointer.getRotation() - std::min(rotationSpeed, maxRotationSpeed));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() + std::min(rotationSpeed, maxRotationSpeed));
            }
        }
        else
        {
            if ((rotationAngle + 180) < 0)
            {
                pointer.setRotation(pointer.getRotation() + std::min(rotationSpeed, maxRotationSpeed));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() - std::min(rotationSpeed, maxRotationSpeed));
            }
        }
    }
}

//рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &ellipse)
{
    window.clear();
    window.draw(ellipse);
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
        "Pointer follows mouse", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;
    sf::Clock clock;

    init(pointer);
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, deltaTime);
        redrawFrame(window, pointer);
    }
}