#include <SFML/Graphics.hpp>
using namespace sf;

#include "Manager.h"

int main()
{
    // Creating an un-resizable window
    RenderWindow window(VideoMode(512, 712), "CMake SFML Project", Style::Titlebar | Style::Close);
    // More or less in the middle
    window.setPosition(Vector2i(704, 160));
    window.setFramerateLimit(144);
    // And create the manager
    Manager manager(window.getSize());

    // Main loop
    while (window.isOpen()) {
        // Variable for checking when left mouse button is pressed (pressed not mantained pressed)
        bool oneLeft = false;
        for (auto event = Event{}; window.pollEvent(event);) {
            // Escape for exiting
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            } else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Button::Left) {
                oneLeft = true;
            }
        }
        
        // Update the manager
        manager.update(window, oneLeft);
        window.clear();
        // And draw everything to the screen
        manager.draw(window);
        window.display();
    }
}