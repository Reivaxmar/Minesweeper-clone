#ifndef MANAGER_H
#define MANAGER_H

#include "Board.h"
#include "BoardDrawer.h"

class Manager {
    public:
        Manager(Vector2u windowSize);
        void update(RenderWindow& window);
        void draw(RenderWindow& window);
    private:
        int flagsRemaining;
        bool firstClick;
        void updateClicks(RenderWindow& window);
        bool lastRight;
        Board board;
        BoardDrawer drawer;
        Vector2f boardPos;
        Font font;
};

#endif