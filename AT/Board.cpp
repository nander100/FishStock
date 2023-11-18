#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <ctype.h>
#include "Moves.h"

Board::Board() : gameBoard(8, vector<Piece>(8, Piece(0, 0))) {
    // white = 0, black = 1
    // pawn = 1
    // knight = 2
    // bishop = 3
    // rook = 4
    // queen = 5
    // king = 6
    // 4 2 3 5 6 3 2 4 ROW 0
    // 1 1 1 1 1 1 1 1 ROW 1
    // 0 0 0 0 0 0 0 0 ROW 2
    // 0 0 0 0 0 0 0 0 ROW 3
    // 0 0 0 0 0 0 0 0 ROW 4
    // 0 0 0 0 0 0 0 0 ROW 5
    // 1 1 1 1 1 1 1 1 ROW 6
    // 4 2 3 5 6 3 2 4 ROW 7
    // 
    // 0 1 2 3 4 5 6 7 
    // gameBoard(8, vector<Piece>(8, Piece(0,0)));
    // a1 = 7,0

    // fill the white position
    for(int i = 0; i < 8; ++i) { // for the pawns
        gameBoard[6][i] = Piece(0, 1);
    }
    gameBoard[7][0] = Piece(0, 4); // rook
    gameBoard[7][7] = Piece(0, 4); // rook

    gameBoard[7][1] = Piece(0, 2); // knight
    gameBoard[7][6] = Piece(0, 2); // knight

    gameBoard[7][2] = Piece(0, 3); // bishop
    gameBoard[7][5] = Piece(0, 3); // bishop

    gameBoard[7][3] = Piece(0, 5); // queen
    gameBoard[7][4] = Piece(0, 6); // king

    // fill the black pawns positon
    for(int i = 0; i < 8; ++i) { // for the pawns
        gameBoard[1][i] = Piece(1, 1);
    }

    gameBoard[0][0] = Piece(1, 4); // rook
    gameBoard[0][7] = Piece(1, 4); // rook

    gameBoard[0][1] = Piece(1, 2); // knight
    gameBoard[0][6] = Piece(1, 2); // knight

    gameBoard[0][2] = Piece(1, 3); // bishop
    gameBoard[0][5] = Piece(1, 3); // bishop

    gameBoard[0][3] = Piece(1, 5); // queen
    gameBoard[0][4] = Piece(1, 6); // king

    //init
    moves = 0; // white to move
    eval = 0.0;
}

void Board::printBoard() const {
    cout << "Current Board State..." << endl << endl;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cout << gameBoard[i][j].getType() << " ";
        }
        cout << endl;
    }
}

