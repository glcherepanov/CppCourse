#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::ConvexShape roof1;
    roof1.setFillColor(sf::Color(139, 137, 112));
    roof1.setPosition({40, 440});
    roof1.setPointCount(4);
    roof1.setPoint(0, {0, 0});
    roof1.setPoint(1, {+160, -160});
    roof1.setPoint(2, {+600, -160});
    roof1.setPoint(3, {+600, -0});

    sf::ConvexShape roof2;
    roof2.setFillColor(sf::Color(139, 137, 112));
    roof2.setPosition(640, 280);
    roof2.setPointCount(3);
    roof2.setPoint(0, {0, 0});
    roof2.setPoint(1, {0, +160});
    roof2.setPoint(2, {+200, +160});

    sf::RectangleShape wall;
    wall.setSize({480, 320});
    wall.setRotation(0);
    wall.setPosition({200, 440});
    wall.setFillColor(sf::Color(255, 248, 220));

    sf::RectangleShape door;
    door.setSize({120, 200});
    door.setRotation(0);
    door.setPosition({280, 560});
    door.setFillColor(sf::Color(205, 179, 139));

    sf::RectangleShape tube1;
    tube1.setSize({80, 80});
    tube1.setRotation(0);
    tube1.setPosition({520, 240});
    tube1.setFillColor(sf::Color(165, 42, 42));

    sf::RectangleShape tube2;
    tube2.setSize({160, 40});
    tube2.setRotation(0);
    tube2.setPosition({480, 200});
    tube2.setFillColor(sf::Color(165, 42, 42));

    sf::CircleShape smoke1(40);
    smoke1.setPosition({520, 160});
    smoke1.setFillColor(sf::Color(255, 255, 255));

    sf::CircleShape smoke2(45);
    smoke2.setPosition({560, 120});
    smoke2.setFillColor(sf::Color(255, 255, 255));

    sf::CircleShape smoke3(50);
    smoke3.setPosition({600, 80});
    smoke3.setFillColor(sf::Color(255, 255, 255));

    sf::CircleShape smoke4(55);
    smoke4.setPosition({640, 40});
    smoke4.setFillColor(sf::Color(255, 255, 255));

    sf::RenderWindow window(sf::VideoMode({880, 800}), "House");
    window.clear();
    window.draw(roof1);
    window.draw(roof2);
    window.draw(wall);
    window.draw(door);
    window.draw(smoke1);
    window.draw(smoke2);
    window.draw(smoke3);
    window.draw(smoke4);
    window.draw(tube1);
    window.draw(tube2);
    window.display();

    sf::sleep(sf::seconds(5));
}