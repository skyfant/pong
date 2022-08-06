#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int screenWidth = 1000;
const int screenHeight = 800;

static int player1Score = 0;
static int player2Score = 0;


typedef struct {
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;
    float radius;
} Ball;

typedef struct{
    float positionY;
    float velocity;
} Paddle;


static Ball ball = {screenWidth / 2.00f, screenHeight / 2.00f, 5.00f, 10.00f, 15.00f};

static Paddle paddle1 = {screenHeight / 2.00f - 80.00f, 8.00f};    // 80 half of paddle 
static Paddle paddle2 = {screenHeight / 2.00f - 80.00f, 8.00f};


void BallDrawMove(void) {

    DrawCircle(ball.positionX, ball.positionY, ball.radius, RAYWHITE);

    // move ball

    ball.positionX += ball.velocityX;
    ball.positionY += ball.velocityY;
    
    // check for horizontal wall collision

    if (ball.positionY > screenHeight - ball.radius || ball.positionY < 0 + ball.radius) {
        ball.velocityY *= -1;
    }
}


void Paddles(void) {

    DrawRectangle(20.00f, paddle1.positionY, 20.00f, 160.00f, RAYWHITE);
    DrawRectangle(screenWidth - 40.00f, paddle2.positionY, 20.00f, 160.00f, RAYWHITE);

    // move paddles

    if (IsKeyDown(KEY_W)) {
        paddle1.positionY -= paddle1.velocity;
    }
    else if (IsKeyDown(KEY_S)) {
        paddle1.positionY += paddle1.velocity;
    }

    if (IsKeyDown(KEY_UP)) {
        paddle2.positionY -= paddle2.velocity;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        paddle2.positionY += paddle2.velocity;
    }

    // stop paddles at top and buttom

    if (paddle1.positionY + 160.00f > screenHeight) {
        paddle1.positionY = screenHeight - 160.00f;
    }
    else if (paddle1.positionY < 0) {
        paddle1.positionY = 0;
    }

    if (paddle2.positionY + 160.00f > screenHeight) {
        paddle2.positionY = screenHeight - 160.00f;
    }
    else if (paddle2.positionY < 0) {
        paddle2.positionY = 0;
    }
}    
    
void HandleBallPaddleCollision(void) {
    if (ball.positionX == 40 + ball.radius && ball.positionY > paddle1.positionY && ball.positionY < paddle1.positionY + 160.00f) {
        ball.velocityX *= -1;
        ball.positionX = 40 + ball.radius;
    }
    else if (ball.positionX == screenWidth - 40 - ball.radius && ball.positionY > paddle2.positionY && ball.positionY < paddle2.positionY + 160.00f) {
        ball.velocityX *= -1;
        ball.positionX = screenWidth - 40 - ball.radius;
    }
}

void Points(void) {
    if (ball.positionX < 0 - ball.radius) {
        player2Score++;
        paddle1.positionY = screenHeight / 2.00f - 80.00f;
        paddle2.positionY = screenHeight / 2.00f - 80.00f;
        ball.positionX = screenWidth / 2.00f;
        ball.positionY = screenHeight / 2.00f;
    }
    else if (ball.positionX > screenWidth + ball.radius) {
        player1Score++;
        paddle1.positionY = screenHeight / 2.00f - 80.00f;
        paddle2.positionY = screenHeight / 2.00f - 80.00f;
        ball.positionX = screenWidth / 2.00f;
        ball.positionY = screenHeight / 2.00f;
    }
    
    char player1ScoreString[20]; 
    char player2ScoreString[20];
    sprintf(player1ScoreString, "%d", player1Score);
    sprintf(player2ScoreString, "%d", player2Score);

    DrawText(player1ScoreString, screenWidth / 4, 60, 40, RAYWHITE);
    DrawText(player2ScoreString, screenWidth / 4 * 3, 60, 40, RAYWHITE);

}


int main(void) {

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);
    bool paused = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            
            if (IsKeyPressed(KEY_SPACE)) {
                paused = !paused;
            }
            if (paused) {
                DrawText("Paused", screenWidth / 2.00f - 80.00f, screenHeight / 2.00f - 100.00f, 50, WHITE);
                Points();
            }
            else {
 
            BallDrawMove();

            Paddles();

            HandleBallPaddleCollision();

            Points();

            DrawFPS(10, 10);
            }

        EndDrawing();
    }

    CloseWindow();
}

