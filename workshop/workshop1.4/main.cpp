#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void initCat_Pointer(sf::Texture &textureCat, sf::Sprite &cat, sf::Texture &texturePoint, sf::Sprite &pointer)
{
    textureCat.loadFromFile("../img/cat.png");
    cat.setTexture(textureCat);
    cat.setPosition(400, 400);
    cat.setOrigin(34, 14);
    texturePoint.loadFromFile("../img/red_pointer.png");
    pointer.setTexture(texturePoint);
    pointer.setOrigin(16, 16);
}

void update(sf::Sprite &cat, sf::Sprite &pointer, sf::Vector2f &mousePosition, float dt)
{
    pointer.setPosition(mousePosition);
    const sf::Vector2 delta = mousePosition - cat.getPosition();
    sf::Vector2f moution = mousePosition - cat.getPosition();
    sf::Vector2f direction = {moution.x / sqrt(moution.x * moution.x + moution.y * moution.y), moution.y / sqrt(moution.x * moution.x + moution.y * moution.y)};
    const float MaxSpeed = 20.f;
    const float speed = MaxSpeed * dt;
    sf::Vector2f catPos = cat.getPosition();
    sf::Vector2f pointerPos = pointer.getPosition();
    if (sqrt(pow(pointerPos.x - catPos.x, 2) + pow(pointerPos.y - catPos.y, 2)) >= 1)
    {
        if (pointerPos.x - catPos.x > 0)
        {
            cat.setScale(1, 1);
            cat.setPosition(cat.getPosition() + direction * speed);
        }
        if (pointerPos.x - catPos.x < 0)
        {
            cat.setScale(-1, 1);
            cat.setPosition(cat.getPosition() + direction * speed);
        }
    }
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

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &pointer)
{
    window.clear();
    window.draw(cat);
    window.draw(pointer);
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
        "cat folllows pointer", sf::Style::Default, settings);
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));

    sf::Vector2f mousePosition;

    sf::Texture textureCat;
    sf::Texture texturePoint;

    sf::Sprite cat;
    sf::Sprite pointer;

    sf::Clock clock;

    initCat_Pointer(textureCat, cat, texturePoint, pointer);
    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(cat, pointer, mousePosition, dt);
        redrawFrame(window, cat, pointer);
    }
}