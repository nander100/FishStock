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
        vector<Moves> whiteMoves;
        vector<Moves> blackMoves;
        bool isPinned(Piece) const;

    public:
        Board();
        double getEval() const {return eval;}
        void evaluate() ;
        Moves bestMove();
        // bool isPinned(string) const;
        void printBoard() const;
        void move(string, string); 
        void move(Moves);
        bool validMove(string, string);
        void generateMoves();

};

#endif

