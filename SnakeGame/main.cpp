#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
void gotoxy( int column, int line );

struct Point {
    int x, y;
};

const int MOVING_DISTANCE = 1;

const int WIDTH = 50;
const int HEIGHT = 20;

class SNAKE {
    public:
        Point snake[100];
        int snakeLength;
        Point food;

        SNAKE(){
            snakeLength = 3;
            snake[0].x = 10; snake[0].y = 10;
            snake[1].x = 11; snake[1].y = 10;
            snake[2].x = 12; snake[2].y = 10;

            generateFood();
        }

        void drawSnake(){
            for (int i = 0; i < snakeLength; i++){
                if (i == 0) {
                    gotoxy(snake[i].x, snake[i].y);
                    cout << "O";
                }
                gotoxy(snake[i].x, snake[i].y);
                cout << "o";
            }
        }

        void drawFood() {
            gotoxy(food.x, food.y);
            cout << "*";
        }

        void moveSnake(int direction){
            for (int i = snakeLength - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }
            if (direction==0) snake[0].x += MOVING_DISTANCE;
            if (direction==1) snake[0].y += MOVING_DISTANCE;
            if (direction==2) snake[0].x -= MOVING_DISTANCE;
            if (direction==3) snake[0].y -= MOVING_DISTANCE;

            // eat food
            if (snake[0].x == food.x && snake[0].y == food.y) {
                snakeLength++;
                generateFood();
            }
        }
        // FOOD
        bool isFoodValid(Point newFood) {
            for (int i = 0; i < snakeLength; i++ ) {
                if (newFood.x == snake[i].x && newFood.y == snake[i].y)
                    return false;
            }
            return true;
        }

        void generateFood() {
            do  {
                food.x = rand() % (WIDTH - 2) + 1;
                food.y = rand() % (HEIGHT - 2) + 1;
            } while (!isFoodValid(food));
        }
};



void drawGameArea() {
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < WIDTH; j++) {
            cout << " ";
        }
        cout << "|" << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "-";
    }
    cout << endl;
}

void gotoxy( int column, int line ) {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
}

int main()
{
    SNAKE snake;
    char t;
    int direction = 0;

    drawGameArea();
    snake.drawFood();
    snake.drawSnake();

    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') direction = 2;
            if (t=='w') direction = 3;
            if (t=='d') direction = 0;
            if (t=='s') direction = 1;
        }
        snake.moveSnake(direction);
        snake.drawFood();
        snake.drawSnake();
        Sleep(300);
    }

    return 0;
}



