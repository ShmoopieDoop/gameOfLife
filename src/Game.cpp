//
// Created by Tom Malhi on 25/05/2023.
//

#include "Game.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Game::Game(int width, int height) {
    this->width = width;
    this->height = height;
    this->grid = createGrid();
}

Game::~Game() {
    this->destroyGrid(grid);
}

Cell **Game::createGrid(int _width, int _height) {
    Cell **newGrid = (Cell **) malloc(sizeof(Cell *) * _width);
    Cell *column;
    for (int i = 0; i < _width; ++i) {
        column = (Cell *) malloc(sizeof(Cell) * _width);
        newGrid[i] = column;
        for (int j = 0; j < _height; ++j) {
            column[j] = Cell(j, i);
        }
    }
    return newGrid;
}
Cell **Game::createGrid() const {
    return createGrid(width, height);
}

Cell **Game::copyGrid(Cell **oldGrid) const {
    Cell **newGrid = createGrid();
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (oldGrid[i][j].isAlive()) {
                newGrid[i][j].flip();
            }
        }
    }
    return newGrid;
}

void Game::destroyGrid(Cell **g) const {
    for (int i = 0; i < width; ++i) {
        delete g[i];
    }
    delete g;
}

int Game::countLivingNeighbors(int x, int y) {
    int count = 0;
    if (0 < x && x < width - 1) {
        count += (int) grid[x][y + 1].isAlive();
        count += (int) grid[x][y - 1].isAlive();
    }
    if (x > 0) {
        count += (int) grid[x - 1][y].isAlive();
        if (y > 0) {
            count += (int) grid[x - 1][y - 1].isAlive();
        }
        if (y < height - 1) {
            count += (int) grid[x - 1][y + 1].isAlive();
        }
    }
    if (x < width - 1) {
        count += (int) grid[x + 1][y].isAlive();
        if (y > 0) {
            count += (int) grid[x + 1][y - 1].isAlive();
        }
        if (y < height - 1) {
            count += (int) grid[x + 1][y + 1].isAlive();
        }
    }
    return count;
}

void Game::update() {
    Cell **newGrid = copyGrid(grid);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (grid[x][y].isAlive()) {
                if (countLivingNeighbors(x, y) < 2
                    || countLivingNeighbors(x, y) > 3)
                    newGrid[x][y].flip();
            } else if (countLivingNeighbors(x, y) == 3) {
                newGrid[x][y].flip();
            }
        }
    }
    destroyGrid(grid);
    grid = newGrid;
}

int Game::fSetPosition(const char *fileName) {
    std::ifstream f(fileName);
    if (!f.is_open()) {
        return 1;
    }
    char cur;
    int x = 0, y = 0;
    while (f && y != height) {
        cur = (char) f.get();
        switch (cur) {
            case '1':
                grid[x][y].setAlive(true);
                break;
            case '0':
                grid[x][y].setAlive(false);
                break;
            case '\n':
                if (x) y++;
                x = -1;
                break;
            default:
                x--;
                break;
        }
        x++;
        if (x == width) {
            x = 0;
            y++;
        }
    }
    if (y != height)
        std::cout << "File does not have enough data. Grid not full."
                  << std::endl;
    f.close();
    return 0;
}

int Game::fSave(const char *fileName) {
    std::ofstream f(fileName);
    if (!f.is_open()) {
        return 1;
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[x][y].isAlive()) {
                f << '1';
            } else {
                f << '0';
            }
        }
        f << '\n';
    }
    f.close();
    return 0;
}

void Game::flipCell(int x, int y) {
    if (x >= width || y >= height)
        // expand grid
        return;
    grid[x][y].flip();
}

void Game::clearGrid() {
    destroyGrid(grid);
    grid = createGrid();
}

/*
 * generates a new larger grid copies the old grid into such that (0, 0) in the
 * old grid is now (x, y) in the new grid.
 */
void Game::expandGrid(int newWidth, int newHeight, int x, int y) {
    if (x + width > newWidth || y + height > newHeight)
        throw std::invalid_argument("Old grid must fit within new grid.");
    Cell **newGrid = createGrid(newWidth, newHeight);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            newGrid[x + i][y + j] = grid[i][j];
        }
    }
    destroyGrid(grid);
    grid = newGrid;
    width = newWidth;
    height = newHeight;
}

void Game::expandToFitScreen(int screenWidth, int screenHeight, int cellSize) {
    if (screenWidth / cellSize <= width && screenHeight / cellSize <= height)
        return;
    int newWidth = std::max(screenWidth / cellSize, width);
    int newHeight = std::max(screenHeight / cellSize, height);
    expandGrid(newWidth, newHeight, 0, 0);
}

