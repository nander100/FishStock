#ifndef PIECE_H
#define PIECE_H

class Piece {
    public:
        Piece() {type = 0; team = 0; hasMoved = false;}
        Piece(int newTeam, int newType) {team = newTeam, type = newType; hasMoved = false;}
        int getTeam()const {return team;}
        int getType()const {return type;}
        bool moved() const {return hasMoved;}
        void setType (int newType) {type = newType;}
        void setTeam(int newTeam) {team = newTeam;}
    private:
        int type;
        int team;
        bool hasMoved;
};

#endif