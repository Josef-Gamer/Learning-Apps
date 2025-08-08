
#include <iostream>
#include <conio.h>     // For _kbhit() and _getch()
#include <windows.h>   // For Sleep()

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;

int ballX, ballY;
int ballDirX = 1, ballDirY = 1;
int leftPaddleY = HEIGHT / 2, rightPaddleY = HEIGHT / 2;
int leftScore = 0, rightScore = 0;

void Setup() {
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
}

void Draw() {
    system("cls");

    // Top border
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\n";

    for (int y = 0; y < HEIGHT; y++) {
        cout << "#";
        for (int x = 0; x < WIDTH; x++) {
            if (x == ballX && y == ballY)
                cout << "O"; // Ball
            else if (x == 1 && (y >= leftPaddleY - 1 && y <= leftPaddleY + 1))
                cout << "|"; // Left paddle
            else if (x == WIDTH - 2 && (y >= rightPaddleY - 1 && y <= rightPaddleY + 1))
                cout << "|"; // Right paddle
            else
                cout << " ";
        }
        cout << "#\n";
    }

    // Bottom border
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\n";

    // Score
    cout << "Player 1: " << leftScore << "  Player 2: " << rightScore << "\n";
}

void Input() {
    if (_kbhit()) {
        char key = _getch();
        // Player 1 (W/S)
        if (key == 'w' && leftPaddleY > 1) leftPaddleY--;
        if (key == 's' && leftPaddleY < HEIGHT - 2) leftPaddleY++;

        // Player 2 (Arrow keys)
        if (key == 72 && rightPaddleY > 1) rightPaddleY--; // Up arrow
        if (key == 80 && rightPaddleY < HEIGHT - 2) rightPaddleY++; // Down arrow
    }
}

void Logic() {
    ballX += ballDirX;
    ballY += ballDirY;

    // Top and bottom wall bounce
    if (ballY <= 0 || ballY >= HEIGHT - 1)
        ballDirY *= -1;

    // Left paddle collision
    if (ballX == 2 && ballY >= leftPaddleY - 1 && ballY <= leftPaddleY + 1)
        ballDirX *= -1;

    // Right paddle collision
    if (ballX == WIDTH - 3 && ballY >= rightPaddleY - 1 && ballY <= rightPaddleY + 1)
        ballDirX *= -1;

    // Scoring
    if (ballX <= 0) {
        rightScore++;
        Setup(); // Reset
    }
    if (ballX >= WIDTH - 1) {
        leftScore++;
        Setup(); // Reset
    }
}

int main() {
    Setup();
    while (true) {
        Draw();
        Input();
        Logic();
        Sleep(50); // Adjust speed
    }

    return 0;
}

