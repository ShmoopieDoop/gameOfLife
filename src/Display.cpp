//
// Created by Tom Malhi on 27/05/2023.
//

#include "Display.h"

Display::Display(Game *game, int width, int height) {
    this->game = game;
    this->width = width;
    this->height = height;
}

int Display::getCellDrawSize() {
    if (width < height) {
        return width / game->getWidth(); 
    } return height / game->getHeight();
}

void Display::mouseToGridCoordinates(int x, int y, int *resultX, int *resultY) {
    int cellSize = getCellDrawSize();
    *resultX = x / cellSize;
    *resultY = y / cellSize;
}

void Display::drawGame(SDL_Renderer *renderer, bool pause) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    Cell **grid = game->getGrid();
    int cellSize = this->getCellDrawSize();
    SDL_Rect rect;
    for (int x = 0; x < game->getWidth(); ++x) {
        for (int y = 0; y < game->getHeight(); ++y) {
            if (grid[x][y].isAlive()) {
                rect =  (SDL_Rect) {
                    cellSize * x, cellSize * y, cellSize, cellSize
                };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    if (!pause) return;
    for (int i = 0; i < width; ++i) {
        SDL_RenderDrawLine(renderer, cellSize * i, 0, cellSize * i, height);
    }
    for (int i = 0; i < height; ++i) {
        SDL_RenderDrawLine(renderer, 0, cellSize * i, width, cellSize * i);
    }
}
