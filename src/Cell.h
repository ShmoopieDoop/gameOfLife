//
// Created by Tom Malhi on 25/05/2023.
//

#ifndef GAMEOFLIFE_CELL_H
#define GAMEOFLIFE_CELL_H


class Cell {
    int x;
    int y;
    bool alive;
public:
    Cell(int x, int y);

    Cell(int x, int y, bool state);

    void flip();

    bool isAlive() const;
    
    void setAlive(bool state);
};


#endif //GAMEOFLIFE_CELL_H
