//
// Created by Abhishek on 23/10/18.
//

#ifndef OTHELLO_ASSIGNMENT_3_OTHELLO_H
#define OTHELLO_ASSIGNMENT_3_OTHELLO_H

#include <bits/stdc++.h>

using namespace std;

class Othello {
    vector<vector<char>> board;
    unsigned short int boardSize;

    // turn = true means black's turn
    bool turn;

public:
    static const char black_symbol;
    static const char white_symbol;
    static const char empty_symbol;

    Othello();

    void printBoard();

    bool getTurn();

    bool playMove(short x, short y);

    set<pair<short int, short int>> get_moves();

    int get_game_score();

    void pass_turn();

private:
    void initialiseBoard();

    void clearBoard();

    bool playSubMove(short x, const short &xStep, short y, const short &yStep);

    bool canPlayInDirection(const char &symbol_to_find, short x, const short &xDir, short y, const short &yDir);
};


#endif //OTHELLO_ASSIGNMENT_3_OTHELLO_H
