#include <SFML/Graphics.hpp>

//https://www.youtube.com/watch?v=4oh-tmxtIrA&ab_channel=IntMain
//https://dev.to/giovannicodes/sfml-2-5-1-setup-on-macos-with-clion-505m

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);

    float x  = rand() % 100;
    int y =  rand() % 100;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            x -= 0.01;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            x += 0.01;
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(window); // window is a sf::Window

        shape.setPosition(mouse.x - 50, mouse.y - 50);

        window.clear();
        window.draw(shape);
        window.display();
    }
}