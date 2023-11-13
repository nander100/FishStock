#ifndef MOVES_H
#define MOVES_H

class Moves {
    public:
        Moves(int a, int b, int c, int d): sRank(a), sFile(b), eRank(c), eFile(d) {}
        int sRank;
        int sFile;
        int eRank;
        int eFile;
};
#endif