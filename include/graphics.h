#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "constants.h"

// 2D Vector
struct Vector2D {
    float x;
    float y;
};

// draw the half-way line
void drawHalfWay(SDL_Renderer* renderer);

// set bounds
void setBounds();


#endif // GRAPHICS_H_
