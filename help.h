#include <windows.h>
#include <iostream>
using namespace std;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void myLine(int x1, int y1, int x2, int y2, int color) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(color, color, color)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
}

// This function checks if any of the 5 cursor keys are pressed. 
// If any cursor key is pressed, then the function returns true, and whichKey identifies which of the 5 cursor keys is pressed.
// whichkey is assigned following values if any cursor key is pressed. 1 for left, 2 for up, 3 for right, 4 for left and 5 for enter.
bool isCursorKeyPressed(int& whichKey)   //whichKey passed as reference.... 
{
	char key;
	key = GetAsyncKeyState(37);
	if (key == 1)
	{
		whichKey = 1;		// 1 if left key is pressed 
		return true;
	}
	key = GetAsyncKeyState(38);
	if (key == 1)
	{

		whichKey = 2;		// 2 if up key is pressed
		return true;
	}

	key = GetAsyncKeyState(39);
	if (key == 1)
	{

		whichKey = 3; // 3 if right key is pressed
		return true;
	}
	key = GetAsyncKeyState(40);
	if (key == 1)
	{

		whichKey = 4;   // 4 if down key is pressed
		return true;
	}
	key = GetAsyncKeyState(13);
	if (key == 1)
	{

		whichKey = 5;   // 5 if enter key is pressed
		return true;
	}
	return false;
}

void myRect(int x1, int y1, int x2, int y2, int R, int G, int B, int a, int b, int c)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(a, b, c)); //Fill color can also be passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(245, 245, 245));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}


//***********************************************************************************************************
//***************************************FUNCTIONS WE ADDED OURSELVES****************************************
//***********************************************************************************************************

//This function draws an 8-by-8 grid
void Grid()
{
	//border
	myRect(52, 12, 548, 508, 100, 25, 62, 245, 245, 245);
	myRect(54, 14, 546, 506, 100, 25, 62, 245, 245, 245);
	myRect(56, 16, 544, 504, 100, 25, 62, 245, 245, 245);
	myRect(58, 18, 542, 502, 100, 25, 62, 245, 245, 245);

	//vertical lines
	for (int j = 60; j <= 540; j += 60)
	{
		myLine(j, 20, j, 500, 140);
		myLine(j - 1, 20, j - 1, 500, 140);
	}

	//horizontal lines
	for (int j = 20; j <= 500; j += 60)
	{
		myLine(60, j, 540, j, 140);
		myLine(60, j - 1, 540, j - 1, 140);
	}
}

//this function will be used foe making the shapes
void shapeLine(int x1, int y1, int x2, int y2, int R, int G, int B) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(R, G, B)); //4 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
}

//This function is to make the selector
void Selector(int x, int y)
{
	shapeLine(x, y, x + 60, y, 200, 15, 52);
	shapeLine(x, y, x, y + 60, 200, 15, 52);
	shapeLine(x + 60, y, x + 60, y + 60, 200, 15, 52);
	shapeLine(x, y + 60, x + 60, y + 60, 200, 15, 52);
}

//This function is to remove the selector from its previous position
void removeSelector(int x, int y)
{
	shapeLine(x, y, x + 60, y, 140, 140, 140);
	shapeLine(x, y, x, y + 60, 140, 140, 140);
	shapeLine(x + 60, y, x + 60, y + 60, 140, 140, 140);
	shapeLine(x, y + 60, x + 60, y + 60, 140, 140, 140);
}

//*****Shapes to be distributed in the grid*****

void Triangle(int x, int y)// pass the block coordinates to print triangle
{
	int x1 = x - 1, y1 = y + 3;
	int x2 = x1 + 32, y2 = y1, x3 = (x1 + x2) / 2, y3 = y1 + 27;
	shapeLine(x1, y1, x2, y2, 255, 125, 47);
	shapeLine(x1, y1, x3, y3, 255, 125, 47);
	shapeLine(x2, y2, x3, y3, 255, 125, 47);
}

void Star(int x, int y)// pass the block coordinates to print star
{
	int x1 = x - 1, y1 = y + 3;
	int x2 = x1 + 32, y2 = y1, x3 = (x1 + x2) / 2, y3 = y1 + 29;
	shapeLine(x1, y1, x2, y2, 102, 51, 153);
	shapeLine(x1, y1, x3, y3, 102, 51, 153);
	shapeLine(x2, y2, x3, y3, 102, 51, 153);
	y1 = y1 + 20;
	y2 = y2 + 20;
	y3 = y3 - 39;
	shapeLine(x1, y1, x2, y2, 102, 51, 153);
	shapeLine(x1, y1, x3, y3, 102, 51, 153);
	shapeLine(x2, y2, x3, y3, 102, 51, 153);
}