void Board::generateMoves() {

    Piece pieceToMove;
    for(unsigned int rank = 0; rank < 8; ++rank) {
        for(unsigned int file = 0; file < 8; ++file) {
            pieceToMove = gameBoard[rank][file];
            // PAWNS (COLOR DEPENDENT)
            if(pieceToMove.getTeam() == 0) {
                // THE NUMBER OF AVAILABLE PAWN MOVES FOR WHITE 
                if (pieceToMove.getType() == 1) {
                    if (!pieceToMove.moved()){ // pawn has not moved 
                        if (gameBoard[rank - 1][file].getType() == 0) {
                            moves++;
                            possibleMoves.push_back(Moves(rank, file, rank - 1, file));
                            if (gameBoard[rank - 2][file].getType() == 0) {
                                moves++;
                                possibleMoves.push_back(Moves(rank, file, rank - 2, file));
                            }
                        }
                    }               
                    else { // pawn has moved
                        if (gameBoard[rank - 1][file].getType() == 0) {
                            moves++;
                            possibleMoves.push_back(Moves(rank, file, rank - 1, file));
                        }
                    }
                    if (gameBoard[rank - 1][file + 1].getType() != 0) {
                        if (gameBoard[rank - 1][file + 1].getTeam() != gameBoard[rank][file].getTeam()) {
                            if (gameBoard[rank - 1][file + 1].getType() != 6) {
                                ++moves;
                                possibleMoves.push_back(Moves(rank, file, rank - 1, file + 1, 1)); // capture
                            }
                             
                            else {
                                // ++moves;
                                // possibleMoves.push_back(Moves(rank, file, rank, file + 1, 2)); // check                              
                            }
                        }
                    }
                    else if (gameBoard[rank - 1][file - 1].getType() != 0) {
                        if (gameBoard[rank - 1][file - 1].getTeam() != gameBoard[rank][file].getTeam()) {
                            if (gameBoard[rank - 1][file - 1].getType() != 6) {
                                ++moves;
                                possibleMoves.push_back(Moves(rank, file, rank - 1, file - 1, 1)); // capture
                            }
                            else {
                                // ++moves;
                                // possibleMoves.push_back(Moves(rank, file, rank, file - 1, 2)); // check  
                            }
                        }
                    }
                }
            }
            else if (pieceToMove.getTeam() == 1) {
                if (pieceToMove.getType() == 1) {
                    // THE NUMBER OF AVAILABLE PAWN MOVES FOR BLACK 
                    if (!pieceToMove.moved()){ // pawn has not moved 
                        if (gameBoard[rank + 1][file].getType() == 0) {
                            moves++;
                            possibleMoves.push_back(Moves(rank, file, rank +1, file));
                            if (gameBoard[rank + 2][file].getType() == 0) {

                                moves++;
                                possibleMoves.push_back(Moves(rank, file, rank + 2, file));
                            }
                        }
                    }
                    else { // pawn has moved
                        if (gameBoard[rank + 1][file].getType() == 0) {
                            moves++;
                            possibleMoves.push_back(Moves(rank, file, rank + 1, file));
                        }
                    }
                    // pawn captures and checks
                    if (gameBoard[rank + 1][file - 1].getType() != 0) {
                        if (gameBoard[rank + 1][file - 1].getTeam() != gameBoard[rank][file].getTeam()) {
                            if (gameBoard[rank + 1][file- 1].getType() != 6) {
                                ++moves;
                                possibleMoves.push_back(Moves(rank, file, rank + 1, file - 1, 1)); // capture
                            }
                             
                            else {
                                // ++moves;
                                // possibleMoves.push_back(Moves(rank, file, rank, file + 1, 2)); // check                              
                            }
                        }
                    }
                    else if (gameBoard[rank + 1][file + 1].getType() != 0) {
                        if (gameBoard[rank + 1][file + 1].getTeam() != gameBoard[rank][file].getTeam()) {
                            if (gameBoard[rank + 1][file + 1].getType() != 6) {
                                ++moves;
                                possibleMoves.push_back(Moves(rank, file, rank + 1, file +1, 1)); // capture
                            }
                            else {
                                // ++moves;
                                // possibleMoves.push_back(Moves(rank, file, rank, file - 1, 2)); // check  
                            }
                        }
                    }
                }
            }
            // KNIGHTS
            if (pieceToMove.getType() == 2) {
                if ((rank + 2 >= 0 && rank + 2 < 8 && file + 1 >= 0 && file + 1 < 8) &&
                    gameBoard[rank + 2][file + 1].getType() == 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank + 2, file + 1));
                }
                else if ((rank + 2 >= 0 && rank + 2 < 8 && file + 1 >= 0 && file + 1 < 8) &&
                    gameBoard[rank + 2][file + 1].getType() != 0 &&
                    gameBoard[rank + 2][file + 1].getTeam() != gameBoard[rank][file].getTeam() &&
                    gameBoard[rank + 2][file + 1].getType() != 6){
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank + 2, file + 1, 1));
                }

                if ((rank + 2 >= 0 && rank + 2 < 8 && file - 1 >= 0 && file - 1 < 8) && 
                    gameBoard[rank + 2][file - 1].getType() == 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank + 2, file - 1));

                }
                else if ((rank + 2 >= 0 && rank + 2 < 8 && file - 1 >= 0 && file - 1 < 8) &&
                    gameBoard[rank + 2][file - 1].getType() != 0 &&
                    gameBoard[rank + 2][file - 1].getTeam() != gameBoard[rank][file].getTeam() &&
                    gameBoard[rank + 2][file - 1].getType() != 6){
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank + 2, file - 1, 1));
                }

                if ((rank - 2 >= 0 && rank - 2 < 8 && file + 1 >= 0 && file + 1 < 8) &&
                    gameBoard[rank - 2][file + 1].getType() == 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank - 2, file + 1));

                }
                else if ((rank - 2 >= 0 && rank - 2 < 8 && file + 1 >= 0 && file + 1 < 8) &&
                    gameBoard[rank - 2][file + 1].getType() != 6 &&
                    gameBoard[rank - 2][file + 1].getTeam() != gameBoard[rank][file].getTeam() &&
                    gameBoard[rank - 2][file + 1].getType() != 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank - 2, file + 1, 1));

                }

                if ((rank - 2 >= 0 && rank - 2 < 8 && file - 1 >= 0 && file - 1 < 8) &&
                    gameBoard[rank - 2][file - 1].getType() == 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank - 2, file - 1));

                }
                else if ((rank - 2 >= 0 && rank - 2 < 8 && file - 1 >= 0 && file - 1 < 8) &&
                    gameBoard[rank - 2][file - 1].getType() != 0 && 
                    gameBoard[rank - 2][file - 1].getTeam() != gameBoard[rank][file].getTeam() &&
                    gameBoard[rank - 2][file - 1].getType() != 6) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank - 2, file - 1, 1));
                }

                if ((rank - 1 >= 0 && rank - 1 < 8 && file + 2 >= 0 && file + 2 < 8) &&
                    gameBoard[rank - 1][file + 2].getType() == 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank - 1, file + 2));

                }
                else if ((rank - 1 >= 0 && rank - 1 < 8 && file + 2 >= 0 && file + 2 < 8) &&
                    gameBoard[rank - 1][file + 2].getType() != 0 &&
                    gameBoard[rank - 1][file + 2].getTeam() != gameBoard[rank][file].getTeam() &&
                    gameBoard[rank - 1][file + 2].getType() != 6) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank - 1, file + 2, 1)); 
                }

                if ((rank - 1 >= 0 && rank - 1 < 8 && file - 2 >= 0 && file - 2 < 8) &&
                    gameBoard[rank - 1][file - 2].getType() == 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank - 1, file - 2));

                }
                else if ((rank - 1 >= 0 && rank - 1 < 8 && file - 2 >= 0 && file - 2 < 8) &&
                    gameBoard[rank - 1][file - 2].getType() != 0 &&
                    gameBoard[rank - 1][file - 2].getTeam() != gameBoard[rank][file].getTeam() &&
                    gameBoard[rank - 1][file - 2].getType() != 6) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank - 1, file - 2, 1));

                }

                if ((rank + 1 >= 0 && rank + 1 < 8 && file + 2 >= 0 && file + 2 < 8) &&
                    gameBoard[rank + 1][file + 2].getType() == 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank + 1, file + 2));
                }
                else if ((rank + 1 >= 0 && rank + 1 < 8 && file + 2 >= 0 && file + 2 < 8) &&
                    gameBoard[rank + 1][file + 2].getType() != 0 &&
                    gameBoard[rank + 1][file + 2].getTeam() != gameBoard[rank][file].getTeam() &&
                    gameBoard[rank + 1][file + 2].getType() != 6) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank + 1, file + 2, 1));
                }

                if ((rank + 1 >= 0 && rank + 1 < 8 && file - 2 >= 0 && file -2 < 8) &&
                    gameBoard[rank + 1][file - 2].getType() == 0) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank + 1, file - 2));
                }
                else if ((rank + 1 >= 0 && rank + 1 < 8 && file - 2 >= 0 && file -2 < 8) &&
                    gameBoard[rank + 1][file - 2].getType() != 0 && 
                    gameBoard[rank + 1][file - 2].getTeam() != gameBoard[rank][file].getTeam() &&
                    gameBoard[rank + 1][file - 2].getType() != 6) {
                    moves++;
                    possibleMoves.push_back(Moves(rank, file, rank + 1, file - 2, 1));
                }
            }

            // BIHOPS
            if (pieceToMove.getType() == 3) {
                int bRank = rank;
                int bFile = file;
                cout << "0" << endl;
                while (bRank + 1 <= 7 && bRank + 1 >= 0 && bFile + 1 <= 7 && bFile + 1 >=0) {
                    if(gameBoard[bRank + 1][bFile + 1].getType() == 0){
                        cout << 1 << endl;
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, bRank + 1, bFile + 1));
                        bRank++;
                        bFile++;
                    }
                    else {
                        break;
                    }
                }
                bRank = rank;
                bFile = file;
                
                while (bRank + 1 <= 7 && bRank + 1 >=0 && bFile - 1 <= 7 && bFile - 1 >= 0) {
                    if(gameBoard[bRank + 1][bFile - 1].getType() == 0){
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, bRank + 1, bFile - 1));
                        bRank++;
                        bFile--;
                    }
                    else if(gameBoard[bRank + 1][bFile - 1].getType() != 0 && 
                            gameBoard[bRank + 1][bFile - 1].getTeam() != gameBoard[bRank][bFile].getTeam() &&
                            gameBoard[bRank + 1][bFile - 1].getType() != 6) {
                            possibleMoves.push_back(Moves(rank, file, bRank + 1, bFile - 1, 1));
                            break;
                    }
                    else {
                        break;
                    }
                }
                bRank = rank;
                bFile = file;

                while (bRank - 1 <= 7 && bRank - 1 >=0 && bFile + 1 <= 7 && bFile + 1 >= 0) {
                    if(gameBoard[bRank - 1][bFile + 1].getType() == 0){
                        cout << 1 << endl;
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, bRank - 1, bFile + 1));
                        bRank--;
                        bFile++;
                    }
                    else if(gameBoard[bRank - 1][bFile + 1].getType() != 0 && 
                            gameBoard[bRank - 1][bFile + 1].getTeam() != gameBoard[bRank][bFile].getTeam() &&
                            gameBoard[bRank - 1][bFile + 1].getType() != 6) {
                            possibleMoves.push_back(Moves(rank, file, bRank - 1, bFile + 1, 1));
                            break;
                    }
                    else {
                        break;
                    }
                }
                bRank = rank;
                bFile = file;
                                                
                while (bRank - 1 <= 7 && bRank - 1 >=0 && bFile - 1 <= 7 && bFile - 1 >= 0) {
                    if(gameBoard[bRank - 1][bFile - 1].getType() == 0){
                        cout << 1 << endl;
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, bRank - 1, bFile - 1));
                        bRank--;
                        bFile--;
                    }
                    else if(gameBoard[bRank - 1][bFile - 1].getType() != 0 && 
                            gameBoard[bRank - 1][bFile - 1].getTeam() != gameBoard[bRank][bFile].getTeam() &&
                            gameBoard[bRank - 1][bFile - 1].getType() != 6) {
                            possibleMoves.push_back(Moves(rank, file, bRank - 1, bFile - 1, 1));
                            break;
                    }
                    else {
                        break;
                    }
                }
            }

            // ROOKS
            if (pieceToMove.getType() == 4) {
                int rRank = rank;
                int rFile = file;
                cout << "0" << endl;
                while (rRank + 1 <= 7 && rRank + 1 >= 0 && rFile <= 7 && rFile >=0) {
                    if(gameBoard[rRank + 1][rFile].getType() == 0){
                        possibleMoves.push_back(Moves(rank, file, rRank + 1, rFile));
                        rRank++;
                    }
                    else if(gameBoard[rRank + 1][rFile].getType() != 0 && 
                        gameBoard[rRank + 1][rFile].getTeam() != gameBoard[rank][file].getTeam() &&
                        gameBoard[rRank + 1][rFile].getType() != 6) {
                        possibleMoves.push_back(Moves(rank, file, rRank + 1, rFile, 1));
                        break;
                    }
                    else {
                        break;
                    }
                }
                rRank = rank;
                rFile = file;
                
                while (rRank - 1 <= 7 && rRank - 1 >=0 && rFile <= 7 && rFile >= 0) {
                    if(gameBoard[rRank - 1][rFile].getType() == 0){
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, rRank - 1, rFile));
                        rRank--;
                    }
                    else if(gameBoard[rRank - 1][rFile].getType() != 0 && 
                        gameBoard[rRank - 1][rFile].getTeam() != gameBoard[rank][file].getTeam() &&
                        gameBoard[rRank - 1][rFile].getType() != 6) {
                        possibleMoves.push_back(Moves(rank, file, rRank - 1, rFile, 1));
                        break;
                    }
                    else {
                        break;
                    } 
                }
                rRank = rank;
                rFile = file;

                while (rRank <= 7 && rRank >= 0 && rFile + 1 <= 7 && rFile + 1 >=0) {
                    if(gameBoard[rRank][rFile + 1].getType() == 0){
                        possibleMoves.push_back(Moves(rank, file, rRank, rFile + 1));
                        rFile++;
                    }
                    else if(gameBoard[rRank][rFile + 1].getType() != 0 && 
                        gameBoard[rRank][rFile + 1].getTeam() != gameBoard[rank][file].getTeam() &&
                        gameBoard[rRank][rFile + 1].getType() != 6) {
                        possibleMoves.push_back(Moves(rank, file, rRank, rFile + 1, 1));
                        break;
                    }
                    else {
                        break;
                    }
                }
                rRank = rank;
                rFile = file;
                
                while (rRank <= 7 && rRank >=0 && rFile - 1 <= 7 && rFile - 1 >= 0) {
                    if(gameBoard[rRank][rFile - 1].getType() == 0){
                        possibleMoves.push_back(Moves(rank, file, rRank, rFile - 1));
                        rFile--;
                    }
                    else if(gameBoard[rRank][rFile - 1].getType() != 0 && 
                        gameBoard[rRank][rFile - 1].getTeam() != gameBoard[rank][file].getTeam() &&
                        gameBoard[rRank][rFile - 1].getType() != 6) {
                        possibleMoves.push_back(Moves(rank, file, rRank, rFile - 1, 1));
                        break;
                    }
                    else {
                        break;
                    }
                }
                rRank = rank;
                rFile = file;
            } 

            if (pieceToMove.getType() == 5) {
                int rRank = rank;
                int rFile = file;
                cout << "0" << endl;
                while (rRank + 1 <= 7 && rRank + 1 >= 0 && rFile <= 7 && rFile >=0) {
                    if(gameBoard[rRank + 1][rFile].getType() == 0){
                        possibleMoves.push_back(Moves(rank, file, rRank + 1, rFile));
                        rRank++;
                    }
                    else if(gameBoard[rRank + 1][rFile].getType() != 0 && 
                        gameBoard[rRank + 1][rFile].getTeam() != gameBoard[rank][file].getTeam() &&
                        gameBoard[rRank + 1][rFile].getType() != 6) {
                        possibleMoves.push_back(Moves(rank, file, rRank + 1, rFile, 1));
                        break;
                    }
                    else {
                        break;
                    }
                }
                rRank = rank;
                rFile = file;
                
                while (rRank - 1 <= 7 && rRank - 1 >=0 && rFile <= 7 && rFile >= 0) {
                    if(gameBoard[rRank - 1][rFile].getType() == 0){
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, rRank - 1, rFile));
                        rRank--;
                    }
                    else if(gameBoard[rRank - 1][rFile].getType() != 0 && 
                        gameBoard[rRank - 1][rFile].getTeam() != gameBoard[rank][file].getTeam() &&
                        gameBoard[rRank - 1][rFile].getType() != 6) {
                        possibleMoves.push_back(Moves(rank, file, rRank - 1, rFile, 1));
                        break;
                    }
                    else {
                        break;
                    } 
                }
                rRank = rank;
                rFile = file;

                while (rRank <= 7 && rRank >= 0 && rFile + 1 <= 7 && rFile + 1 >=0) {
                    if(gameBoard[rRank][rFile + 1].getType() == 0){
                        possibleMoves.push_back(Moves(rank, file, rRank, rFile + 1));
                        rFile++;
                    }
                    else if(gameBoard[rRank][rFile + 1].getType() != 0 && 
                        gameBoard[rRank][rFile + 1].getTeam() != gameBoard[rank][file].getTeam() &&
                        gameBoard[rRank][rFile + 1].getType() != 6) {
                        possibleMoves.push_back(Moves(rank, file, rRank, rFile + 1, 1));
                        break;
                    }
                    else {
                        break;
                    }
                }
                rRank = rank;
                rFile = file;
                
                while (rRank <= 7 && rRank >=0 && rFile - 1 <= 7 && rFile - 1 >= 0) {
                    if(gameBoard[rRank][rFile - 1].getType() == 0){
                        possibleMoves.push_back(Moves(rank, file, rRank, rFile - 1));
                        rFile--;
                    }
                    else if(gameBoard[rRank][rFile - 1].getType() != 0 && 
                        gameBoard[rRank][rFile - 1].getTeam() != gameBoard[rank][file].getTeam() &&
                        gameBoard[rRank][rFile - 1].getType() != 6) {
                        possibleMoves.push_back(Moves(rank, file, rRank, rFile - 1, 1));
                        break;
                    }
                    else {
                        break;
                    }
                }
                rRank = rank;
                rFile = file;

                int bRank = rank;
                int bFile = file;
                cout << "0" << endl;
                while (bRank + 1 <= 7 && bRank + 1 >= 0 && bFile + 1 <= 7 && bFile + 1 >=0) {
                    if(gameBoard[bRank + 1][bFile + 1].getType() == 0){
                        cout << 1 << endl;
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, bRank + 1, bFile + 1));
                        bRank++;
                        bFile++;
                    }
                    else {
                        break;
                    }
                }
                bRank = rank;
                bFile = file;
                
                while (bRank + 1 <= 7 && bRank + 1 >=0 && bFile - 1 <= 7 && bFile - 1 >= 0) {
                    if(gameBoard[bRank + 1][bFile - 1].getType() == 0){
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, bRank + 1, bFile - 1));
                        bRank++;
                        bFile--;
                    }
                    else if(gameBoard[bRank + 1][bFile - 1].getType() != 0 && 
                            gameBoard[bRank + 1][bFile - 1].getTeam() != gameBoard[rank][file].getTeam() &&
                            gameBoard[bRank + 1][bFile - 1].getType() != 6) {
                            possibleMoves.push_back(Moves(rank, file, bRank + 1, bFile - 1, 1));
                            break;
                    }
                    else {
                        break;
                    }
                }
                bRank = rank;
                bFile = file;

                while (bRank - 1 <= 7 && bRank - 1 >=0 && bFile + 1 <= 7 && bFile + 1 >= 0) {
                    if(gameBoard[bRank - 1][bFile + 1].getType() == 0){
                        cout << 1 << endl;
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, bRank - 1, bFile + 1));
                        bRank--;
                        bFile++;
                    }
                    else if(gameBoard[bRank - 1][bFile + 1].getType() != 0 && 
                            gameBoard[bRank - 1][bFile + 1].getTeam() != gameBoard[rank][file].getTeam() &&
                            gameBoard[bRank - 1][bFile + 1].getType() != 6) {
                            possibleMoves.push_back(Moves(rank, file, bRank - 1, bFile + 1, 1));
                            break;
                    }
                    else {
                        break;
                    }
                }
                bRank = rank;
                bFile = file;
                                                
                while (bRank - 1 <= 7 && bRank - 1 >=0 && bFile - 1 <= 7 && bFile - 1 >= 0) {
                    if(gameBoard[bRank - 1][bFile - 1].getType() == 0){
                        cout << 1 << endl;
                        moves++;
                        possibleMoves.push_back(Moves(rank, file, bRank - 1, bFile - 1));
                        bRank--;
                        bFile--;
                    }
                    else if(gameBoard[bRank - 1][bFile - 1].getType() != 0 && 
                            gameBoard[bRank - 1][bFile - 1].getTeam() != gameBoard[rank][file].getTeam() &&
                            gameBoard[bRank - 1][bFile - 1].getType() != 6) {
                            possibleMoves.push_back(Moves(rank, file, bRank - 1, bFile - 1, 1));
                            break;
                    }
                    else {
                        break;
                    }
                }
            } // end queen
        } // end for loop
    } // end for loop

    cout << "possibleMoves: " << possibleMoves.size() << endl;  
    for (unsigned int i = 0; i < possibleMoves.size(); ++i) {

        // int rank = 8 - (start.at(start.size() - 1) - 48); // finds the index of the rank
        // int file = start.at(start.size() - 2) - 97; // finds the index of the file

        char sRank = ( -1 * (possibleMoves[i].sRank - 8) ) + 48;
        char sFile = possibleMoves[i].sFile + 97;

        char eRank = ( -1 * (possibleMoves[i].eRank - 8) ) + 48;
        char eFile = possibleMoves[i].eFile + 97;
        if (possibleMoves[i].moveType == 0){
            cout << sFile << sRank << " to " << eFile << eRank << endl;
        }
        else if (possibleMoves[i].moveType == 1) {
            cout << sFile << sRank << " takes " << eFile << eRank << endl;
        }
        else {
            cout << sFile << sRank << " to " << eFile << eRank << "check" << endl;
        }
    }
    cout << endl;
}// end function

