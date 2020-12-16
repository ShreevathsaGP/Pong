#ifndef GAME_H_
#define GAME_H_

#include "SDL2/SDL.h"
#include "constants.h"
#include "graphics.h"

const int vertical_buffer = 10;
const int paddle_buffer = 20;
const int paddle_vert = 10;


// game data
struct GameData {
    int p1_points;
    int p2_points;
};

// init game constants
void initGameConstants();

// paddle-left 
class PaddleLeft {
    public:
        // no param constructor
        PaddleLeft();

        // move up
        void move_up();

        // move down
        void move_down();

        // render
        void render(SDL_Renderer* renderer);
        
        // get x
        int getX();

        // get y
        int getY();

    private:
        int x_left;
        int y_bottom;
        SDL_Rect paddle;
        
        // reset the paddle (widh new updated values)
        void resetPaddle();

};

// paddle-right
class PaddleRight {
    public:
        // no param constructor
        PaddleRight();

        // move up
        void move_up();

        // move down
        void move_down();

        // render
        void render(SDL_Renderer* renderer);

        // get x
        int getX();

        // get y
        int getY();

    private:
        int x_right;
        int y_bottom;
        SDL_Rect paddle;

        // reset the paddle (widh new updated values)
        void resetPaddle();
};

// ball
class Ball {
    public:
        // no param constructor
        Ball();

        // update ball position
        void update();

        // render the ball
        void render(SDL_Renderer* renderer);

        // reset the ball
        void resetBall();

        // vertical collisons
        void vertCollisions();

        // horizontal collisions
        void horCollisions();

        // get x
        int getX();

        // get y
        int getY();

        // set velocity
        void setVelocity(float x, float y);

        // get velocity x
        float getVX();

        // get velocity-y
        float getVY();

    private:
        int x;
        int y;
        SDL_Rect ball;
        Vector2D velocity;
};

#endif // GAME_H_
