#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

//структура курсора
struct Pointer
{
    sf::ConvexShape arrow;
    sf::Vector2f position;
    float speed;
};

//инициализация курсора
void initPointer(Pointer &pointer, float width, float height)
{
    pointer.arrow.setPosition({400, 300});
    pointer.arrow.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    pointer.arrow.setPointCount(7);
    pointer.arrow.setPoint(0, {0, 60});
    pointer.arrow.setPoint(1, {60, 0});
    pointer.arrow.setPoint(2, {0, -60});
    pointer.arrow.setPoint(3, {0, -30});
    pointer.arrow.setPoint(4, {-60, -30});
    pointer.arrow.setPoint(5, {-60, 30});
    pointer.arrow.setPoint(6, {0, 30});
    pointer.arrow.setOutlineColor(sf::Color(0, 0, 0));
    pointer.arrow.setOutlineThickness(2);

    pointer.speed = 20.f;
    pointer.position = {width / 2, height / 2};
    pointer.arrow.setPosition(pointer.position);
}

//Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180 / M_PI);
}

//обновление курсора
void update(Pointer &pointer, float deltaTime, sf::Vector2f &mousePosition)
{
    pointer.position = pointer.arrow.getPosition();
    if (sqrt(pow(pointer.position.x - mousePosition.x, 2) + pow(pointer.position.y - mousePosition.y, 2)) >= 1)
    {
        const sf::Vector2f delta = mousePosition - pointer.position;
        const float maxAngleInSecond = 90;
        float angle = atan2(delta.y, delta.x);
        const float maxRotationSpeed = maxAngleInSecond * deltaTime;
        if (angle < 0)
        {
            angle += 2 * M_PI;
        }
        float rotationAngle = toDegrees(angle) - pointer.arrow.getRotation();
        float rotationSpeed = std::abs(rotationAngle) * deltaTime;
        if (rotationAngle != 0)
        {
            if (rotationAngle > 0)
            {
                if ((rotationAngle - 180) > 0)
                {
                    pointer.arrow.setRotation(pointer.arrow.getRotation() - std::min(rotationSpeed, maxRotationSpeed));
                }
                else
                {
                    pointer.arrow.setRotation(pointer.arrow.getRotation() + std::min(rotationSpeed, maxRotationSpeed));
                }
            }
            else
            {
                if ((rotationAngle + 180) < 0)
                {
                    pointer.arrow.setRotation(pointer.arrow.getRotation() + std::min(rotationSpeed, maxRotationSpeed));
                }
                else
                {
                    pointer.arrow.setRotation(pointer.arrow.getRotation() - std::min(rotationSpeed, maxRotationSpeed));
                }
            }
        }

        sf::Vector2f moution = mousePosition - pointer.position;
        sf::Vector2f direction = {moution.x / sqrt(pow(moution.x, 2) + pow(moution.y, 2)), moution.y / sqrt(pow(moution.x, 2) + pow(moution.y, 2))};
        const float speed = pointer.speed * deltaTime;
        pointer.arrow.setPosition(pointer.position + direction * speed);
    }
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << " , y=" << event.y << std::endl;
    mousePosition = {float(event.x),
                     float(event.y)};
}

//опрашивает и обрабатывает доступные в цикле события
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

//Рисует и выводит один кадр
void redrawFrame(Pointer &pointer, sf::RenderWindow &window)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer.arrow);
    window.display();
}

int main()
{
    constexpr unsigned WindowWidth = 800;
    constexpr unsigned WindowHeight = 600;

    sf::RenderWindow window(sf::VideoMode({WindowWidth, WindowHeight}), "arrow folllows mouse", sf::Style::Default);

    Pointer pointer;
    initPointer(pointer, WindowWidth, WindowHeight);

    sf::Clock clock;
    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(pointer, deltaTime, mousePosition);
        redrawFrame(pointer, window);
    }
}