bool Board::validMove(string start, string end) {
    int rank = 8 - (start.at(start.size() - 1) - 48); // finds the index of the rank
    int file = start.at(start.size() - 2) - 97; // finds the index of the file

    int rankEnd = 8 - (end.at(end.size() - 1) - 48); // finds the index of the rank
    int fileEnd = end.at(end.size() - 2) - 97; // finds the index of the file
    Moves toMove(rank, file, rankEnd, fileEnd);
    for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
        if (possibleMoves[i].sRank == rank &&
            possibleMoves[i].sFile == file &&
            possibleMoves[i].eRank == rankEnd &&
            possibleMoves[i].eFile == fileEnd) {
            return true;
        }
    }
    return false;
}

void Board::move(string start, string end) { // test move pf4

    // find the initial square

        int rank = 8 - (start.at(start.size() - 1) - 48); // finds the index of the rank
        int file = start.at(start.size() - 2) - 97; // finds the index of the file
        Piece pieceToMove = gameBoard[rank][file];

        // find the destination square
        int rankEnd = 8 - (end.at(end.size() - 1) - 48); // finds the index of the rank
        int fileEnd = end.at(end.size() - 2) - 97; // finds the index of the file

        //moves the piece
        
        gameBoard[rank][file] = Piece();
        gameBoard[rankEnd][fileEnd] = pieceToMove;
        gameBoard[rankEnd][fileEnd].hasMoved = true;
        moves++;




    // else if (pieceToMove.getType() == 1){
    //     if (pieceToMove)

    // }

    // determine the square
    if (moves %2 ==  0) { // white to move
        if (start == "O-O") { // short castle
            for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if ((blackMoves[i].eRank == 7 && blackMoves[i].eFile == 6) ||
                    (blackMoves[i].eRank == 7 && blackMoves[i].eFile == 5)){
                    cout << "Invalid Move!" << endl;
                    return;
                }
            }
            if (gameBoard[7][5].getType() == 0 &&
            gameBoard[7][6].getType() == 0 &&
            gameBoard[7][7].getType() == 4 &&
            gameBoard[7][6].getType() == 0 &&
            gameBoard[7][4].getType() == 6 &&
            gameBoard[7][4].moved() == 0 &&
            gameBoard[7][6].moved() == 0) {
                
                gameBoard[7][4] = Piece();
                gameBoard[7][5] = Piece(0, 6);
                gameBoard[7][6] = Piece(0, 4);
                gameBoard[7][7] = Piece();
                moves++;
            }

        }
        // else if (moves == "O-O-O") { // long castle

        // }
        // else {
        //     cout <<" Invalid Move!" << endl;
        // }
    }
}

