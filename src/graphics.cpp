#include <iostream>
#include "SDL2/SDL.h"
#include "constants.h"
#include "graphics.h"

using namespace std;

int middle;
int vert_space;
int one_length;

// set screen bounds
void setBounds() {
    // half-way line constants
    middle = WINDOW_WIDTH / 2;
    vert_space = 7;
    one_length = (WINDOW_HEIGHT - (vert_space * 10)) / 10; // we want 10 vertical lines
}

// draw the half-way line
void drawHalfWay(SDL_Renderer* renderer) {
    // set the render to white
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // draw half-way line
    for (int bottom = 0; bottom <= WINDOW_HEIGHT;) {
        SDL_RenderDrawLine(renderer, middle, bottom, middle, (bottom + one_length));
        bottom += one_length + vert_space;
    }
}

