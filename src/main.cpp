//
// Created by Tom Malhi on 26/05/2023.
//

#include <iostream>
#include <SDL.h>
#include <map>
#include "Game.h"
#include "Display.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
            "Game of Life",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool run = true, pause = true;
    Game *game = new Game(50, 50);
    const char *fileName = "/Users/tom/CLionProjects/gameOfLife/mapData/gridData.txt";
    int err = game->fSetPosition(fileName);
    if (err)
        std::cout << "File didn't open." << std::endl;
    auto *display = new Display(game, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->expandToFitScreen(SCREEN_WIDTH, SCREEN_HEIGHT,
                            display->getCellDrawSize());
    int mouseX, mouseY;
    // selected coordinates
    int curX, curY;
    while (run) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        display->drawGame(renderer, pause);
        if (!pause) {
            game->update();
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_SPACE:
                            pause = !pause;
                            break;
                        case SDLK_c:
                            game->clearGrid();
                            break;
                        case SDLK_r:
                            game->fSetPosition(fileName);
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (e.button.button) {
                        case SDL_BUTTON_LEFT:
                            if (!pause) break;
                            SDL_GetMouseState(&mouseX, &mouseY);
                            display->mouseToGridCoordinates(
                                    mouseX, mouseY, &curX, &curY);
                            game->flipCell(curX, curY);
                            std::cout << curX << ", " << curY << std::endl;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    run = false;
                    break;
                default:
                    break;
            }
        }
    }

    const char *outputFileName = "/Users/tom/CLionProjects/gameOfLife/mapData/output.txt";
    game->fSave(outputFileName);

    delete game;
    delete display;
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}