void Square(int x, int y) // pass the block coordinates to print square
{
	myRect(x, y, x + 30, y + 30, 19, 119, 17, 245, 245, 245);
}


void Circle(int x, int y) // pass the block coordinates to print circle
{
	myEllipse(x, y, x + 30, y + 30, 180, 0, 0);
}

void Cross(int x, int y)// pass the block coordinates to print cross
{
	shapeLine(x, y, x + 27, y + 27, 50, 50, 50);
	shapeLine(x + 27, y, x, y + 27, 50, 50, 50);
}

//to ramdomly distribute shapes in the array
void Randomize(int arr[][8])
{
	// to randomly select and assign numbers to an array

	int symbol, num;
	srand((unsigned)time(0));
	for (int x = 0; x <= 7; x = x + 1)
	{
		for (int y = 0; y <= 7; y = y + 1)
		{
			symbol = 1 + (rand() % 5); // 1 signifies the start value and 5 the end value. 
			if (arr[x][y] == 0)
				arr[x][y] = symbol;
		}
	}

	int row = 0;
	for (int x = 75; x < 540; x = x + 60) // to print the symbols according to their values in the array
	{
		int column = 0;
		for (int y = 35; y < 500; y = y + 60)
		{
			num = arr[row][column];
			switch (num)
			{
			case 1: Square(x, y); // 1 is square
				break;
			case 2: Circle(x, y); // 2 is circle
				break;
			case 3: Cross(x, y); // 3 is cross
				break;
			case 4: Star(x, y); // 4 is star
				break;
			case 5: Triangle(x, y); // 5 is triangle
				break;
			default:
				break;
			}
			column++;
		}
		row++;
	}
}

//to make a copy of orriginal array
void Copy(int originalArr[][8], int copiedArr[][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			copiedArr[i][j] = originalArr[i][j];
}

//to check if the shapes can be swapped
bool CanSwap(int copied[][8])
{
	int flag = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 1; j < 8; j++)
		{
			//to check horizontally
			if (copied[i][j] == copied[i + 1][j] && copied[i][j] == copied[i + 2][j]
				|| copied[i][j] == copied[i + 1][j] && copied[i][j] == copied[i - 1][j]
				|| copied[i][j] == copied[i - 1][j] && copied[i][j] == copied[i - 2][j])
				return true;

			//to check vertically
			if (copied[i][j] == copied[i][j + 1] && copied[i][j] == copied[i][j + 2]
				|| copied[i][j] == copied[i][j + 1] && copied[i][j] == copied[i][j - 1]
				|| copied[i][j] == copied[i][j - 1] && copied[i][j] == copied[i][j - 2])
				flag = 1;
		}
	return flag;
}

//to print shapes according to their value in the array
void PrintShapes(int arr[][8])
{
	int row = 0;
	for (int x = 75; x < 540; x = x + 60) // to print the symbols according to their values
	{

		int column = 0;
		for (int y = 35; y < 500; y = y + 60)
		{
			int num = arr[row][column];
			int x1 = x - 15, y1 = y - 15;
			myRect(x1, y1, x1 + 60, y1 + 60, 140, 140, 140, 245, 245, 245);
			switch (num)
			{
			case 1: Square(x, y); // 1 is square
				break;
			case 2: Circle(x, y); // 2 is circle
				break;
			case 3: Cross(x, y); // 3 is cross
				break;
			case 4: Star(x, y); // 4 is star
				break;
			case 5: Triangle(x, y); // 5 is triangle
				break;
			default:
				break;
			}
			column++;
		}
		row++;
	}
}

//to check and delete three or more consecutive shapes
void CheckAndDelete(int arr[][8], int& score)
{
	//for horizontal deletion
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])
			{
				int count = 0, flag = 0;

				for (int a = i; a < 7 && flag == 0; a++)
				{
					if (arr[a][j] == arr[a + 1][j])
					{
						count++;
						score += 100;
					}
					else
						flag = 1;
				}
				for (int a = i + count; a >= i; a--)
				{
					for (int b = j; b > 0; b--)
						arr[a][b] = arr[a][b - 1];
					arr[a][0] = 0;
				}
			}

	// for vertical deletion 
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])
			{
				int count = 0, flag = 0;

				for (int b = j; b < 7 && flag == 0; b++)
				{
					if (arr[i][b] == arr[i][b + 1])
					{
						count++;
						score += 100;
					}
					else
						flag = 1;
				}
				for (int b = j + count; b >= count; b--)
					arr[i][b + 1] = arr[i][b - count];

				for (int b = count; b >= 0; b--)
					arr[i][b] = 0;
			}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (arr[i][j] == 0)
			{
				arr[i][j] = 1 + rand() % 5;
				PrintShapes(arr);
			}
}










