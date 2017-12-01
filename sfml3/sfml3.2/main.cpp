#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

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

void updateleft(const sf::Vector2f &mousePosition, sf::CircleShape &AppleLeft, sf::Vector2f &EyeLeftPos)
{
    sf::Vector2f delta = mousePosition - EyeLeftPos;
    sf::Vector2f OffsetLeft;
    float ULeft = std::atan2(delta.x, delta.y);
    AppleLeft.setOrigin({25, 25});
    OffsetLeft.x = EyeLeftPos.x - 25 + 60 * sin(ULeft);
    OffsetLeft.y = EyeLeftPos.y - 25 + 150 * cos(ULeft);
    AppleLeft.setPosition(OffsetLeft);
}

void updateright(const sf::Vector2f &mousePosition, sf::CircleShape &AppleRight, sf::Vector2f &EyeRightPos)
{
    sf::Vector2f delta = mousePosition - EyeRightPos;
    sf::Vector2f OffsetRight;
    float URight = std::atan2(delta.x, delta.y);
    AppleRight.setOrigin({25, 25});
    OffsetRight.x = EyeRightPos.x - 25 + 60 * sin(URight);
    OffsetRight.y = EyeRightPos.y - 25 + 150 * cos(URight);
    AppleRight.setPosition(OffsetRight);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &EyeLeft, sf::CircleShape &AppleLeft, sf::ConvexShape &EyeRight, sf::CircleShape &AppleRight)
{
    window.clear();
    window.draw(EyeLeft);
    window.draw(AppleLeft);
    window.draw(EyeRight);
    window.draw(AppleRight);
    window.display();
}

void initEyeLeft(sf::ConvexShape &EyeLeft)
{
    float pointCount = 200;
    sf::Vector2f Radius = {150.f, 250.f};
    EyeLeft.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            Radius.x * std::sin(angle),
            Radius.y * std::cos(angle)};
        EyeLeft.setPoint(pointNo, point);
    }
}

void initEyeRight(sf::ConvexShape &EyeRight)
{
    float pointCount = 200;
    sf::Vector2f Radius = {150.f, 250.f};
    EyeRight.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            Radius.x * std::sin(angle),
            Radius.y * std::cos(angle)};
        EyeRight.setPoint(pointNo, point);
    }
}
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({1200, 800}), "Eyes",
        sf::Style::Default, settings);

    sf::ConvexShape EyeLeft;
    sf::ConvexShape EyeRight;
    sf::CircleShape AppleLeft(50);
    sf::CircleShape AppleRight(50);

    sf::Vector2f EyeLeftPos = {400, 400};
    sf::Vector2f EyeRightPos = {800, 400};

    EyeLeft.setPosition(EyeLeftPos);
    EyeRight.setPosition(EyeRightPos);
    EyeRight.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    AppleLeft.setPosition(EyeLeftPos);
    AppleLeft.setFillColor(sf::Color(0x0, 0x0, 0x0));
    AppleRight.setPosition(EyeRightPos);
    AppleRight.setFillColor(sf::Color(0x0, 0x0, 0x0));

    sf::Vector2f mousePosition;

    initEyeLeft(EyeLeft);
    initEyeRight(EyeRight);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateleft(mousePosition, AppleLeft, EyeLeftPos);
        updateright(mousePosition, AppleRight, EyeRightPos);
        redrawFrame(window, EyeLeft, AppleLeft, EyeRight, AppleRight);
    }
}
