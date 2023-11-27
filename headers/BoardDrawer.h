#ifndef BOARD_DRAWER_H
#define BOARD_DRAWER_H

#include "Board.h"

#include <SFML/Graphics.hpp>
using namespace sf;

#define MINEAND (unsigned int)32

class BoardDrawer {
    private:
        const int TILE_SIZE = 16 * 4;
        void getTexMineNum(int n);
        void getTexMines(int n);
        void getTexFace(int n);
        void getTexNum(int n);
        Texture tex;
        Sprite spr;
        void drawNotFinished(Vector2f pos, pbi info);
        void drawFinished(Vector2f pos, pbi info);
    public:
        void DrawBoard(RenderWindow& window, Board& board, Vector2f pos, bool finished);
        BoardDrawer();
};

/*
https://stackoverflow.com/questions/34458791/making-custom-types-drawable-with-sfml
*/

#endif