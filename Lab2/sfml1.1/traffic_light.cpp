#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({320, 720}), "Traficlight");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({240, 640});
    shape1.setRotation(0);
    shape1.setPosition({40, 40});
    shape1.setFillColor(sf::Color(0x69, 0x69, 0x69));
    window.draw(shape1);

    sf::CircleShape shape2(80);
    shape2.setPosition({80, 80});
    shape2.setFillColor(sf::Color(0, 255, 0));
    window.draw(shape2);

    sf::CircleShape shape3(80);
    shape3.setPosition({80, 280});
    shape3.setFillColor(sf::Color(255, 255, 0));
    window.draw(shape3);

    sf::CircleShape shape4(80);
    shape4.setPosition({80, 480});
    shape4.setFillColor(sf::Color(255, 0, 0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}