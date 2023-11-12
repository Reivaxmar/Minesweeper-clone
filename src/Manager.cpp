#include "Manager.h"

Manager::Manager(Vector2u windowSize)
    : board(Vector2u(8, 8), 10)
    , drawer()
    , boardPos(0, windowSize.y - 512)
{
    firstClick = true;
    font.loadFromFile("../assets/Ubuntu.ttf");
    flagsRemaining = 10;
    for(int x = 0; x < board.generatedmap.size(); x++) {
        for(int y = 0; y < board.generatedmap[0].size(); y++) {
            cout << board.generatedmap[x][y].second << " ";
        }
        cout << endl;
    }

}

void Manager::update(RenderWindow& window) {
    updateClicks(window);
}

void Manager::updateClicks(RenderWindow& window) {
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2i mpb = Vector2i(mousePos.x - boardPos.x, mousePos.y - boardPos.y);
    // Prints the tile the mouse is hovering
    mpb /= 64;
    if(mpb.x >= 0 && mpb.y >= 0 && 
        mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x < window.getSize().x && mousePos.y < window.getSize().y) {
        if(Mouse::isButtonPressed(Mouse::Left) && (board.generatedmap[mpb.x][mpb.y].second & uint(32)) == 0) {
            if(firstClick) {
                board.regenerate_map(Vector2u(8, 8), 10, mpb);
                firstClick = false;
            }
            int res = board.updateAt(mpb);
            if(res == 1) {
                cout << "You lost!" << endl;
                window.close();
            }
        } else if(Mouse::isButtonPressed(Mouse::Right) && !lastRight) {
            board.generatedmap[mpb.x][mpb.y].second ^= uint(32);
            flagsRemaining += ((board.generatedmap[mpb.x][mpb.y].second & uint(32)) == 0) * 2 - 1;
            cout << flagsRemaining << endl;
            lastRight = true;
        }
        if(!Mouse::isButtonPressed(Mouse::Right)) {
            lastRight = false;
        }
    }
}

void Manager::draw(RenderWindow& window) {
    drawer.DrawBoard(window, board, boardPos);
    Text text;
    text.setFont(font);
    text.setString(to_string(flagsRemaining));
    text.setFillColor(Color::Red);
    window.draw(text);
}