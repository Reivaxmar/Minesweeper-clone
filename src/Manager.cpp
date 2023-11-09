#include "Manager.h"

Manager::Manager()
    : board(Vector2u(8, 8), 10)
    , drawer()
{
    for(int x = 0; x < board.generatedmap.size(); x++) {
        for(int y = 0; y < board.generatedmap[0].size(); y++) {
            cout << board.generatedmap[x][y].second << " ";
        }
        cout << endl;
    }

}

void Manager::update() {

}

void Manager::draw(RenderWindow& window) {
    drawer.DrawBoard(window, board, Vector2f(0, window.getSize().y - 512));
}