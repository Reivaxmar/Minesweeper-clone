#include "BoardDrawer.h"

BoardDrawer::BoardDrawer() {
    tex.loadFromFile("../assets/Minesweeper.png");
    spr.setTexture(tex);
    spr.setScale(4, 4);
    getTexMines(0);
}

void BoardDrawer::DrawBoard(RenderWindow &window, Board& board, Vector2f pos, bool finished)
{
    for(int x = 0; x < board.getSize().x; x++) {
        for(int y = 0; y < board.getSize().y; y++) {

            Vector2f tilePos = pos;
            tilePos += Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            spr.setPosition(tilePos);
            if(finished)
                drawFinished(tilePos, board.generatedmap[x][y]);
            else
                drawNotFinished(tilePos, board.generatedmap[x][y]);
            window.draw(spr);
            
        }
    }
}

void BoardDrawer::drawNotFinished(Vector2f pos, pbi info) {
    if(!info.first) { // If it isn't visible
        if((info.second & FLAG_AND) == 0) { // If it isn't a flag
            getTexMines(0); // Draw unpressed
        } else {
            getTexMines(2); // Draw flag
        }
        return;
    }
    int adjMines = info.second;
    if(adjMines == 0)
        getTexMines(1); // Draw no adjacent
    else if(adjMines == 9)
        getTexMines(5); // Draw mine
    else
        getTexMineNum(adjMines - 1); // Draw num adjacent
}

void BoardDrawer::drawFinished(Vector2f pos, pbi info) {
    int visible = info.first;
    int adjMines = info.second;
    if(visible) {
        if(adjMines == 0)
            getTexMines(1); // Draw no adjacent
        else if(adjMines == 9)
            getTexMines(6); // Draw exploded mine
        else
            getTexMineNum(adjMines - 1); // Draw num adjacent
    } else {
        if((adjMines & FLAG_AND) == 0) {
            if(adjMines == 9)
                getTexMines(5); // Draw unexploded mine
            else
                getTexMines(0); // Draw unpressed
        } else {
            if((adjMines & (FLAG_AND-1)) == 9)
                getTexMines(2); // Draw flag
            else
                getTexMines(7); // Draw bad flag
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

