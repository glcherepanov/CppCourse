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

void initAppleLeft(sf::ConvexShape &AppleLeft, sf::Vector2f &EyeLeftPos)
{
    AppleLeft.setPosition(EyeLeftPos);
    float pointCount = 200;
    sf::Vector2f Radius = {30.f, 60.f};
    AppleLeft.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            Radius.x * std::sin(angle),
            Radius.y * std::cos(angle)};
        AppleLeft.setPoint(pointNo, point);
    }
}

void initAppleRight(sf::ConvexShape &AppleRight, sf::Vector2f &EyeRightPos)
{
    AppleRight.setPosition(EyeRightPos);
    float pointCount = 200;
    sf::Vector2f Radius = {30.f, 60.f};
    AppleRight.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            Radius.x * std::sin(angle),
            Radius.y * std::cos(angle)};
        AppleRight.setPoint(pointNo, point);
    }
}

void updateleft(const sf::Vector2f &mousePosition, sf::ConvexShape &AppleLeft, sf::Vector2f &EyeLeftPos)
{
    AppleLeft.setFillColor(sf::Color(0x0, 0x0, 0x0));
    sf::Vector2f delta = mousePosition - EyeLeftPos;
    sf::Vector2f OffsetLeft;
    float ULeft = std::atan2(delta.x, delta.y);
    OffsetLeft.x = EyeLeftPos.x + 60 * sin(ULeft);
    OffsetLeft.y = EyeLeftPos.y + 120 * cos(ULeft);
    if (pow((mousePosition.x - EyeLeftPos.x), 2) / pow(60, 2) + pow((mousePosition.y - EyeLeftPos.y), 2) / pow(120, 2)
     < 1)
    {
        OffsetLeft = mousePosition;
    };
    AppleLeft.setPosition(OffsetLeft);
}

void updateright(const sf::Vector2f &mousePosition, sf::ConvexShape &AppleRight, sf::Vector2f &EyeRightPos)
{
    AppleRight.setFillColor(sf::Color(0x0, 0x0, 0x0));
    sf::Vector2f delta = mousePosition - EyeRightPos;
    sf::Vector2f OffsetRight;
    float URight = std::atan2(delta.x, delta.y);
    OffsetRight.x = EyeRightPos.x + 60 * sin(URight);
    OffsetRight.y = EyeRightPos.y + 120 * cos(URight);
    if ((pow((mousePosition.x - EyeRightPos.x), 2) / pow(60, 2) + pow((mousePosition.y - EyeRightPos.y), 2) / pow(120, 2)) <= 1)
    {
        OffsetRight = mousePosition;
    };
    AppleRight.setPosition(OffsetRight);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &EyeLeft, sf::ConvexShape &AppleLeft, sf::ConvexShape &EyeRight, sf::ConvexShape &AppleRight)
{
    window.clear();
    window.draw(EyeLeft);
    window.draw(AppleLeft);
    window.draw(EyeRight);
    window.draw(AppleRight);
    window.display();
}

void initEyeLeft(sf::ConvexShape &EyeLeft, sf::Vector2f &EyeLeftPos)
{
    EyeLeft.setPosition(EyeLeftPos);
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

void initEyeRight(sf::ConvexShape &EyeRight, sf::Vector2f &EyeRightPos)
{
    EyeRight.setPosition(EyeRightPos);
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
        sf::VideoMode({1200, 800}), "Eyes follows mouse",
        sf::Style::Default, settings);

    sf::ConvexShape EyeLeft;
    sf::ConvexShape EyeRight;
    sf::ConvexShape AppleLeft;
    sf::ConvexShape AppleRight;

    sf::Vector2f EyeLeftPos = {400, 400};
    sf::Vector2f EyeRightPos = {800, 400};

    sf::Vector2f mousePosition;

    initEyeLeft(EyeLeft, EyeLeftPos);
    initEyeRight(EyeRight, EyeRightPos);
    initAppleLeft(AppleLeft, EyeLeftPos);
    initAppleRight(AppleRight, EyeRightPos);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateleft(mousePosition, AppleLeft, EyeLeftPos);
        updateright(mousePosition, AppleRight, EyeRightPos);
        redrawFrame(window, EyeLeft, AppleLeft, EyeRight, AppleRight);
    }
}
