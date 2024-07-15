#include "Manager.h"

Manager::Manager(Vector2u windowSize)
    : board(mapSize, mapMines)
    , drawer()
    , boardPos(0, windowSize.y - 512)
    , clock()
    , winTime(-1)
{
    // Setup some variables
    firstClick = true;
    finished = false;
    win = false;
    // Load the font (best font btw)
    font.loadFromFile("../assets/Ubuntu.ttf");
    flagsRemaining = 10;
}

// Main update loop
void Manager::update(RenderWindow& window, bool a) {
    // Get the scuffed variable
    leftPressed = a;
    // Update the game while it's started and not finished
    if(!finished)
        updateClicks(window);
    if(Keyboard::isKeyPressed(Keyboard::R)) { // Restart if r is pressed
        firstClick = true;
        finished = false;
        win = false;
        flagsRemaining = 10;
        board.regenerate_map(mapSize, mapMines, Vector2i(0, 0));
        winTime = -1;
    }
}

// Function that updates the grid if the player clicks
void Manager::updateClicks(RenderWindow& window) {
    // Update the timer when the game goes on
    if(!firstClick)
        winTime = clock.getElapsedTime().asSeconds();
    // Get the current tile the mouse is in
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2i mpb = Vector2i(mousePos.x - boardPos.x, mousePos.y - boardPos.y);
    mpb /= 64;
    // First check if the mouse is in the boundaries
    if(mpb.x >= 0 && mpb.y >= 0 && 
        mousePos.x >= boardPos.x && mousePos.y >= boardPos.y &&
        mousePos.x < boardPos.x + board.getSize().x * drawer.TILE_SIZE &&
        mousePos.y < boardPos.y + board.getSize().y * drawer.TILE_SIZE) {
        
        // If left clicked and there's not a flag
        if(leftPressed && (board.generatedmap[mpb.x][mpb.y].second & FLAG_AND) == 0) {
            // Create the board with some space from the mouse
            if(firstClick) {
                board.regenerate_map(Vector2u(board.getSize()), 10, mpb);
                firstClick = false;
                clock.restart();
            }
            // Update the grid at the pressed position
            int res = board.updateAt(mpb);

            // If clicked on a mine lose
            if(res == 1) {
                cout << "You lost!" << endl; // TODO: remove from console
                finished = true;
                winTime = clock.getElapsedTime().asSeconds();
            }
            // If completed the grid win
            if(board.checkWin()) {
                cout << "You won!" << endl; // TODO: remove from console
                board.autoComplete();
                finished = true;
                win = true;
                winTime = clock.getElapsedTime().asSeconds();
            }
        }
        // If right clicked
        else if(Mouse::isButtonPressed(Mouse::Right) && !lastRight) { // Other way of check if right pressed once
            // If the tile isn't visible
            if(!board.generatedmap[mpb.x][mpb.y].first) {
                // Add or remove a flag if the tile isn't visible
                board.generatedmap[mpb.x][mpb.y].second ^= FLAG_AND;
                // Change the flags remaining by +-1
                flagsRemaining += ((board.generatedmap[mpb.x][mpb.y].second & FLAG_AND) == 0) * 2 - 1;
                lastRight = true;
            }
        }
        // For the first-time-press check
        if(!Mouse::isButtonPressed(Mouse::Right)) {
            lastRight = false;
        }
    }
}

// Draws the board and text to the screen
void Manager::draw(RenderWindow& window) {
    // Draw the board
    drawer.DrawBoard(window, board, boardPos, finished);
    Text text;
    // Draw the flags remaining text
    text.setFont(font);
    text.setFillColor(Color::Red);
    text.setString(to_string(flagsRemaining));
    window.draw(text);
    // And the current time text
    text.setPosition(Vector2f(0, 50));
    text.setString(to_string(int(winTime)));
    window.draw(text);
    // TODO: change this text to real cool text (with textured numbers)
}