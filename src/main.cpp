#include <iostream>
#include "SDL2/SDL.h"
#include "graphics.h"
#include "game.h"

using namespace std;

int ball_x;
int ball_y;

int paddle_x;
int paddle_y;


// left-paddle collisions
void leftCollision(PaddleLeft& paddle, Ball& ball) {
    ball_x = ball.getX() - (15/2);
    ball_y = ball.getY() + (15/2);
    paddle_x = paddle.getX();
    paddle_y = paddle.getY();

    if ((ball_x >= paddle_x && ball_x <= (paddle_x + 10)) && (ball_y <= paddle_y && ball_y >= (paddle_y - (WINDOW_HEIGHT / 6)))) {
        ball.setVelocity(ball.getVX() * -1, ball.getVY());
    }
}

// right-paddle collisions
void rightCollision(PaddleRight& paddle, Ball& ball) {
    ball_x = ball.getX() + (15/2);
    ball_y = ball.getY() + (15/2);
    paddle_x = paddle.getX();
    paddle_y = paddle.getY();

    if ((ball_x <= paddle_x && ball_x >= (paddle_x - 10)) && (ball_y <= paddle_y && ball_y >= (paddle_y - (WINDOW_HEIGHT / 6)))) {
        ball.setVelocity(ball.getVX() * -1, ball.getVY());
    }
}

// left paddle input
bool leftInput(const Uint8* keyboard, PaddleLeft& left_paddle) {
    if (keyboard[SDL_SCANCODE_W] == true && keyboard[SDL_SCANCODE_S] == true) return false;

    if (keyboard[SDL_SCANCODE_W]) {
        left_paddle.move_up();
        return true;
    }
    
    if (keyboard[SDL_SCANCODE_S]) {
        left_paddle.move_down();
        return true;
    }

    return false;
}

// right paddle input
bool rightInput(const Uint8* keyboard, PaddleRight& right_paddle) {
    if (keyboard[SDL_SCANCODE_UP] == true && keyboard[SDL_SCANCODE_DOWN] == true) return false;

    if (keyboard[SDL_SCANCODE_UP]) {
        right_paddle.move_up(); 
        return true;
    }

    if (keyboard[SDL_SCANCODE_DOWN]) {
        right_paddle.move_down();
        return true;
    }

    return false;
}

int main() {
    // initialize SDL Components
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // setup the game data
    setBounds();
    initGameConstants();
    PaddleLeft left_paddle = PaddleLeft();
    PaddleRight right_paddle = PaddleRight();
    Ball ball = Ball();
    
    // mouse data
    int mouse_x;
    int mouse_y;

    // keyboard data
    const Uint8* keyboard = SDL_GetKeyboardState(NULL); // array of key state

    // game loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                // x button
                case SDL_QUIT:
                    running = false;

                // keyboard
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;

                        default: {}
                    }

                // mouse
                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button) {
                        // left click
                        case SDL_BUTTON_LEFT:
                            SDL_GetMouseState(&mouse_x, &mouse_y); // pass by reference

                        default: {}
                    }
                
                default: {}
            }
        }

        // clear the window to black
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer);

        //---------------------------------------------------------------------------------------------------
        drawHalfWay(renderer); // draw the half-way line        

        // paddle input
        leftInput(keyboard, left_paddle);
        rightInput(keyboard, right_paddle);

        // paddle rendering
        left_paddle.render(renderer);
        right_paddle.render(renderer);

        // ball rendering
        ball.vertCollisions();
        ball.horCollisions();
        ball.update();
        ball.render(renderer);

        // paddle collisions
        leftCollision(left_paddle, ball);
        rightCollision(right_paddle, ball);
        //---------------------------------------------------------------------------------------------------

        // present the back buffer
        SDL_RenderPresent(renderer);
    }

    // clean it up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
