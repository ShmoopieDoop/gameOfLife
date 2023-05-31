//
// Created by Tom Malhi on 27/05/2023.
//

#ifndef GAMEOFLIFE_DISPLAY_H
#define GAMEOFLIFE_DISPLAY_H

#include "Game.h"
#include <SDL.h>
#include <iostream>

class Display {
    Game *game;
    int width;
    int height;
public:
    Display(Game *game, int width, int height);
    void mouseToGridCoordinates(int x, int y, int *resultX, int *resultY);
    int getCellDrawSize();
    void drawGame(SDL_Renderer *renderer, bool pause);
};


#endif //GAMEOFLIFE_DISPLAY_H
