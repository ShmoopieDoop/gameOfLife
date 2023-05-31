//
// Created by Tom Malhi on 25/05/2023.
//

#include "Cell.h"

Cell::Cell(int x, int y) {
    this->x = x;
    this->y = y;
    alive = false;
}

Cell::Cell(int x, int y, bool state) {
    this->x = x;
    this->y = y;
    alive = state;
}

void Cell::flip() {
    alive = !alive;
}

bool Cell::isAlive() const {
    return alive;
}

void Cell::setAlive(bool state) {
    alive = state;
}