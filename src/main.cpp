#include <SFML/Graphics.hpp>
using namespace sf;

#include "Manager.h"

int main()
{
    RenderWindow window(VideoMode(512, 712), "CMake SFML Project");
    window.setFramerateLimit(144);
    Manager manager(window.getSize());

    while (window.isOpen())
    {
        for (auto event = Event{}; window.pollEvent(event);)
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }

        manager.update(window);
        window.clear();
        manager.draw(window);
        window.display();
    }
}