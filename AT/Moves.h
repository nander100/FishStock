#ifndef MOVES_H
#define MOVES_H



class Moves {
    public:
        Moves(): sRank(0), sFile(0), eRank(0), eFile(0), moveType(0){}
        Moves(int a, int b, int c, int d): sRank(a), sFile(b), eRank(c), eFile(d), moveType(0) {}
        Moves(int a, int b, int c, int d, int e) : sRank(a), sFile(b), eRank(c), eFile(d), moveType(e) {}
        int sRank;
        int sFile;
        int eRank;
        int eFile;
        int moveType; // capture = 1, check = 2

};
#endif