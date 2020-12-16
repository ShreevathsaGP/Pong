#include <iostream>
#include <cmath>
#include "SDL2/SDL.h"
#include "constants.h"
#include "graphics.h"
#include "game.h"

#define PI 3.14159

using namespace std;

int paddle_length;
int paddle_width;
int ball_size;
double ball_mul;
int ball_velocity;

void initGameConstants() {
    paddle_length = WINDOW_HEIGHT / 6;
    paddle_width = 10;
    ball_size = 15;
    ball_mul = 1;
    ball_velocity = 4;
}

// paddle-left
// no param constructor
PaddleLeft::PaddleLeft() {
    x_left = paddle_buffer;
    y_bottom = (WINDOW_HEIGHT / 2) + (paddle_length / 2);

    // set up rectangle
    paddle.x = x_left;
    paddle.y = y_bottom - paddle_length;
    paddle.h = paddle_length;
    paddle.w = paddle_width;
}

// move up
void PaddleLeft::move_up() {
    if ((y_bottom - paddle_length) <= vertical_buffer) return;

    y_bottom -= paddle_vert;
    resetPaddle();
}

// move down
void PaddleLeft::move_down() {
    if ((y_bottom + paddle_vert) >= (WINDOW_HEIGHT - vertical_buffer)) return;

    y_bottom += paddle_vert;
    resetPaddle();
}

// reset the paddle (with updated values)
void PaddleLeft::resetPaddle() {
    paddle.x = x_left;
    paddle.y = y_bottom - paddle_length;
}

// render
void PaddleLeft::render(SDL_Renderer* renderer) {
    // set the render to white
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // draw and fill paddle
    /* SDL_RenderDrawRect(renderer, &paddle); */
    SDL_RenderFillRect(renderer, &paddle);
}

// paddle-right // no param constructor
PaddleRight::PaddleRight() {
    x_right = WINDOW_WIDTH - paddle_buffer;
    y_bottom = (WINDOW_HEIGHT / 2) + (paddle_length / 2);

    // set up rectangle
    paddle.x = x_right - paddle_width;
    paddle.y = y_bottom - paddle_length;
    paddle.h = paddle_length;
    paddle.w = paddle_width;
}

// move up
void PaddleRight::move_up() {
    if ((y_bottom - paddle_length) <= vertical_buffer) return;

    y_bottom -= paddle_vert;
    resetPaddle();
}

// move down
void PaddleRight::move_down() {
    if ((y_bottom + paddle_vert) >= (WINDOW_HEIGHT - vertical_buffer)) return;

    y_bottom += paddle_vert;
    resetPaddle();
}

// reset the paddle (with updated values)
void PaddleRight::resetPaddle() {
    paddle.x = x_right - paddle_width;
    paddle.y = y_bottom - paddle_length;
}

// render
void PaddleRight::render(SDL_Renderer* renderer) {
    // set the render to white
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    // draw and fill paddle
    /* SDL_RenderDrawRect(renderer, &paddle); */
    SDL_RenderFillRect(renderer, &paddle);
}

// get x
int PaddleLeft::getX() {
    return x_left;
}

// get y
int PaddleLeft::getY() {
    return y_bottom;
}

// get x
int PaddleRight::getX() {
    return x_right;
}

// get y
int PaddleRight::getY() {
    return y_bottom;
}

// no param constructor
Ball::Ball() {
    x = WINDOW_WIDTH / 2;
    y = WINDOW_HEIGHT / 2;
    velocity = Vector2D();
    velocity.x = ball_velocity;
    velocity.y = ball_velocity;

    // ball square
    resetBall();
    ball.w = ball_size;
    ball.h = ball_size;
}

// render the ball
void Ball::render(SDL_Renderer* renderer) {
    // set the render to white
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    
    // fill the ball
    SDL_RenderFillRect(renderer, &ball);
}

// update ball position
void Ball::update() {
    x += (ball_mul * velocity.x);
    y -= (ball_mul * velocity.y);

    resetBall();
}

// reset ball with updated values
void Ball::resetBall() {
    ball.x = x - (ball_size/2);
    ball.y = y - (ball_size/2);
}

// vertical collision
void Ball::vertCollisions() {
    // wall case
    if ((y - (ball_size / 2) <= 0) || (y + (ball_size / 2) >= WINDOW_HEIGHT)) {
        velocity.y = velocity.y * -1;
    }
}

void Ball::horCollisions() {
    // wall case
    if ((x - (ball_size /2) <= 0) || (x + (ball_size / 2) >= WINDOW_WIDTH)) {
        velocity.x = velocity.x * -1;
    }
}

// get x
int Ball::getX() {
    return x;
}

// get y
int Ball::getY() {
    return y;
}

// set velocity
void Ball::setVelocity(float in_x, float in_y) {
    velocity.x = in_x;
    velocity.y = in_y;
}

// get velocity-x
float Ball::getVX() {
    return velocity.x;
}


// get velocity-y
float Ball::getVY() {
    return velocity.y;
}
