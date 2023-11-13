#include "Piece.h"
#include "Moves.h"
#include <string>
#include <vector>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board {
    private:
        vector<vector<Piece> > gameBoard;
        double eval;
        int moves;
        vector<Moves> possibleMoves;
        bool isPinned(string) const;
        void generateMoves();

    public:
        Board();
        double getEval() const {return eval;}
        void evaluate() const;
        string bestMove() const;
        void printBoard() const;
        void move(string, string); 
        bool validMove(string, string);
};

#endif

