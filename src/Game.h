//
// Created by Tom Malhi on 25/05/2023.
//

#ifndef GAMEOFLIFE_GAME_H
#define GAMEOFLIFE_GAME_H


#include "Cell.h"

class Game{
    Cell** grid;
    int width;
    int height;
public:
    Game(int width, int height); 
    ~Game();
    int countLivingNeighbors(int x, int y);
    void update();
    int fSetPosition(const char *fileName);
    int fSave(const char *fileName);
    void flipCell(int x, int y);
    void clearGrid();
    void expandGrid(int newWidth, int newHeight, int x, int y);
    void expandToFitScreen(int screenWidth, int screenHeight, int cellSize);
    Cell** getGrid() {return grid;}
    [[nodiscard]] int getWidth() const {return width;}
    [[nodiscard]] int getHeight() const {return height;}
private:
    static Cell **createGrid(int width, int height) ;
    [[nodiscard]] Cell **createGrid() const;
    Cell **copyGrid(Cell **oldGrid) const;
    void destroyGrid(Cell **g) const;
};



#endif //GAMEOFLIFE_GAME_H
