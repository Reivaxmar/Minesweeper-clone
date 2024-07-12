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
        bool a = false;
        for (auto event = Event{}; window.pollEvent(event);) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            } else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Button::Left) {
                a = true;
            }
        }

        manager.update(window, a);
        window.clear();
        manager.draw(window);
        window.display();
    }
}