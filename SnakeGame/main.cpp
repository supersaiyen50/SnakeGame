#include <conio.h> 
#include <iostream> 
#include <windows.h>
using namespace std;

//size of game board
const int width = 80;
const int height = 20;

//head co-ords of snake
int x, y;
//food co-ords
int foodCoordx, foodCoordy;
//players score
int playerScore;
//array to store tail coords to calculate collision (x,y)
int TailX[100], TailY[100];
//snake Length
int snakeTailLen;
//storing direction of snake
enum snakeDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
//direction variable
snakeDirection sDir;
//bool is game over
bool isGameOver;


void GameInit() {
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    foodCoordx = rand() % width;
    foodCoordy = rand() % height;
    playerScore = 0;
}

void GameRender(string playerName)
{
    system("cls"); // Clear the console 

    // Creating top walls with '-' 
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            // Creating side walls with '|' 
            if (j == 0 || j == width)
                cout << "|";
            // Creating snake's head with 'O' 
            if (i == y && j == x)
                cout << "O";
            // Creating the sanke's food with '#' 
            else if (i == foodCoordy && j == foodCoordx)
                cout << "#";
            // Creating snake's head with 'O' 
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (TailX[k] == j
                        && TailY[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    // Creating bottom walls with '-' 
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    // Display player's score 
    cout << playerName << "'s Score: " << playerScore
        << endl;
}

void UpdateGame()
{
    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // Checks for snake's collision with the wall (|) 
    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    // Checks for collision with the tail (o) 
    for (int i = 0; i < snakeTailLen; i++) {
        if (TailX[i] == x && TailY[i] == y)
            isGameOver = true;
    }

    // Checks for snake's collision with the food (#) 
    if (x == foodCoordx && y == foodCoordy) {
        playerScore += 10;
        foodCoordx = rand() % width;
        foodCoordy = rand() % height;
        snakeTailLen++;
    }
}

int SetDifficulty() {
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
            "\nNOTE: if not chosen or pressed any other "
            "key, the difficulty will be automatically set "
            "to medium\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
    case '1':
        dfc = 100;
        break;
    case '2':
        dfc = 150;
        break;
    case '3':
        dfc = 200;
        break;
    default:
        dfc = 150;
    }
    return dfc;
}

// Function to handle user UserInput 
void UserInput()
{
    // Checks if a key is pressed or not 
    if (_kbhit()) {
        // Getting the pressed key 
        switch (_getch()) {
        case 'a':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 'w':
            sDir = UP;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}

// Main function / game looping function 
int main()
{
    string playerName;
    cout << "enter your name: ";
    cin >> playerName;
    int dfc = SetDifficulty();

    GameInit();
    while (!isGameOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        // creating a delay for according to the chosen 
        // difficulty 
        Sleep(dfc);
    }

    return 0;
}