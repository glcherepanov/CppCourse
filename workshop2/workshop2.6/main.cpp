#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
    sf::Vector2f position;
    int ballSize;
    float timer;
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

void createBall(Ball &ball, int ballSize, sf::Color *color, size_t colorSize, sf::Vector2f mousePosition)
{
    ball.ballSize = ballSize;
    ball.ball.setRadius(ballSize);
    ball.ball.setOrigin(ballSize, ballSize);
    float x = 0.01 * (rand() % 14000 - 7000);
    float y = 0.01 * (rand() % 14000 - 7000);
    ball.speed = {x, y};
    int fc = rand() % colorSize;
    int sc = rand() % colorSize;
    ball.ball.setFillColor(sf::Color((color[fc].r + color[sc].r) / 2, (color[fc].g + color[sc].g) / 2, (color[fc].b + color[sc].b) / 2));
    ball.position = mousePosition;
    ball.ball.setPosition(ball.position);
    ball.timer = 10;
}

void initBalls(std::vector<Ball> &balls, sf::Color *color, size_t colorSize, sf::Vector2f &mousePosition)
{
    bool collisionBalls = false;
    int ballSize = rand() % 20 + 30;
    Ball NewBall;
    for (size_t i = 0; i < balls.size(); ++i)
    {
        if ((sqrt(pow(balls[i].position.x - mousePosition.x, 2) + pow(balls[i].position.y - mousePosition.y, 2)) <= balls[i].ballSize + ballSize) && collisionBalls == false)
        {
            collisionBalls = true;
        }
    }
    if (collisionBalls == false)
    {
        createBall(NewBall, ballSize, color, colorSize, mousePosition);
        balls.emplace_back(NewBall);
    }
    std::cout << "collisionBalls:" << collisionBalls << std::endl;
}

sf::Vector2f collisionWalls(sf::Vector2f &speed, sf::Vector2f &pos, float BallSize, float width, float height)
{
    if ((pos.x + BallSize > width) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((pos.y + BallSize > height) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((pos.x - BallSize < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((pos.y - BallSize < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
    return (speed);
}

void update(std::vector<Ball> &balls, float dt, int width, int height)
{
    for (size_t i = 0; i < balls.size(); ++i)
    {
        balls[i].position += balls[i].speed * dt;
        balls[i].speed = collisionWalls(balls[i].speed, balls[i].position, balls[i].ballSize, width, height);
        balls[i].ball.setPosition(balls[i].position);
        balls[i].timer = balls[i].timer - dt;
    }
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
        {
            if (sqrt(pow(balls[fi].position.x - balls[si].position.x, 2) + pow(balls[fi].position.y - balls[si].position.y, 2)) <= balls[fi].ballSize + balls[si].ballSize)
            {
                float dot1 = ((balls[fi].speed.x - balls[si].speed.x) * (balls[fi].position.x - balls[si].position.x) + (balls[fi].speed.y - balls[si].speed.y) * (balls[fi].position.y - balls[si].position.y)) / (pow(balls[fi].position.x - balls[si].position.x, 2) + pow(balls[fi].position.y - balls[si].position.y, 2));
                sf::Vector2f SumSpeed = balls[fi].speed + balls[si].speed;
                balls[fi].speed = {balls[fi].speed.x - dot1 * (balls[fi].position.x - balls[si].position.x), balls[fi].speed.y - dot1 * (balls[fi].position.y - balls[si].position.y)};
                balls[si].speed = SumSpeed - balls[fi].speed;
            }
        }
    }
}

void removeDeathBalls(std::vector<Ball> &balls)
{
    auto removeBalls = [&](Ball balls) -> bool {
        return balls.timer < 0;
    };
    auto iterator = std::remove_if(balls.begin(), balls.end(), removeBalls);
    balls.erase(iterator, balls.end());
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, std::vector<Ball> &balls, sf::Color *color, size_t colorSize)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            mousePosition = {float(event.mouseButton.x), float(event.mouseButton.y)};
            std::cout << mousePosition.x << "; " << mousePosition.y << std::endl;
            initBalls(balls, color, colorSize, mousePosition);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (size_t i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Balls", sf::Style::Default, settings);

    sf::Clock clock;
    std::vector<Ball> balls(5, Ball());
    sf::Vector2f mousePosition;

    sf::Color(color[8]);
    fillPalette(color);

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition, balls, color, std::size(color));
        removeDeathBalls(balls);
        update(balls, dt, WINDOW_WIDTH, WINDOW_HEIGHT);
        redrawFrame(window, balls);
    }
}