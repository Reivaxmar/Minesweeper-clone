#include "Board.h"

template<typename T>
inline bool isinsquare(Vector2<T> x, Vector2<T> y) {
    return (x.x >= 0 && x.y >= 0 && x.x < y.x && x.y < y.y);
}

Board::Board(Vector2u s, int mines)
    : rng(dev())
    , randomMinex(0, s.x - 1)
    , randomMiney(0, s.y - 1)
{
    regenerate_map(s, mines, Vector2i(0, 0)); // TODO: put the click thing working with the click in the game
}

int Board::updateAt(Vector2i pos) {
    // Check if pos is valid
    if((pos.x < 0 || pos.y < 0) || (pos.x >= size.x || pos.y >= size.y)) return -1;
    pbi tile = generatedmap[pos.x][pos.y];
    if(tile.first == true) return 0;
    if(tile.second == 9) return 1;
    if(tile.second == 0) {
        generatedmap[pos.x][pos.y].first = true;
        for(int x = -1; x < 2; x++) {
            for(int y = -1; y < 2; y++) {
                updateAt(pos + Vector2i(x, y));
            }
        }
        return 0;
    } else {
        generatedmap[pos.x][pos.y].first = true;
        return 0;
    }
}

void Board::regenerate_map(Vector2u s, int mines, Vector2i clickPos)
{
    randomMinex.param(uniform_int_distribution<mt19937::result_type>::param_type(0, s.x - 1));
    randomMiney.param(uniform_int_distribution<mt19937::result_type>::param_type(0, s.y - 1));
    size = s; nmines = mines;

    minepos = vector<Vector2u>();
    // Generatedmap ==> pair<bool, int> -> bool visible, int mines (9 is mine)
    generatedmap = vec<vec<pbi>>(size.x, vec<pbi>(size.y, mp(false, 0)));
    for(int i = 0; i < mines; i++) {
        // Get distance between the mine and the cursor
        Vector2u random2 = Vector2u(randomMinex(rng), randomMinex(rng));
        while(abs((int)random2.x - clickPos.x) + abs((int)random2.y - clickPos.y) <= 2 || generatedmap[random2.x][random2.y].second != false) {
            random2 = Vector2u(randomMinex(rng), randomMinex(rng));
        }
        minepos.push_back(random2);
        generatedmap[random2.x][random2.y] = mp(false, 9);
    }
    
    regenerate_visible();
}

void Board::regenerate_visible() {
    for(int x = 0; x < generatedmap.size(); x++) {
        for(int y = 0; y < generatedmap[0].size(); y++) {
            if(generatedmap[x][y].second == 9) continue;
            generatedmap[x][y] = mp(false, checkMinesAround(Vector2u(x, y)));
            //cout << "Generated one!" << endl;
        }
    }
}

Vector2i Board::getSize()
{
    return Vector2i(size.x, size.y);
}

int Board::checkMinesAround(Vector2u pos) {
    Vector2i npos = Vector2i(pos.x, pos.y);
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
    int ret = 0;
    for(int i = 0; i < 8; i++) {
        Vector2i x = adds[i];
        Vector2i toCheck = npos + x;
        if(isinsquare(toCheck, Vector2i(8, 8)))
            if(generatedmap[toCheck.x][toCheck.y].second == 9)
                ret++;
    }
    return ret;
}