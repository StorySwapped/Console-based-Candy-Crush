#include <iostream>
#include <time.h>
#include "help.h"

using namespace std;

int main()
{
    int key1 = 0;
    gotoxy(50, 12);

    gotoxy(50, 11);
    cout << "INSTRUCTIONS";
    gotoxy(15, 13);
    cout << "1. Use arrow keys to move the selector.";
    gotoxy(15, 14);
    cout << "2. If you want to swap: Press enter + an arrow key(in the direction you want to swap)";
    Sleep(4000);
    gotoxy(0, 0);
    system("cls");

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    int block[8][8], copied[8][8], x = 60, y = 20, row = 0, column = 0, score = 0, key = 0;

    Grid();
    Randomize(block);

    for (int i = 1; i <= 20; i++)
        CheckAndDelete(block, score);

    score = 0;
    time_t timeStart = clock();
    int n = 1;
    while (n > 0)
    {
        Copy(block, copied);
        CheckAndDelete(block, score);//this will delete three or more consecutive entries
        if (n % 500 == 0)
        {
            if (65 - clock() / 1000 >= 10)
                cout << "\r\t" << "TIME LEFT: " << 65 - clock() / 1000 << "s\t\t\t\tSCORE: " << score;
            else
                cout << "\r\t" << "TIME LEFT: 0" << 65 - clock() / 1000 << "s\t\t\t\tSCORE: " << score;
        }

        key = 0;
        isCursorKeyPressed(key);//selector movement according to the arrow keys
        if (key != 0)
        {
            removeSelector(x, y);
        }
        if (key == 1 && x > 60)
        {
            x -= 60;
            row--;
        }
        else if (key == 2 && y > 20)
        {
            y -= 60;
            column--;
        }
        else if (key == 3 && x < 480)
        {
            x += 60;
            row++;
        }
        else if (key == 4 && y < 430)
        {
            y += 60;
            column++;
        }
        else if (key == 5)
        {
            CheckAndDelete(block, score);
            int key = 0;
            while (key == 0)
            {
                Selector(x, y);
                Sleep(100);
                removeSelector(x, y);
                Sleep(60);

                isCursorKeyPressed(key);
                if (key == 1 && x > 60)
                {
                    swap(copied[row][column], copied[row - 1][column]);
                    if (CanSwap(copied) == true)
                        swap(block[row][column], block[row - 1][column]);
                }
                else if (key == 2 && y > 20)
                {
                    swap(copied[row][column], copied[row][column - 1]);
                    if (CanSwap(copied) == 1)
                        swap(block[row][column], block[row][column - 1]);
                }
                else if (key == 3 && x < 480)
                {
                    swap(copied[row][column], copied[row + 1][column]);
                    if (CanSwap(copied) == 1)
                        swap(block[row][column], block[row + 1][column]);
                }
                else if (key == 4 && y < 440)
                {
                    swap(copied[row][column], copied[row][column + 1]);
                    if (CanSwap(copied) == 1)
                        swap(block[row][column], block[row][column + 1]);
                }
                if (key != 0)
                {
                    PrintShapes(block);
                    CheckAndDelete(block, score);
                }
            }
        }
        Selector(x, y);
        if ((clock() - timeStart) / CLOCKS_PER_SEC >= 60)
            break;
        n++;
    }
    system("cls");
    gotoxy(53, 14);
    cout << "GAME ENDED!";
    gotoxy(50, 16);
    cout << "YOUR SCORE: " << score;
    while (1);
    return 0;
}
