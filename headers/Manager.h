#ifndef MANAGER_H
#define MANAGER_H

#include "Board.h"
#include "BoardDrawer.h"

class Manager {
    public:
        Manager();
        void update();
        void draw(RenderWindow& window);
    private:
        Board board;
        BoardDrawer drawer;
};

#endif