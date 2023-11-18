#include "Piece.h"
#include "Board.h"
#include <vector>
#include <iostream>
#include<ctype.h>
using namespace std;

int main() {
    string start;
    string end;
    Board myBoard;
    myBoard.printBoard();

    // while(true) {
    //     cout << "Enter a starting piece" << end;
    //     cin >> start;

    //     cout << "Enter the ending location" << endl;
    //     cin >> end;

    //     myBoard.move(start, end);
    //     myBoard.printBoard();
    // }
    for(unsigned int i = 0; i < 2; i++) {
        cout << "Enter a starting piece" << end;
        cin >> start;

        cout << "Enter the ending location" << endl;
        cin >> end;

        myBoard.move(start, end);
        myBoard.printBoard();
    }
    myBoard.generateMoves();
 
    return 0;
}