void Board::evaluate()  {
    
    
    
    
    
    return;
}

Moves Board::bestMove() {
    int rank;
    int file;
    int turn;
    int whiteMaterial;
    int blackMaterial;
    Moves bMove;
    for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
        rank = possibleMoves[i].sRank;
        file = possibleMoves[i].sFile;
        if(gameBoard[rank][file].getTeam() == 0) {
            blackMoves.push_back(possibleMoves[i]);
        }
        else {
            whiteMoves.push_back(possibleMoves[i]);
        }
    }
    for (unsigned int i = 0; i < 8; ++i) {
        for (unsigned int j = 0; j < 8; ++j)
        if (gameBoard[i][j].getTeam() == 0) {
            if (gameBoard[i][j].getType() == 1) {
                whiteMaterial++;
            }
            else if (gameBoard[i][j].getType() == 2) {
                whiteMaterial = whiteMaterial + 3;
            }
            else if (gameBoard[i][j].getType() == 3) {
                whiteMaterial = whiteMaterial + 3;
            }
            else if (gameBoard[i][j].getType() == 4) {
                whiteMaterial = whiteMaterial + 5;
            }
            else if (gameBoard[i][j].getType() == 5) {
                whiteMaterial = whiteMaterial + 9;
            }

        }
        else {
            if (gameBoard[i][j].getType() == 1) {
                blackMaterial++;
            }
            else if (gameBoard[i][j].getType() == 2) {
                blackMaterial = blackMaterial + 3;
            }
            else if (gameBoard[i][j].getType() == 3) {
                blackMaterial = blackMaterial + 3;
            }
            else if (gameBoard[i][j].getType() == 4) {
                blackMaterial = blackMaterial + 5;
            }
            else if (gameBoard[i][j].getType() == 5) {
                blackMaterial = blackMaterial + 9;
            }
        }

        eval = whiteMaterial - blackMaterial;
        int moveInd = rand() % possibleMoves.size();

        Moves bestMove = blackMoves[moveInd];
        
    }
    return bMove;

}

void Board::move(Moves toMove) {

}

// bool Board::isPinned(Piece piece) const {
//     Piece wKing;
//     Piece bKing;
//     vector<Piece> pinnedPieces;
//     for(unsigned int rank = 0; rank < 8; ++rank) {
//         for(unsigned int file = 0; file < 8; ++file) {
//             if (gameBoard[rank][file].getTeam() == 1){
//                 if (gameBoard[rank][file].getType() == 6) {
//                     bKing = gameBoard[rank][file];
//                     //north
//                     int newRank = rank;
//                     int newFile = file;
//                     while (newRank <= 7 && newRank >=0 && newFile <= 7 && newFile>= 0){
//                         if (gameBoard[newRank - 1][newfile] == 0)
//                     }
                    
//                 }
//             }
//             else if(gameBoard[rank][file].getTeam() == 0) {
//                 if (gameBoard[rank][file].getType() == 6) {
//                     wKing = gameBoard[rank][file];
//                 }
//             }
//         }
//     }
        

    
//     piece.getType();
// }

