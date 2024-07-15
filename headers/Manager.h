#ifndef MANAGER_H
#define MANAGER_H

#include "Board.h"
#include "BoardDrawer.h"

const Vector2u mapSize = Vector2u(8, 8);
const int mapMines = 10;

class Manager {
    public:
        Manager(Vector2u windowSize);
        void update(RenderWindow& window, bool a);
        void draw(RenderWindow& window);
    private:
        int flagsRemaining;
        bool firstClick;
        void updateClicks(RenderWindow& window);
        bool lastRight;
        bool finished;
        bool win;
        Board board;
        BoardDrawer drawer;
        Vector2f boardPos;
        Font font;
        Clock clock;
        long double winTime;
        bool leftPressed;
};

#endif