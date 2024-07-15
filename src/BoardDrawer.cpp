#include "BoardDrawer.h"

BoardDrawer::BoardDrawer() {
    // Import the tile textures and scale it
    tex.loadFromFile("../assets/Minesweeper.png");
    spr.setTexture(tex);
    spr.setScale(4, 4);
    getTexMines(0); // Useless?
}

// Function that draws a board to the screen
void BoardDrawer::DrawBoard(RenderWindow &window, Board& board, Vector2f pos, bool finished)
{
    // For each tile
    for(int x = 0; x < board.getSize().x; x++) {
        for(int y = 0; y < board.getSize().y; y++) {
            // Get the screen tile position
            Vector2f tilePos = pos;
            tilePos += Vector2f(x * TILE_SIZE, y * TILE_SIZE);
            // Set the sprite position
            spr.setPosition(tilePos);
            // Get the texture depending on if you have win/lost or in-game
            if(finished)
                drawFinished(tilePos, board.generatedmap[x][y]);
            else
                drawNotFinished(tilePos, board.generatedmap[x][y]);
            // Finally draw the tile
            window.draw(spr);
        }
    }
}

// Draw everything if the player hasn't finished yet
void BoardDrawer::drawNotFinished(Vector2f pos, pbi info) {
    if(!info.first) { // If it isn't visible it's either a flag or unpressed
        if((info.second & FLAG_AND) == 0) { // If it isn't a flag
            getTexMines(0); // Draw unpressed
        } else {
            getTexMines(2); // Draw flag
        }
        return;
    }
    // Else it's a number
    int adjMines = info.second;
    // There are no adjacent mines
    if(adjMines == 0)
        getTexMines(1); // Draw no adjacent
    else if(adjMines == 9) // A mine
        getTexMines(5); // Draw mine (not necessary but just in case)
    else // Or a number
        getTexMineNum(adjMines - 1); // Draw num adjacent
}

// Draw everything if the player has already finished (show everything)
void BoardDrawer::drawFinished(Vector2f pos, pbi info) {
    // Make the info more readable
    int visible = info.first;
    int adjMines = info.second;

    // The tile is visible
    if(visible) {
        if(adjMines == 0)
            getTexMines(1); // Draw no adjacent
        else if(adjMines == 9) // If it's >10, then it's a flag
            getTexMines(6); // Draw exploded mine
        else
            getTexMineNum(adjMines - 1); // Draw num adjacent
    } else { // It isn't visible
        if((adjMines & FLAG_AND) == 0) { // If there's no flag there
            if(adjMines == 9)
                getTexMines(5); // Draw unexploded mine
            else
                getTexMines(0); // Draw unpressed
        } else {
            if((adjMines & (~FLAG_AND)) == 9) // The tile without a flag
                getTexMines(2); // Draw flag
            else
                getTexMines(7); // Draw bad flag
        }
    }
}

// Set the sprite texture to a number tile (1-8)
void BoardDrawer::getTexMineNum(int n)
{
    spr.setTextureRect(IntRect(Vector2i(n * 17, 66), Vector2i(16, 16)));
}
// Set the sprite texture to a texture in the first row (flags, mines, 0, etc)
void BoardDrawer::getTexMines(int n)
{
    spr.setTextureRect(IntRect(Vector2i(n * 17, 49), Vector2i(16, 16)));
}

void BoardDrawer::getTexFace(int n) // TODO
{
}

void BoardDrawer::getTexNum(int n) // TODO
{
}

