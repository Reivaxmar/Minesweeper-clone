#include "BoardDrawer.h"

BoardDrawer::BoardDrawer() {
    tex.loadFromFile("../assets/Minesweeper.png");
    spr.setTexture(tex);
    spr.setScale(4, 4);
    getTexMines(0);
}

void BoardDrawer::DrawBoard(RenderWindow &window, Board& board, Vector2f pos)
{
    for(int x = 0; x < board.getSize().x; x++) {
        for(int y = 0; y < board.getSize().y; y++) {
            Vector2f tilePos = pos;
            tilePos += Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            int adjMines = board.generatedmap[x][y].second;
            if(!board.generatedmap[x][y].first) {
                if((board.generatedmap[x][y].second & MINEAND) == 0) {
                    getTexMines(0);
                } else {
                    getTexMines(2);
                }
                spr.setPosition(tilePos);
                window.draw(spr);
                continue;
            }
            if(adjMines == 0)
                getTexMines(1);
            else if(adjMines == 9)
                getTexMines(5);
            else
                getTexMineNum(adjMines - 1);
            spr.setPosition(tilePos);
            window.draw(spr);
        }
    }
}


void BoardDrawer::getTexMineNum(int n)
{
    spr.setTextureRect(IntRect(Vector2i(n * 17, 66), Vector2i(16, 16)));
}

void BoardDrawer::getTexMines(int n)
{
    spr.setTextureRect(IntRect(Vector2i(n * 17, 49), Vector2i(16, 16)));
}

void BoardDrawer::getTexFace(int n)
{
}

void BoardDrawer::getTexNum(int n)
{
}

