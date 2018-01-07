#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <cassert>

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
    sf::Vector2f position;
    int ballSize;
};

void fillPalette(sf::Color (&color)[8])
{
    color[0].r = 255;
    color[0].g = 0;
    color[0].b = 0;

    color[1].r = 0;
    color[1].g = 255;
    color[1].b = 0;

    color[2].r = 0;
    color[2].g = 0;
    color[2].b = 255;

    color[3].r = 255;
    color[3].g = 51;
    color[3].b = 102;

    color[4].r = 204;
    color[4].g = 255;
    color[4].b = 102;

    color[5].r = 153;
    color[5].g = 255;
    color[5].b = 255;

    color[6].r = 153;
    color[6].g = 0;
    color[6].b = 255;

    color[7].r = 51;
    color[7].g = 255;
    color[7].b = 51;
}

void initBalls(Ball *ball, size_t size, sf::Color *color, size_t colorSize, float width, float height)
{
    for (size_t i = 0; i < size; ++i)
    {
        ball[i].ballSize = 50;
        ball[i].ball.setRadius(ball[i].ballSize);
        ball[i].ball.setOrigin(ball[i].ballSize, ball[i].ballSize);
        float x = 0.01 * (rand() % 14000 - 7000);
        float y = 0.01 * (rand() % 14000 - 7000);
        ball[i].speed = {x, y};
        int fc = rand() % colorSize;
        int sc = rand() % colorSize;
        ball[i].ball.setFillColor(sf::Color((color[fc].r + color[sc].r) / 2, (color[fc].g + color[sc].g) / 2, (color[fc].b + color[sc].b) / 2));
    }

    ball[0].position = {100, 100};
    ball[1].position = {200, 200};
    ball[2].position = {300, 300};
    ball[3].position = {400, 400};
    ball[4].position = {500, 500};

    ball[0].ball.setPosition(ball[0].position);
    ball[1].ball.setPosition(ball[1].position);
    ball[2].ball.setPosition(ball[2].position);
    ball[3].ball.setPosition(ball[3].position);
    ball[4].ball.setPosition(ball[4].position);
}

sf::Vector2f collision(sf::Vector2f &speed, sf::Vector2f &pos, float ballSize, float width, float height)
{
    if ((pos.x + ballSize > width) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((pos.y + ballSize > height) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((pos.x - ballSize < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((pos.y - ballSize < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
    return (speed);
}

void update(Ball *ball, size_t size, float dt, int width, int height)
{
    for (size_t i = 0; i < size; ++i)
    {
        ball[i].position += ball[i].speed * dt;
        ball[i].speed = collision(ball[i].speed, ball[i].position, ball[i].ballSize, width, height);
        ball[i].ball.setPosition(ball[i].position);
    }
    for (size_t fi = 0; fi < size; ++fi)
    {
        for (size_t si = fi + 1; si < size; ++si)
        {
            if (sqrt(pow(ball[fi].position.x - ball[si].position.x, 2) + pow(ball[fi].position.y - ball[si].position.y, 2)) <= ball[fi].ballSize + ball[si].ballSize)
            {
                float dot1 = ((ball[fi].speed.x - ball[si].speed.x) * (ball[fi].position.x - ball[si].position.x) + (ball[fi].speed.y - ball[si].speed.y) * (ball[fi].position.y - ball[si].position.y)) / (pow(ball[fi].position.x - ball[si].position.x, 2) + pow(ball[fi].position.y - ball[si].position.y, 2));
                sf::Vector2f SumSpeed = ball[fi].speed + ball[si].speed;
                ball[fi].speed = {ball[fi].speed.x - dot1 * (ball[fi].position.x - ball[si].position.x), ball[fi].speed.y - dot1 * (ball[fi].position.y - ball[si].position.y)};
                ball[si].speed = SumSpeed - ball[fi].speed;
            }
        }
    }
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Ball *ball, size_t size)
{
    window.clear();
    for (size_t i = 0; i < size; ++i)
    {
        window.draw(ball[i].ball);
    }
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
        "Balls", sf::Style::Default, settings);

    sf::Clock clock;

    Ball ball[5];

    sf::Color(color[8]);

    fillPalette(color);
    initBalls(ball, std::size(ball), color, std::size(color), WINDOW_WIDTH, WINDOW_HEIGHT);

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window);
        update(ball, std::size(ball), dt, WINDOW_WIDTH, WINDOW_HEIGHT);
        redrawFrame(window, ball, std::size(ball));
    }
}