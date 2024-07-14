#include "Manager.h"

Manager::Manager(Vector2u windowSize)
    : board(mapSize, mapMines)
    , drawer()
    , boardPos(0, windowSize.y - 512)
    , clock()
    , winTime(-1)
{
    firstClick = true;
    finished = false;
    win = false;
    font.loadFromFile("../assets/Ubuntu.ttf");
    flagsRemaining = 10;
    for(int x = 0; x < board.generatedmap.size(); x++) {
        for(int y = 0; y < board.generatedmap[0].size(); y++) {
            cout << board.generatedmap[x][y].second << " ";
        }
        cout << endl;
    }

}

void Manager::update(RenderWindow& window, bool a) {
    leftReleased = a;
    if(!finished)
        updateClicks(window);
    if(Keyboard::isKeyPressed(Keyboard::R)) { //Restart if r is pressed
        firstClick = true;
        finished = false;
        win = false;
        font.loadFromFile("../assets/Ubuntu.ttf");
        flagsRemaining = 10;
        board.regenerate_map(mapSize, mapMines, Vector2i(0, 0));
        winTime = -1;
    }
}

void Manager::updateClicks(RenderWindow& window) {
    if(!firstClick)
        winTime = clock.getElapsedTime().asSeconds();
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2i mpb = Vector2i(mousePos.x - boardPos.x, mousePos.y - boardPos.y);
    // Prints the tile the mouse is hovering
    mpb /= 64;
    // if(Keyboard::isKeyPressed(Keyboard::D)) {cout << "mbp: " << mpb.x <<  ", " << mpb.y << endl << "mousePos: " << mousePos.x <<  ", " << mousePos.y << endl << boardPos.x + board.getSize().x << endl << ; }
    if(mpb.x >= 0 && mpb.y >= 0 && 
        mousePos.x >= boardPos.x && mousePos.y >= boardPos.y &&
        mousePos.x < boardPos.x + board.getSize().x * drawer.TILE_SIZE &&
        mousePos.y < boardPos.y + board.getSize().y * drawer.TILE_SIZE) {
        if(leftReleased && (board.generatedmap[mpb.x][mpb.y].second & MINEAND) == 0) {
            if(firstClick) {
                board.regenerate_map(Vector2u(8, 8), 10, mpb);
                firstClick = false;
                clock.restart();
            }
            int res = board.updateAt(mpb);
            if(res == 1) {
                cout << "You lost!" << endl;
                finished = true;
                winTime = clock.getElapsedTime().asSeconds();
            }
            if(board.checkWin()) {
                cout << "You won!" << endl;
                board.autoComplete();
                finished = true;
                win = true;
                winTime = clock.getElapsedTime().asSeconds();
            }
        } else if(Mouse::isButtonPressed(Mouse::Right) && !lastRight) {
            if(!board.generatedmap[mpb.x][mpb.y].first) {
                // Add or remove a flag if the tile isn't visible
                board.generatedmap[mpb.x][mpb.y].second ^= FLAG_AND;
                // Change the flags remaining by +-1
                flagsRemaining += ((board.generatedmap[mpb.x][mpb.y].second & FLAG_AND) == 0) * 2 - 1;
                lastRight = true;
            }
        }
        if(!Mouse::isButtonPressed(Mouse::Right)) {
            lastRight = false;
        }
    }
}

void Manager::draw(RenderWindow& window) {
    drawer.DrawBoard(window, board, boardPos, finished);
    Text text;
    text.setFont(font);
    text.setFillColor(Color::Red);
    text.setString(to_string(flagsRemaining));
    window.draw(text);
    text.setPosition(Vector2f(0, 50));
    text.setString(to_string(int(winTime)));
    window.draw(text);
}