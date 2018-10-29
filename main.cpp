#include <bits/stdc++.h>
#include "Othello.h"

#define MAX_INFINITY 1000
#define MIN_INFINITY -1000

using namespace std;

int DEPTH_CUTOFF = 7;


int get_move_score(Othello game, pair<short int, short int> m, int depth,  int alpha, int beta) {
    game.playMove(m.first, m.second);

    if(depth == DEPTH_CUTOFF){
        return game.get_game_score();
    }

    set<pair<short int, short int>> moves;
    moves = game.get_moves();

    int bestValue, value;

    // Maximising Player
    if(!game.getTurn()){
        bestValue = MIN_INFINITY;

        for(pair<short int, short int> move: moves){
            value = get_move_score(game, move, depth + 1, alpha, beta);
            bestValue = max(bestValue, value);
            alpha = max( alpha, bestValue);

            if (beta <= alpha)
                break;
        }
        return bestValue;
    }
    else{
        bestValue = MAX_INFINITY;

        for(pair<short int, short int> move: moves){
            value = get_move_score(game, move, depth + 1, alpha, beta);
            bestValue = min(bestValue, value);
            beta = min( alpha, bestValue);

            if (beta <= alpha)
                break;
        }
        return bestValue;
    }
}


/**
 * This function returns the best move according to the player's turn
 * @param game: othello game instance
 * @return pair<short int, short int>: (row, column)
 */
pair<short int, short int> get_best_move(Othello game) {
    set<pair<short int, short int>> moves;
    moves = game.get_moves();

    pair<short int, short int> bestMove = {-1, -1};

    int bestValue, value;

    // Maximising Player (White)
    if(!game.getTurn()){
        bestValue = MIN_INFINITY;

        for(pair<short int, short int> move: moves){
            value = get_move_score(game, move, 0, MIN_INFINITY, MAX_INFINITY);

            if(value > bestValue){
                bestValue = value;
                bestMove.first = move.first;
                bestMove.second = move.second;
            }
        }
    }

    // Minimising Player (Black)
    else{
        bestValue = MAX_INFINITY;

        for(pair<short int, short int> move: moves){
            value = get_move_score(game, move, 0, MIN_INFINITY, MAX_INFINITY);

            if(value < bestValue){
                bestValue = value;
                bestMove.first = move.first;
                bestMove.second = move.second;
            }
        }
    }

    return bestMove;
}


int main() {
    Othello game;
    game.printBoard();

    short int x = 0, y = 0;

    cout << "You are playing as Black." << endl;

    while (((x >= 0 && x <= 7) && (y >= 0 && y <= 7))) {
        if (game.getTurn()) {
            cout << "Your turn" << endl;

            if(game.get_moves().empty()){
                cout << "You have no valid moves. Hence, passing turn to the computer.";
                game.pass_turn();
            }

            cout << "Enter move (row column) = ";
            cin >> x >> y;

            if (game.playMove(x, y))
                cout << "Move applied" << endl;
            else
                cout << "Invalid move" << endl;
        } else {
            cout << "Computer's turn" << endl;

            pair<short int, short int> move = get_best_move(game);

            if(move.first == -1 and move.second == -1){
                cout << "Computer have no valid moves. Hence, passing turn to the you.";
                game.pass_turn();
            }
            else {
                cout << "Computer choose t play at (" << move.first << ", " << move.second << ")" << endl;
                game.playMove(move.first, move.second);
            }
        }

        cout << endl;

        game.printBoard();
    }

    return 0;
}