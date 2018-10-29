//
// Created by Abhishek on 23/10/18.
//

#include "Othello.h"

const char Othello::black_symbol = 'B';
const char Othello::white_symbol = 'W';
const char Othello::empty_symbol = '-';

/**
 * Othello game constructor
 */
Othello::Othello() {
    this->boardSize = 8;
    this->initialiseBoard();

    this->turn = true;
}

/**
 * Function to initialise the board
 */
void Othello::initialiseBoard() {
    // Clear the board first
    this->clearBoard();

    for (int i = 0; i < this->boardSize; i++) {
        (this->board).push_back(vector<char>());

        for (int j = 0; j < this->boardSize; j++) {
            (this->board)[i].push_back(Othello::empty_symbol);
        }
    }

    this->board[3][3] = Othello::white_symbol;
    this->board[4][4] = Othello::white_symbol;
    this->board[3][4] = Othello::black_symbol;
    this->board[4][3] = Othello::black_symbol;
}

/**
 * Function to clear the board variable
 */
void Othello::clearBoard() {
    this->board.clear();
}

/**
 * Prints the board
 */
void Othello::printBoard() {
    cout << "   ";

    for (int i = 0; i < this->boardSize; i++) {
        cout << i << " ";
    }

    cout << endl;

    for (int i = 0; i < this->boardSize; i++) {
        cout << i << "  ";

        for (int j = 0; j < this->boardSize; j++) {
            cout << this->board[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;
}

/**
 * @return true if it is black's turn else false
 */
bool Othello::getTurn() {
    return this->turn;
}

/**
 * Function to play the move at the given box according to the player if possible.
 *
 * @param x : x coordinate of the box to play the move on
 * @param y : y coordinate of the box to play the move on
 * @return bool : Move played successfully or not
 */
bool Othello::playMove(short x, short y) {
    bool moveApplied = false;

    if (!((x >= 0 && x <= 7) && (y >= 0 && y <= 7))) {
        return moveApplied;
    }

    if ((this->board)[x][y] != Othello::empty_symbol) {
        return moveApplied;
    }

    // Try to flip the discs in all directions
    moveApplied |= this->playSubMove(x, -1, y, -1);
    moveApplied |= this->playSubMove(x, -1, y, 0);
    moveApplied |= this->playSubMove(x, -1, y, 1);
    moveApplied |= this->playSubMove(x, 0, y, -1);
    moveApplied |= this->playSubMove(x, 0, y, 1);
    moveApplied |= this->playSubMove(x, 1, y, -1);
    moveApplied |= this->playSubMove(x, 1, y, 0);
    moveApplied |= this->playSubMove(x, 1, y, 1);

    if (moveApplied)
        this->turn = !this->turn;

    return moveApplied;
}

/**
 * Function to find a new box having disc of same color of the player and
 * flip all the discs between the given box and found box if possible. This
 * function also places the new disc and the given position if possible.
 *
 * @param x : x coordinate of the box to play the move on
 * @param xStep : step for x coordinate to find the new box
 * @param y : y coordinate of the box to play the move on
 * @param yStep : step for x coordinate to find the new box
 * @return bool : Move played successfully or not
 */
bool Othello::playSubMove(short x, const short &xStep, short y, const short &yStep) {
    bool subMoveApplied = false;
    const char symbolToFind = this->turn ? Othello::black_symbol : Othello::white_symbol;

    // Position of the new box
    short int xExtreme = x;
    short int yExtreme = y;

    bool found = false;

    // Try to find another box to flip discs between the given and the new box.
    while (!found) {
        xExtreme = xExtreme + xStep;
        yExtreme = yExtreme + yStep;

        if (!((xExtreme >= 0 && xExtreme <= 7) && (yExtreme >= 0 && yExtreme <= 7))) {
            return subMoveApplied;
        }

        if (this->board[xExtreme][yExtreme] == Othello::empty_symbol) {
            return subMoveApplied;
        }

        if ((this->board)[xExtreme][yExtreme] == symbolToFind) {
            found = true;
        }
    }

    // If two squares found are adjacent then this is not a legal move
    if ((x + xStep == xExtreme) && (y + yStep == yExtreme)) {
        return subMoveApplied;
    } else {
        subMoveApplied = true;
    }

    // Flip discs and place new disc on (x, y)
    while (!((x == xExtreme) && (y == yExtreme))) {
        xExtreme = xExtreme - xStep;
        yExtreme = yExtreme - yStep;
        (this->board)[xExtreme][yExtreme] = symbolToFind;
    }

    return subMoveApplied;
}

set<pair<short int, short int>> Othello::get_moves() {
    set<pair<short, short>> moves;
    const char symbolToFind = this->turn ? Othello::black_symbol : Othello::white_symbol;
    bool canPlay;

    for (short int i = 0; i < this->boardSize; i++) {
        for (short int j = 0; j < this->boardSize; j++) {
            canPlay = false;

            canPlay |= canPlayInDirection(symbolToFind, i, -1, j, -1);
            canPlay |= canPlayInDirection(symbolToFind, i, -1, j, 0);
            canPlay |= canPlayInDirection(symbolToFind, i, -1, j, 1);
            canPlay |= canPlayInDirection(symbolToFind, i, 0, j, -1);
            canPlay |= canPlayInDirection(symbolToFind, i, 0, j, 1);
            canPlay |= canPlayInDirection(symbolToFind, i, 1, j, -1);
            canPlay |= canPlayInDirection(symbolToFind, i, 1, j, 0);
            canPlay |= canPlayInDirection(symbolToFind, i, 1, j, 1);

            if (canPlay) {
                moves.insert(make_pair(i, j));
            }
        }
    }

    return moves;
}

bool Othello::canPlayInDirection(const char &symbol_to_find, short x, const short &xDir, short y, const short &yDir) {
    bool canPlay = false, done = false;

    if (this->board[x][y] != Othello::empty_symbol) {
        return canPlay;
    }

    if ((x + xDir >= 0 && x + xDir <= 7) && (y + yDir >= 0 && y + yDir <= 7)) {
        if (this->board[x + xDir][y + yDir] == symbol_to_find) {
            return canPlay;
        }
    }

    x += xDir;
    y += yDir;

    while ((x >= 0 && x <= 7) && (y >= 0 && y <= 7) && !done) {
        if (this->board[x][y] == Othello::empty_symbol) {
            done = true;
        }

        if (this->board[x][y] == symbol_to_find) {
            done = true;
            canPlay = true;
        }

        x += xDir;
        y += yDir;
    }

    return canPlay;
}

int Othello::get_game_score() {
    int score = 0;

    for(int i = 0; i < this->boardSize; i++){
        for(int j = 0; j < this->boardSize; j++){
            if(this->board[i][j] == Othello::white_symbol){
                score++;
            }
            else if(this->board[i][j] == Othello::black_symbol){
                score--;
            }
        }
    }

    return score;
}

void Othello::pass_turn() {
    this->turn = !this->turn;
}
