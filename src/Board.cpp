#include "Board.h"

// Function that checks if the vec2 x is inside the square (0, 0) (inclusive) and y (not inclusive)
template<typename T>
inline bool isinsquare(Vector2<T> x, Vector2<T> y) {
    return (x.x >= 0 && x.y >= 0 && x.x < y.x && x.y < y.y); // Check if x in the range [0, y)
}

Board::Board(Vector2u s, int mines)
    : rng(time(nullptr))
    , randomMinex(0, s.x - 1)
    , randomMiney(0, s.y - 1)
{
    // Regenerate the map at the start of the game
    regenerate_map(s, mines, Vector2i(0, 0));
}

// Function that automatically adds the missing flags. Only call when the grid is finished
void Board::autoComplete() {
    // Iterate through each row and column
    for(auto& row : generatedmap) {
        for(auto& col : row) {
            // Get the information of the tile
            bool visible = col.first;
            int adjMines = col.second;
            // Add the missing flags
            if(!visible && adjMines == 9) { // 9 is a mine without flag
                col.second ^= FLAG_AND;
            }
        }
    }
}

// Function that returns 1 if a mine is clicked and expands the grid on the clicked tile
int Board::updateAt(Vector2i pos) { // Really just a DFS
    // Check if pos is valid
    if((pos.x < 0 || pos.y < 0) || (pos.x >= size.x || pos.y >= size.y)) return -1;
    // Get the current tile
    pbi tile = generatedmap[pos.x][pos.y];
    // If there's a flag return
    if((tile.second & FLAG_AND) != 0) return -1;
    // If it's already visible
    if(tile.first == true) return 0;
    // Set the tile to be visible
    generatedmap[pos.x][pos.y].first = true;
    // If you expand on a mine, return 1 (lose). Bug proof below
    if(tile.second == 9) return 1;
    // If there aren't any mines around
    if(tile.second == 0) {
        // Expand to the adjacent
        for(int x = -1; x < 2; x++) {
            for(int y = -1; y < 2; y++) {
                updateAt(pos + Vector2i(x, y));
            }
        }
    }
    /*
     * Proof why it isn't a bug
     *
     * To expand, it is required to have no adjacent mines, so to have expanded
     * into a mine, it means that the first iteration (click) was on a mine.
    */
   return 0;
}

// Function that returns true if the player has made all the number tiles visible
bool Board::checkWin() {
    // Iterate for each tile
    for(int x = 0; x < size.x; x++) {
        for(int y = 0; y < size.y; y++) {
            // Get the number of the tile
            int mineNum = generatedmap[x][y].second & (~FLAG_AND);
            // If it's a number and it isn't visible
            if(mineNum >= 0 && mineNum <= 8 && !generatedmap[x][y].first) {
                // You haven't won yet
                return false;
            }
        }
    }
    // Else there aren't any non-visible tiles with numbers
    return true;
}

// Function that regenerates the grid given the position of the first click, so that the click is on a 0 tile
void Board::regenerate_map(Vector2u s, int mines, Vector2i clickPos)
{
    // Setup the RNGs
    randomMinex.param(uniform_int_distribution<mt19937::result_type>::param_type(0, s.x - 1));
    randomMiney.param(uniform_int_distribution<mt19937::result_type>::param_type(0, s.y - 1));
    // Set the class variables
    size = s; nmines = mines;

    // Generatedmap ==> pair<bool, int> -> bool visible, int mines (9 is mine)
    generatedmap = vec<vec<pbi>>(size.y, vec<pbi>(size.x, mp(false, 0)));
    for(int i = 0; i < mines; i++) {
        // Get distance between the mine and the first tile
        Vector2u newRand = Vector2u(randomMinex(rng), randomMinex(rng));
        // If the mine shouldn't go there
        while(abs((int)newRand.x - clickPos.x) + abs((int)newRand.y - clickPos.y) <= 2 ||
              generatedmap[newRand.x][newRand.y].second != false) {
            // Get another mine
            newRand = Vector2u(randomMinex(rng), randomMinex(rng));
        }
        // Add the mine to the grid
        generatedmap[newRand.x][newRand.y] = mp(false, 9);
    }
    
    regenerate_visible();
}

// Function that gets the number of the tiles (the number of mines around)
void Board::regenerate_visible() {
    // Iterate through each tile
    for(int x = 0; x < generatedmap.size(); x++) {
        for(int y = 0; y < generatedmap[0].size(); y++) {
            // If it's a mine skip it
            if(generatedmap[x][y].second == 9) continue;
            // Else set the correct number of surronding mines
            generatedmap[x][y] = mp(false, checkMinesAround(Vector2u(x, y)));
        }
    }
}

// Get function for the size
Vector2i Board::getSize()
{
    return Vector2i(size.x, size.y);
}

// Function that given a tile position, returns the number of adjacent mines around that position
int Board::checkMinesAround(Vector2u pos) {
    // Convert to Vector2i
    Vector2i npos = Vector2i(pos);
    // Array with each of the adjacent tiles
    Vector2i adds[] = {
        Vector2i(-1, -1),
        Vector2i(-1, 0),
        Vector2i(-1, 1),
        Vector2i(0, -1),
        Vector2i(0, 1),
        Vector2i(1, -1),
        Vector2i(1, 0),
        Vector2i(1, 1)
    };
    // Ans
    int ret = 0;
    // Iterate through each of the adjacent tiles
    for(int i = 0; i < 8; i++) {
        // Get the tile to check
        Vector2i toCheck = npos + adds[i];
        // If the tile is inside the level
        if(isinsquare(toCheck, Vector2i(size)))
            // If it's a mine add one
            if(generatedmap[toCheck.x][toCheck.y].second == 9)
                ret++;
    }
    // Return the number of adjacent mines
    return ret;
}