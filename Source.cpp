// For wrapped candies on the second phase, you can use .kind = 0 although, for aesthetic looking, we are keeping the isExploding.
// Phas 2 and positions done!

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;
using namespace System;

#define elderRow 9
#define elderColumn 9

#define timerTime_LAP 1000
#define amountTime 9
#define speedTime_LAP 1

#define dwellTime 9
#define showOffTime 30
#define fishingTime 50
#define xplodngTme 40
#define genTIMER 40

#define fromIni_C 1
#define ini_Candy 3

#define frominGame_C 1
#define inGame_candy 3

// Structs!
typedef struct
{
	int kind;
	int itemID;

	bool isToCrush;
	bool isNew;
	bool isExploding;
}theBoardplex;

// Calling functions!
void printScore(int multiplier, int scorePlayer);
void printInfoText(int n)
{
	Console::ForegroundColor = ConsoleColor::DarkGray;
	Console::SetCursorPosition((elderColumn * 2) + 1, n + 2);
}
void GraphicProcessingUnit(theBoardplex** theBoard);

// Initial Functions and Logic!
void createBoard(theBoardplex** theBoard)
{
	Random rpx;

	for (int i = 0; i < elderRow; i = i + 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			theBoard[i][c].kind = rpx.Next(fromIni_C, ini_Candy + 1);
			theBoard[i][c].itemID = theBoard[i][c].kind; theBoard[i][c].isNew = theBoard[i][c].isToCrush = theBoard[i][c].isExploding = false;
		}
	}
}
void reset_boolean_VALUES(theBoardplex** theBoard)
{
	for (int i = 0; i < elderRow; i = i + 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			theBoard[i][c].isNew = theBoard[i][c].isToCrush = false;
		}
	}
}

void isFalling(int posRow, bool* fallingVector, theBoardplex** theBoard)
{
	for (int c = 0; c < elderColumn; c = c + 1)
	{
		fallingVector[c] = false;

		for (int i = posRow; i < elderRow; i = i + 1)
		{
			if ((theBoard[i][c].kind == 0) && (theBoard[i][c].itemID == 0))
			{
				fallingVector[c] = true;
			}
		}
	}
}

// p_Functions, used by others!
void swapBoardItem(theBoardplex& r, theBoardplex& y)
{
	theBoardplex auxY;
	auxY = r;
	r = y;
	y = auxY;
}
void swapToVoid(theBoardplex** theBoard)
{
	for (int i = elderRow - 1; i > 0; i = i - 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			if (theBoard[i][c].itemID == 0)
			{
				swapBoardItem(theBoard[i][c], theBoard[i - 1][c]);
			}
		}
	}
}
void spawnNewCandy(theBoardplex** theBoard)
{
	Random rpx;

	for (int c = 0; c < elderColumn; c = c + 1)
	{
		if ((theBoard[0][c].kind == 0) && (theBoard[0][c].itemID == 0))
		{
			theBoard[0][c].kind = rpx.Next(frominGame_C, inGame_candy + 1);
			theBoard[0][c].itemID = theBoard[0][c].kind; //theBoard[0][c].kind;
			theBoard[0][c].isNew = false; theBoard[0][c].isToCrush = false;
		}
	}
}
bool explodeCandy_14(bool* fallingVector, theBoardplex** theBoard)
{
	bool isFinal = true;

	isFalling(0, fallingVector, theBoard);
	for (int n = 0; n < elderColumn; n = n + 1)
	{
		if (fallingVector[n] == true)
		{
			isFinal = false;
		}
	}

	return isFinal;
}

void verifierCrush(int i, int c, theBoardplex** theBoard); // Letting know...

void continueFallingCascade(bool& isCascade, theBoardplex** theBoard)
{
	for (int i = 0; i < elderRow; i = i + 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			if (theBoard[i][c].itemID == 0)
			{
				isCascade = true;
			}
		}
	}
}
int selectingGreatBomOBomProcs(theBoardplex** theBoard)
{
	int* picoVector;
	picoVector = new int[10];
	for (int n = 0; n < 10; n = n + 1)
	{
		picoVector[n] = 0;
	}
	int greatAmount, kind_N;

	for (int i = 0; i < elderRow; i = i + 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			picoVector[0] = picoVector[0] + (theBoard[i][c].kind == 1); picoVector[1] = picoVector[1] + (theBoard[i][c].kind == 2); picoVector[2] = picoVector[2] + (theBoard[i][c].kind == 3);
			picoVector[3] = picoVector[3] + (theBoard[i][c].kind == 4); picoVector[4] = picoVector[4] + (theBoard[i][c].kind == 5); picoVector[5] = picoVector[5] + (theBoard[i][c].kind == 6);
			picoVector[6] = picoVector[6] + (theBoard[i][c].kind == 7); picoVector[7] = picoVector[7] + (theBoard[i][c].kind == 8); picoVector[8] = picoVector[8] + (theBoard[i][c].kind == 9);
			picoVector[9] = picoVector[9] + (theBoard[i][c].kind == 10);
		}
	}

	/* / / / / / / / / / / / / / / / / / / / */
	greatAmount = picoVector[0];
	kind_N = 1;
	
	for (int h = 0; h < 10; h = h + 1)
	{
		if (greatAmount < picoVector[h])
		{
			greatAmount = picoVector[h];
			kind_N = h + 1;
		}
	}

	delete[] picoVector;
	return kind_N;
}
int selectingGreatColorantProcs(int kindID, theBoardplex** theBoard)
{
	int* picoVector;
	picoVector = new int[10];
	for (int n = 0; n < 10; n = n + 1)
	{
		picoVector[n] = 0;
	}
	int greatAmount, kind_N;

	for (int i = 0; i < elderRow; i = i + 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			picoVector[0] = picoVector[0] + (theBoard[i][c].kind == 1); picoVector[1] = picoVector[1] + (theBoard[i][c].kind == 2); picoVector[2] = picoVector[2] + (theBoard[i][c].kind == 3);
			picoVector[3] = picoVector[3] + (theBoard[i][c].kind == 4); picoVector[4] = picoVector[4] + (theBoard[i][c].kind == 5); picoVector[5] = picoVector[5] + (theBoard[i][c].kind == 6);
			picoVector[6] = picoVector[6] + (theBoard[i][c].kind == 7); picoVector[7] = picoVector[7] + (theBoard[i][c].kind == 8); picoVector[8] = picoVector[8] + (theBoard[i][c].kind == 9);
			picoVector[9] = picoVector[9] + (theBoard[i][c].kind == 10);
		}
	}

	/* / / / / / / / / / / / / / / / / / / / */
	if (0 != (kindID - 1))
	{
		greatAmount = picoVector[0];
		kind_N = 1;
	}
	else
	{
		greatAmount = picoVector[1];
		kind_N = 2;
	}

	for (int h = 0; h < 10; h = h + 1)
	{
		if ((greatAmount < picoVector[h]) && (h != (kindID - 1)))
		{
			greatAmount = picoVector[h];
			kind_N = (h + 1);
		}
	}

	delete[] picoVector;
	return kind_N;
}
void fish__AI(int& ROW_Selector, int& COLUMN_Selector,theBoardplex** theBoard)
{
	Random rkx;
	bool isVoid = true;
	bool isVoid_ALL = true;

	for (int i = 0; i < elderRow; i = i + 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			if ((theBoard[i][c].kind != 0) && (theBoard[i][c].itemID != 0) && (theBoard[i][c].itemID != 14) && (theBoard[i][c].isToCrush != true))
			{
				isVoid_ALL = false;
			}
		}
	}

	if (!isVoid_ALL)
	{
		ROW_Selector = rkx.Next(0, elderRow);
		do
		{
			for (int c = 0; c < elderRow; c = c + 1)
			{
				if ((theBoard[ROW_Selector][c].kind != 0) && (theBoard[ROW_Selector][c].itemID != 0) && (theBoard[ROW_Selector][c].itemID != 14) && (theBoard[ROW_Selector][c].isToCrush != true))
				{
					isVoid = false;
				}
			}

			if (isVoid)
			{
				if (ROW_Selector == elderRow - 1)
				{
					ROW_Selector = 0;
				}
				else
				{
					ROW_Selector = ROW_Selector + 1;
				}
			}
		} while (isVoid);

		isVoid = true;
		COLUMN_Selector = rkx.Next(0, elderColumn);
		do
		{
			if ((theBoard[ROW_Selector][COLUMN_Selector].kind != 0) && (theBoard[ROW_Selector][COLUMN_Selector].itemID != 0) && (theBoard[ROW_Selector][COLUMN_Selector].itemID != 14) && (theBoard[ROW_Selector][COLUMN_Selector].isToCrush != true))
			{
				isVoid = false;
			}
			if (isVoid)
			{
				if (COLUMN_Selector == (elderColumn - 1))
				{
					COLUMN_Selector = 0;
				}
				else
				{
					COLUMN_Selector = COLUMN_Selector + 1;
				}
			}
		} while (isVoid);
	}
	else
	{
		ROW_Selector = rkx.Next(0, elderRow);
		COLUMN_Selector = rkx.Next(0, elderColumn);
	}
}
void Xploding_BooM(int i, int c, theBoardplex** theBoard)
{
	for (int n = (i - 1); n <= (i + 1); n = n + 2)
	{
		for (int m = (c - 1); m <= (c + 1); m = m + 1)
		{
			if ((((n >= 0) && (n < elderRow)) && ((m >= 0) && (m < elderColumn))) && (theBoard[n][m].itemID != 14) && (theBoard[n][m].itemID != 0))
			{
				verifierCrush(n, m, theBoard);
			}
		}
	}
	for (int o = (c - 1); o <= (c + 1); o = o + 2)
	{
		if ((((i >= 0) && (i < elderColumn)) && ((o >= 0) && (o < elderColumn))) && (theBoard[i][o].itemID != 14) && (theBoard[i][o].itemID != 0))
		{
			verifierCrush(i, o, theBoard);
		}
	}
}

void crushCandy(int i, int c, theBoardplex** theBoard)
{
	theBoard[i][c].kind = theBoard[i][c].itemID = 0;
	theBoard[i][c].isNew = false; theBoard[i][c].isToCrush = false;
}
void activateSpecial(int i, int c, theBoardplex** theBoard)
{
	// If you don't want the new candies to be crushed, just select a if for those isNew == true.
	int kind_N, kindID, ROW_Selector, COLUMN_Selector;

	switch (theBoard[i][c].itemID)
	{
	case 11:
		crushCandy(i, c, theBoard);

		for (int n = 1; n < elderColumn; n = n + 1)
		{
			if ((c + n) < elderColumn)
			{
				if (theBoard[i][c + n].itemID != 14)
				{
					verifierCrush(i, c + n, theBoard);
				}
			}
			if ((c - n) >= 0)
			{
				if (theBoard[i][c - n].itemID != 14)
				{
					verifierCrush(i, c - n, theBoard);
				}
			}
		}
		break;

	case 12:
		crushCandy(i, c, theBoard);

		for (int n = 1; n < elderRow; n = n + 1)
		{
			if ((i + n) < elderRow)
			{
				if (theBoard[i + n][c].itemID != 14)
				{
					verifierCrush(i + n, c, theBoard);
				}
			}
			if ((i - n) >= 0)
			{
				if (theBoard[i - n][c].itemID != 14)
				{
					verifierCrush(i - n, c, theBoard);
				}
			}
		}
		break;

	case 13:
		theBoard[i][c].itemID = 14;
		theBoard[i][c].isExploding = true;

		Sleep(xplodngTme);
		Xploding_BooM(i, c, theBoard);
		break;

	// case 14 being as a reserved space.

	case 15:
		kind_N = selectingGreatBomOBomProcs(theBoard);
		for (int i = 0; i < elderRow; i = i + 1)
		{
			for (int c = 0; c < elderColumn; c = c + 1)
			{
				if ((theBoard[i][c].kind == kind_N) && (theBoard[i][c].itemID != 14))
				{
					verifierCrush(i, c, theBoard);
					GraphicProcessingUnit(theBoard);
					Sleep(showOffTime);
				}
			}
		}
		crushCandy(i, c, theBoard);
		break;

	case 16:
		kindID = theBoard[i][c].kind;	
		kind_N = selectingGreatColorantProcs(kindID, theBoard);
		for (int i = 0; i < elderRow; i = i + 1)
		{
			for (int c = 0; c < elderColumn; c = c + 1)
			{
				if ((theBoard[i][c].kind == kind_N) && (theBoard[i][c].itemID != 14))
				{
					theBoard[i][c].kind = kindID;
					if (theBoard[i][c].itemID < 11)
					{
						theBoard[i][c].itemID = kindID;
						GraphicProcessingUnit(theBoard);
						Sleep(showOffTime);
					}
					else
					{
						GraphicProcessingUnit(theBoard);
						Sleep(showOffTime);
					}
				}
			}
		}
		crushCandy(i, c, theBoard);
		break;

	case 17:
		crushCandy(i, c, theBoard);
		fish__AI(ROW_Selector, COLUMN_Selector, theBoard);
		Sleep(fishingTime);
		verifierCrush(ROW_Selector, COLUMN_Selector, theBoard);
		break;
	}
}
void verifierCrush(int i, int c, theBoardplex** theBoard)
{
	if (theBoard[i][c].itemID > 10)
	{
		activateSpecial(i, c, theBoard);
	}
	else
	{
		crushCandy(i, c, theBoard);
	}
}
void isToCrush_Process(theBoardplex** theBoard)
{
	for (int i = 0; i < elderRow; i = i + 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			if (theBoard[i][c].isToCrush == true)
			{
				verifierCrush(i, c, theBoard);
			}
		}
	}
}

// Add functions to main or just find a factor like "What's common in among then? Sure, it'll take more time to brain up your answer...".
void findVerticalMatch(int i, int c , int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);
	
	if ((0 < i) && (i < elderRow - 1))
	{
		if (!fallingVector[c])
		{
			if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind)) && // Kind of candy.
				((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i + 1][c].isNew != true)) && // If special candies were form, use isNew field to not match the new candies.
				((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true)) && // For those candies which are already matched.
				((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true)) && // This for wrapped candies phase 2.
				//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i + 1][c].kind != 0))) // Not matching the void or any other candy.
			{
				theBoard[i][c].isToCrush = theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = true;
				playerScore = playerScore + (30 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findHorizontalMatch(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((0 < c) && (c < elderColumn - 1))
	{
		if ((!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c + 1].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c + 1].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c + 1].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c + 1].kind != 0)))

			{
				theBoard[i][c].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = true;
				playerScore = playerScore + (30 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findFishMatch(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((i < elderRow - 1) && (c < elderColumn - 1))
	{
		if ((!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0)))
			{
				theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = true;
				theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
				playerScore = playerScore + (40 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findFish_ClockEight(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if (((0 < i) && (i < elderRow - 1)) && (c < elderColumn - 1))
	{
		isFalling(i + 1, fallingVector, theBoard);
		if (!fallingVector[c + 1])
		{
			isFalling(i, fallingVector, theBoard);
			if (!fallingVector[c])
			{
				if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind) && (theBoard[i][c].kind == theBoard[i - 1][c].kind)) &&
					((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true) && (theBoard[i - 1][c].isNew != true)) && 
					((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true)) &&
					((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true) && (theBoard[i - 1][c].isExploding != true)) &&
					//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0) && (theBoard[i - 1][c].itemID != 0)) &&
					((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0) && (theBoard[i - 1][c].kind != 0)))
				{
					theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = theBoard[i - 1][c].isToCrush = true;
					theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
					playerScore = playerScore + (40 * multiplier);
					multiplier = multiplier + 1;
					printScore(multiplier, playerScore);
					Sleep(dwellTime);
				}
			}
		}
	}
}
void findFish_ClockSeven(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 1) && ((0 < c) && (c < elderColumn - 1)))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true) && (theBoard[i][c - 1].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true) && (theBoard[i][c - 1].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0) && (theBoard[i][c - 1].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0) && (theBoard[i][c - 1].kind != 0)))
			{
				theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = theBoard[i][c - 1].isToCrush = true;
				theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
				playerScore = playerScore + (40 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findFish_ClockSix(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 1) && ((0 < c) && (c < elderColumn - 1)))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			isFalling(i + 1, fallingVector, theBoard);
			if (!fallingVector[c - 1]) 
			{
				if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c - 1].kind)) &&
					((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true) && (theBoard[i + 1][c - 1].isNew != true)) &&
					((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true) && (theBoard[i + 1][c - 1].isToCrush != true)) &&
					((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true) && (theBoard[i + 1][c - 1].isExploding != true)) &&
					//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0) && (theBoard[i + 1][c - 1].itemID != 0)) &&
					((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0) && (theBoard[i + 1][c - 1].kind != 0)))
				{
					theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = theBoard[i + 1][c - 1].isToCrush = true;
					theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
					playerScore = playerScore + (40 * multiplier);
					multiplier = multiplier + 1;
					printScore(multiplier, playerScore);
					Sleep(dwellTime);
				}
			}
		}
	}
}
void findFish_ClockFive(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 2) && (c < elderColumn - 1))
	{
		isFalling(i + 2, fallingVector, theBoard);
		if ((!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true) && (theBoard[i + 2][c].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true) && (theBoard[i + 2][c].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0) && (theBoard[i + 2][c].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0) && (theBoard[i + 2][c].kind != 0)))
			{
				theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = theBoard[i + 2][c].isToCrush = true;
				theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
				playerScore = playerScore + (40 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findFish_ClockFour(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 2) && (c < elderColumn - 1))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 2][c + 1].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true) && (theBoard[i + 2][c + 1].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true) && (theBoard[i + 2][c + 1].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true) && (theBoard[i + 2][c + 1].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0) && (theBoard[i + 2][c + 1].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0) && (theBoard[i + 2][c + 1].kind != 0)))
			{
				theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = theBoard[i + 2][c + 1].isToCrush = true;
				theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
				playerScore = playerScore + (40 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findFish_ClockThree(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 1) && (c < elderColumn - 2))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			isFalling(i + 1, fallingVector, theBoard);
			if (!fallingVector[c + 2])
			{
				if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 2].kind)) &&
					((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true) && (theBoard[i + 1][c + 2].isNew != true)) &&
					((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true) && (theBoard[i + 1][c + 2].isToCrush != true)) &&
					((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true) && (theBoard[i + 1][c + 2].isExploding != true)) &&
					//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0) && (theBoard[i + 1][c + 2].itemID != 0)) &&
					((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0) && (theBoard[i + 1][c + 2].kind != 0)))
				{
					theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = theBoard[i + 1][c + 2].isToCrush = true;
					theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
					playerScore = playerScore + (40 * multiplier);
					multiplier = multiplier + 1;
					printScore(multiplier, playerScore);
					Sleep(dwellTime);
				}
			}
		}
	}
}
void findFish_ClockTwo(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 1) && (c < elderColumn - 2))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0)))
			{
				theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = true;
				theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
				playerScore = playerScore + (40 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findFish_ClockOne(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if (((0 < i) &&(i < elderRow - 1)) && (c < elderColumn - 1))
	{
		isFalling(i - 1, fallingVector, theBoard);
		if (!fallingVector[c + 1])
		{
			isFalling(i, fallingVector, theBoard);
			if (!fallingVector[c])
			{
				if (((theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c + 1].kind) && (theBoard[i][c].kind == theBoard[i - 1][c + 1].kind)) &&
					((theBoard[i][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 1][c + 1].isNew != true) && (theBoard[i - 1][c + 1].isNew != true)) &&
					((theBoard[i][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 1][c + 1].isToCrush != true) && (theBoard[i - 1][c + 1].isToCrush != true)) &&
					((theBoard[i][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 1][c + 1].isExploding != true) && (theBoard[i - 1][c + 1].isExploding != true)) &&
					//((theBoard[i][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 1][c + 1].itemID != 0) && (theBoard[i - 1][c + 1].itemID != 0)) &&
					((theBoard[i][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 1][c + 1].kind != 0) && (theBoard[i - 1][c + 1].kind != 0)))
				{
					theBoard[i][c + 1].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 1][c + 1].isToCrush = theBoard[i - 1][c + 1].isToCrush = true;
					theBoard[i][c].itemID = 17; theBoard[i][c].isNew = true;
					playerScore = playerScore + (40 * multiplier);
					multiplier = multiplier + 1;
					printScore(multiplier, playerScore);
					Sleep(dwellTime);
				}
			}
		}
	}
}
void findStrippedVertical(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((0 < i) && (i < elderRow - 2))
	{
		if (!fallingVector[c])
		{
			if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0)))

			{
				theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = true;
				theBoard[i][c].itemID = 12; theBoard[i][c].isNew = true;
				playerScore = playerScore + (50 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findStrippedHorizontal(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((0 < c) && (c < elderRow - 2))
	{
		if ((!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0)))

			{
				theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = true;
				theBoard[i][c].itemID = 11; theBoard[i][c].isNew = true;
				playerScore = playerScore + (50 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findWrappedCandy_LFive_URight(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((1 < i) && (c < elderColumn - 2))
	{
		isFalling(i + 2, fallingVector, theBoard);
		if (!fallingVector[c])
		{
			isFalling(i, fallingVector, theBoard);
			if ((!fallingVector[c + 1]) && (!fallingVector[c + 2]))
			{
				if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind)) &&
					((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true)) &&
					((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true)) &&
					((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true)) &&
					//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i - 2][c].itemID != 0)&& (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0)) &&
					((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0)))
				{
					theBoard[i - 1][c].isToCrush = theBoard[i - 2][c].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = true;
					theBoard[i][c].itemID = 13; theBoard[i][c].isNew = true;
					playerScore = playerScore + (50 * multiplier);
					multiplier = multiplier + 1;
					printScore(multiplier, playerScore);
					Sleep(dwellTime);
				}
			}
		}
	}
}
void findWrappedCandy_LFive_ULeft(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((1 < i) && (1 < c))
	{
		isFalling(i + 2, fallingVector, theBoard);
		if (!fallingVector[c])
		{
			isFalling(i, fallingVector, theBoard);
			if ((!fallingVector[c - 1]) && (!fallingVector[c - 2]))
			{
				if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c - 2].kind)) &&
					((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c - 2].isNew != true)) &&
					((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true)) &&
					((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c - 2].isExploding != true)) &&
					//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i - 2][c].itemID != 0)&& (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c - 2].itemID != 0)) &&
					((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c - 2].kind != 0)))
				{
					theBoard[i - 1][c].isToCrush = theBoard[i - 2][c].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c - 2].isToCrush = true;
					theBoard[i][c].itemID = 13; theBoard[i][c].isNew = true;
					playerScore = playerScore + (50 * multiplier);
					multiplier = multiplier + 1;
					printScore(multiplier, playerScore);
					Sleep(dwellTime);
				}
			}
		}
	}
}
void findWrappedCandy_LFive_DLeft(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 2) && (1 < c))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c]) && (!fallingVector[c - 1]) && (!fallingVector[c - 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c - 2].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c - 2].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c - 2].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0)&& (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c - 2].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c - 2].kind != 0)))
			{
				theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c - 2].isToCrush = true;
				theBoard[i][c].itemID = 13; theBoard[i][c].isNew = true;
				playerScore = playerScore + (50 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findWrappedCandy_LFive_DRight(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 2) && (c < elderColumn - 2))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0)&& (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0)))
			{
				theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = true;
				theBoard[i][c].itemID = 13; theBoard[i][c].isNew = true;
				playerScore = playerScore + (50 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findWrappedCandy_TFive_U(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((1 < i) && ((0 < c) && (c < elderColumn - 1)))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c + 1].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c + 1].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i - 2][c].itemID != 0)&& (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c + 1].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c + 1].kind != 0)))
			{
				theBoard[i - 1][c].isToCrush = theBoard[i - 2][c].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = true;
				theBoard[i][c].itemID = 13; theBoard[i][c].isNew = true;
				playerScore = playerScore + (50 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findWrappedCandy_TFive_D(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if ((i < elderRow - 2) && ((0 < c) && (c < elderColumn - 1)))
	{
		isFalling(i, fallingVector, theBoard);
		if ((!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c + 1].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c + 1].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c + 1].itemID != 0)) &&
				((theBoard[i][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c + 1].kind != 0)))
			{
				theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = true;
				theBoard[i][c].itemID = 13; theBoard[i][c].isNew = true;
				playerScore = playerScore + (50 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findWrappedCandy_TFive_R(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if (((0 < i) && (i < elderRow - 1)) && (c < elderColumn - 2))
	{
		isFalling(i + 1, fallingVector, theBoard);
		if (!fallingVector[c])
		{
			isFalling(i, fallingVector, theBoard);
			if ((!fallingVector[c + 1]) && (!fallingVector[c + 2]))
			{
				if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind)) &&
					((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true)) &&
					((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true)) &&
					((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true)) &&
					//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0)) &&
					((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0)))
				{
					theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = true;
					theBoard[i][c].itemID = 13; theBoard[i][c].isNew = true;
					playerScore = playerScore + (50 * multiplier);
					multiplier = multiplier + 1;
					printScore(multiplier, playerScore);
					Sleep(dwellTime);
				}
			}
		}
	}
}
void findWrappedCandy_TFive_L(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	if (((0 < i) && (i < elderRow - 1)) && (1 < c))
	{
		isFalling(i + 1, fallingVector, theBoard);
		if (!fallingVector[c])
		{
			isFalling(i, fallingVector, theBoard);
			if ((!fallingVector[c - 1]) && (!fallingVector[c - 2]))
			{
				if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c - 2].kind)) &&
					((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c - 2].isNew != true)) &&
					((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true)) &&
					((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c - 2].isExploding != true)) &&
					//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c - 2].itemID != 0)) &&
					((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c - 2].kind != 0)))
				{
					theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c - 2].isToCrush = true;
					theBoard[i][c].itemID = 13; theBoard[i][c].isNew = true;
					playerScore = playerScore + (50 * multiplier);
					multiplier = multiplier + 1;
					printScore(multiplier, playerScore);
					Sleep(dwellTime);
				}
			}
		}
	}
}
void findBomOBomVertical(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if (!fallingVector[c])
	{
		if ((1 < i) && (i < elderRow - 2))
		{
			if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i - 2][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0)))
			{
				theBoard[i - 2][c].isToCrush = theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = true;
				theBoard[i][c].kind = 0; theBoard[i][c].itemID = 15; theBoard[i][c].isNew = true;
				playerScore = playerScore + (100 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findBomOBomHorizontal(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((1 < c) && (c < elderRow - 2))
	{
		if ((!fallingVector[c - 2]) && (!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c - 2].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c - 2].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c - 2].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c - 2].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c - 2].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0)))
			{
				theBoard[i][c - 2].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = true;
				theBoard[i][c].kind = 0; theBoard[i][c].itemID = 15; theBoard[i][c].isNew = true;
				playerScore = playerScore + (100 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findColorantCandyHorizontal_Seven_sideU(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((1 < i) && ((1 < c) && (c < elderRow - 2)))
	{
		if ((!fallingVector[c - 2]) && (!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c - 2].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind) && (theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c - 2].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c - 2].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c - 2].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0) && (theBoard[i - 1][c].itemID != 0)&& (theBoard[i - 2][c].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i][c - 2].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0)))
			{
				theBoard[i][c - 2].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = theBoard[i - 1][c].isToCrush = theBoard[i - 2][c].isToCrush = true;
				theBoard[i][c].itemID = 16; theBoard[i][c].isNew = true;
				playerScore = playerScore + (200 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findColorantCandyHorizontal_Six_sideU(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((0 < i) && ((1 < c) && (c < elderRow - 2)))
	{
		if ((!fallingVector[c - 2]) && (!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c - 2].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind) && (theBoard[i][c].kind == theBoard[i - 1][c].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c - 2].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true) && (theBoard[i - 1][c].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c - 2].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true) && (theBoard[i - 1][c].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c - 2].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0) && (theBoard[i - 1][c].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i][c - 2].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0) && (theBoard[i - 1][c].kind != 0)))
			{
				theBoard[i][c - 2].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = theBoard[i - 1][c].isToCrush = true;
				theBoard[i][c].itemID = 16; theBoard[i][c].isNew = true;
				playerScore = playerScore + (200 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findColorantCandyHorizontal_Seven_sideD(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((i < elderRow - 2) && ((1 < c) && (c < elderRow - 2)))
	{
		if ((!fallingVector[c - 2]) && (!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c - 2].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c - 2].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c - 2].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c - 2].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0) && (theBoard[i + 1][c].itemID != 0)&& (theBoard[i + 2][c].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i][c - 2].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0)))
			{
				theBoard[i][c - 2].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = true;
				theBoard[i][c].itemID = 16; theBoard[i][c].isNew = true;
				playerScore = playerScore + (200 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findColorantCandyHorizontal_Six_sideD(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if ((i < elderRow - 1) && ((1 < c) && (c < elderRow - 2)))
	{
		if ((!fallingVector[c - 2]) && (!fallingVector[c - 1]) && (!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i][c - 2].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i][c - 2].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true) && (theBoard[i + 1][c].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i][c - 2].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true) && (theBoard[i + 1][c].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i][c - 2].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0) && (theBoard[i + 1][c].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i][c - 2].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0) && (theBoard[i + 1][c].kind != 0)))
			{
				theBoard[i][c - 2].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = theBoard[i + 1][c].isToCrush = true;
				theBoard[i][c].itemID = 16; theBoard[i][c].isNew = true;
				playerScore = playerScore + (200 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findColorantCandyVertical_Seven_sideR(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if (((1 < i) && (i < elderRow - 2)) && (c < elderColumn - 2))
	{
		if ((!fallingVector[c]) && (!fallingVector[c + 1]) && (!fallingVector[c + 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind) && (theBoard[i][c].kind == theBoard[i][c + 2].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true) && (theBoard[i][c + 1].isNew != true) && (theBoard[i][c + 2].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true) && (theBoard[i][c + 2].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true) && (theBoard[i][c + 2].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i - 2][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0) && (theBoard[i][c + 2].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0) && (theBoard[i][c + 1].kind != 0) && (theBoard[i][c + 2].kind != 0)))
			{
				theBoard[i - 2][c].isToCrush = theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = theBoard[i][c + 1].isToCrush = theBoard[i][c + 2].isToCrush = true;
				theBoard[i][c].itemID = 16; theBoard[i][c].isNew = true;
				playerScore = playerScore + (210 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findColorantCandyVertical_Six_sideR(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);
	
	if (((1 < i) && (i < elderRow - 2)) && (c < elderColumn - 1))
	{
		if ((!fallingVector[c]) && (!fallingVector[c + 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c + 1].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true) && (theBoard[i][c + 1].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true) && (theBoard[i][c + 1].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true) && (theBoard[i][c + 1].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i - 2][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0) && (theBoard[i][c + 1].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0) && (theBoard[i][c + 1].kind != 0)))
			{
				theBoard[i - 2][c].isToCrush = theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = theBoard[i][c + 1].isToCrush = true;
				theBoard[i][c].itemID = 16; theBoard[i][c].isNew = true;
				playerScore = playerScore + (200 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findColorantCandyVertical_Seven_sideL(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if (((1 < i) && (i < elderRow - 2)) && (1 < c))
	{
		if ((!fallingVector[c]) && (!fallingVector[c - 1]) && (!fallingVector[c - 2]))
		{
			if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind) && (theBoard[i][c].kind == theBoard[i][c - 2].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true) && (theBoard[i][c - 1].isNew != true) && (theBoard[i][c - 2].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true) && (theBoard[i][c - 2].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true) && (theBoard[i][c - 2].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i - 2][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0) && (theBoard[i][c - 1].itemID != 0) && (theBoard[i][c - 2].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0) && (theBoard[i][c - 1].kind != 0) && (theBoard[i][c - 2].kind != 0)))
			{
				theBoard[i - 2][c].isToCrush = theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = theBoard[i][c - 1].isToCrush = theBoard[i][c - 2].isToCrush = true;
				theBoard[i][c].itemID = 16; theBoard[i][c].isNew = true;
				playerScore = playerScore + (210 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}
void findColorantCandyVertical_Six_sideL(int i, int c, int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	isFalling(i, fallingVector, theBoard);

	if (((1 < i) && (i < elderRow - 2)) && (0 < c))
	{
		if ((!fallingVector[c]) && (!fallingVector[c - 1]))
		{
			if (((theBoard[i][c].kind == theBoard[i - 1][c].kind) && (theBoard[i][c].kind == theBoard[i - 2][c].kind) && (theBoard[i][c].kind == theBoard[i + 1][c].kind) && (theBoard[i][c].kind == theBoard[i + 2][c].kind) && (theBoard[i][c].kind == theBoard[i][c - 1].kind)) &&
				((theBoard[i][c].isNew != true) && (theBoard[i - 1][c].isNew != true) && (theBoard[i - 2][c].isNew != true) && (theBoard[i + 1][c].isNew != true) && (theBoard[i + 2][c].isNew != true) && (theBoard[i][c - 1].isNew != true)) &&
				((theBoard[i][c].isToCrush != true) && (theBoard[i - 1][c].isToCrush != true) && (theBoard[i - 2][c].isToCrush != true) && (theBoard[i + 1][c].isToCrush != true) && (theBoard[i + 2][c].isToCrush != true) && (theBoard[i][c - 1].isToCrush != true)) &&
				((theBoard[i][c].isExploding != true) && (theBoard[i - 1][c].isExploding != true) && (theBoard[i - 2][c].isExploding != true) && (theBoard[i + 1][c].isExploding != true) && (theBoard[i + 2][c].isExploding != true) && (theBoard[i][c - 1].isExploding != true)) &&
				//((theBoard[i][c].itemID != 0) && (theBoard[i - 1][c].itemID != 0) && (theBoard[i - 2][c].itemID != 0) && (theBoard[i + 1][c].itemID != 0) && (theBoard[i + 2][c].itemID != 0) && (theBoard[i][c - 1].itemID != 0)) && 
				((theBoard[i][c].kind != 0) && (theBoard[i - 1][c].kind != 0) && (theBoard[i - 2][c].kind != 0) && (theBoard[i + 1][c].kind != 0) && (theBoard[i + 2][c].kind != 0) && (theBoard[i][c - 1].kind != 0)))
			{
				theBoard[i - 2][c].isToCrush = theBoard[i - 1][c].isToCrush = theBoard[i + 1][c].isToCrush = theBoard[i + 2][c].isToCrush = theBoard[i][c - 1].isToCrush = true;
				theBoard[i][c].itemID = 16; theBoard[i][c].isNew = true;
				playerScore = playerScore + (200 * multiplier);
				multiplier = multiplier + 1;
				printScore(multiplier, playerScore);
				Sleep(dwellTime);
			}
		}
	}
}

// MeanWhile functions!
void matchFinder(int& playerScore, int& multiplier, bool* fallingVector, theBoardplex** theBoard)
{
	for (int n = 31; n > 0; n = n - 1)
	{
		for (int i = 0; i < elderRow; i = i + 1)
		{
			for (int c = 0; c < elderColumn; c = c + 1)
			{
				switch (n)
				{
				case 31:
					findColorantCandyHorizontal_Seven_sideU(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 30:
					findColorantCandyHorizontal_Six_sideU(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 29:
					findColorantCandyHorizontal_Seven_sideD(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 28:
					findColorantCandyHorizontal_Six_sideD(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 27:
					findColorantCandyVertical_Seven_sideR(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 26:
					findColorantCandyVertical_Six_sideR(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 25:
					findColorantCandyVertical_Seven_sideL(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 24:
					findColorantCandyVertical_Six_sideL(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 23:
					findBomOBomHorizontal(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 22:
					findBomOBomVertical(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 21:
					findWrappedCandy_LFive_URight(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 20:
					findWrappedCandy_LFive_ULeft(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 19:
					findWrappedCandy_LFive_DRight(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 18:
					findWrappedCandy_LFive_DLeft(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 17:
					findWrappedCandy_TFive_U(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 16:
					findWrappedCandy_TFive_D(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 15:
					findWrappedCandy_TFive_R(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 14:
					findWrappedCandy_TFive_L(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 13:
					findStrippedHorizontal(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 12:
					findStrippedVertical(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 11:
					findFish_ClockOne(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 10:
					findFish_ClockTwo(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 9:
					findFish_ClockThree(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 8:
					findFish_ClockFour(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 7:
					findFish_ClockFive(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 6:
					findFish_ClockSix(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 5:
					findFish_ClockSeven(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 4:
					findFish_ClockEight(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 3:
					findFishMatch(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 2:
					findHorizontalMatch(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;

				case 1:
					findVerticalMatch(i, c, playerScore, multiplier, fallingVector, theBoard);
					break;
				}
			}
		}
	}
}
void printScore(int multiplier, int playerScore)
{
	int* theHelpy;
	theHelpy = new int[6];
	for (int n = 0; n < 6; n = n + 1)
	{
		theHelpy[n] = 0;
	}

	int auxX, auxX_two, clone_playerScore;
	auxX_two = 0;
	clone_playerScore = playerScore;

	Console::SetCursorPosition((elderColumn * 2) + 1, 0);
	Console::ForegroundColor = ConsoleColor::White;
	cout << "Score: ";
	Console::SetCursorPosition((elderColumn * 2) + 8, 0);
	cout << "                                    ";
	Console::SetCursorPosition((elderColumn * 2) + 8, 0);
	Console::ForegroundColor = ConsoleColor::Cyan;

	while (playerScore > 0)
	{
		auxX = playerScore % 1000;
		theHelpy[auxX_two] = auxX;
		playerScore = playerScore / 1000;
		auxX_two = auxX_two + 1;
	}
	for (int n = 3; n >= 0; n = n - 1)
	{
		if (theHelpy[n] == 0)
		{
			if ((clone_playerScore == 0) && (n == 0))
			{
				cout << theHelpy[n];
			}
			else
			{
				if ((theHelpy[n + 1] > 0) || (theHelpy[n + 2] > 0))
				{
					cout << "000" << ((n == 0) ? "" : "'");
				}
			}
		}
		else
		{
			if ((theHelpy[n] < 10) && (theHelpy[n] > 0))
			{
				cout << ((theHelpy[n + 1] != 0) ? "00" : "") << theHelpy[n] << ((n == 0) ? "" : "'");
			}
			else
			{
				if ((theHelpy[n] < 100) && (theHelpy[n] >= 10))
				{
					cout << ((theHelpy[n + 1] != 0) ? "0" : "") << theHelpy[n] << ((n == 0) ? "" : "'");
				}
				else
				{
					if (theHelpy[n] >= 100)
					{
						cout << theHelpy[n] << ((n == 0) ? "" : "'");
					}
				}
			}
		}
	}

	Console::SetCursorPosition((elderColumn * 2) + 1, 1);
	Console::ForegroundColor = ConsoleColor::White;
	cout << "Combo: ";
	Console::SetCursorPosition((elderColumn * 2) + 8, 1);
	cout << "                                    ";
	Console::SetCursorPosition((elderColumn * 2) + 8, 1);
	Console::ForegroundColor = ConsoleColor::Green;
	cout << "x" << multiplier;

	delete[] theHelpy;
}

// Developer Options!
void showDataValue(bool showOn_OFF, bool enableGetch, bool* fallingVector, theBoardplex** theBoard)
{
	char helperForGetch_Two;

	Console::SetCursorPosition(0, elderRow + 2);
	Console::ForegroundColor = ConsoleColor::White;

	if (showOn_OFF)
	{
		for (int i = 0; i < elderRow; i = i + 1)
		{
			for (int c = 0; c < elderColumn; c = c + 1)
			{
				cout << ((theBoard[i][c].kind == 0) ? "1" : "0") << " ";
			}
			cout << endl;
		}
		cout << endl;

		if (enableGetch)
		{
			helperForGetch_Two = toupper(getch());
		}
	}
	else
	{
		Console::SetCursorPosition(0, elderRow + 1);
		Console::ForegroundColor = ConsoleColor::DarkGray;
		cout << "'0' for not falling, '1' for falling!\n";
		Console::ForegroundColor = ConsoleColor::White;
		Console::SetCursorPosition(0, elderRow + 2);
		for (int n = 0; n < elderColumn; n = n + 1)
		{
			cout << fallingVector[n] << " ";
		}
		cout << endl;

		if (enableGetch)
		{
			helperForGetch_Two = toupper(getch());
		}
	}
}
// Experimental Functions!
void myTimer(bool enableTimer)
{
	if (enableTimer)
	{
		int min_, sec_;

		Console::SetCursorPosition((elderColumn * 2) + 1, 3);
		Console::ForegroundColor = ConsoleColor::Magenta;

		cout << "-> T I M E R <-";
		Console::ForegroundColor = ConsoleColor::White;
		for (int i = amountTime; i >= 0; i = i - 1)
		{
			min_ = i / 60;
			sec_ = i % 60;
			Console::SetCursorPosition((elderColumn * 2) + 6, 4);
			cout << ((min_ < 10) ? "0" : "") << min_ << ":" << ((sec_ < 10) ? "0" : "") << sec_ << " ";

			if (i > 0)
			{
				Sleep(timerTime_LAP / speedTime_LAP);
			}

		}
	}
}

void printSpecialGlyph(wchar_t glyph)
{
	wchar_t cellText[2] = { glyph, L' ' };
	DWORD charsWritten;

	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), cellText, 2, &charsWritten, NULL);
}

// G.P.U. (Graphic Processing Unit)
void GraphicProcessingUnit(theBoardplex** theBoard)
{
	Console::SetCursorPosition(0, 0);

	for (int i = 0; i < elderRow; i = i + 1)
	{
		for (int c = 0; c < elderColumn; c = c + 1)
		{
			// Picking color!
			switch (theBoard[i][c].kind)
			{
			case 0:
				Console::ForegroundColor = ConsoleColor::White;
				break;

			case 1:
				Console::ForegroundColor = ConsoleColor::Red;
				break; 
			
			case 2:
				Console::ForegroundColor = ConsoleColor::DarkYellow;
				break;
			
			case 3:
				Console::ForegroundColor = ConsoleColor::Yellow;
				break;
			
			case 4:
				Console::ForegroundColor = ConsoleColor::Green;
				break;

			case 5:
				Console::ForegroundColor = ConsoleColor::Cyan;
				break;

			case 6:
				Console::ForegroundColor = ConsoleColor::DarkCyan;
				break;

			case 7:
				Console::ForegroundColor = ConsoleColor::DarkBlue;
				break;

			case 8:
				Console::ForegroundColor = ConsoleColor::Magenta;
				break;

			case 9:
				Console::ForegroundColor = ConsoleColor::DarkGray;
				break;

			case 10:
				Console::ForegroundColor = ConsoleColor::DarkRed;
				break;
			}
			// Selecting candy!
			switch (theBoard[i][c].itemID)
			{
			case 0:
				cout << "  ";
				break;

			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
				cout << theBoard[i][c].itemID << " ";
				break;

			case 10:
				cout << "$ ";
				break;

			case 11:
				printSpecialGlyph(L'\u2194'); // left-right arrow (old 29)
				break;

			case 12:
				printSpecialGlyph(L'\u2195'); // up-down arrow (old 18)
				break;

			case 13:
				printSpecialGlyph(L'\u2588'); // full block (old 219)
				break;

			case 14:
				printSpecialGlyph(L'\u25A0'); // black square (old 254)
				break;

			case 15:
				printSpecialGlyph(L'\u263C'); // sun (old 15)
				break;

			case 16:
				printSpecialGlyph(L'\u263B'); // black smiley (old 2)
				break;

			case 17:
				printSpecialGlyph(L'\u2302'); // house (old 127)
				break;
			}
		}
		cout << "\n";
	}
}

// Main Function.
int main()
{
	SetConsoleTitleA("WKLV LV PDVVLYH - - - InDev v.0.0.13a");
	Console::CursorVisible = false;

	theBoardplex** theBoard;
	theBoard = new theBoardplex * [elderRow];
	for (int n = 0; n < elderRow; n = n + 1)
	{
		theBoard[n] = new theBoardplex[elderColumn];
	}

	bool* fallingVector;
	fallingVector = new bool[elderColumn];
	for (int n = 0; n < elderColumn; n = n + 1)
	{
		fallingVector[n] = false;
	}

	/* / / / / / / / / / / / / / / / / / / / / / / */
	char helperForGetch;
	bool ON_OFF = false;
	bool enableGetchOpt = false;
	bool enableTimer = false;
	/* / / / / / / / / / / / / / / / / / / / / / / */

	int playerScore = 0; int multiplier = 0;
	bool isCascade;

	createBoard(theBoard);
	GraphicProcessingUnit(theBoard);
	isFalling(0, fallingVector, theBoard);
	showDataValue(ON_OFF, enableGetchOpt, fallingVector, theBoard);
	printScore(multiplier, playerScore);
	helperForGetch = toupper(getch());
	myTimer(enableTimer);
	
	while (1)
	{
		isCascade = false;
		
		myTimer(enableTimer);
		matchFinder(playerScore, multiplier, fallingVector, theBoard);
		isToCrush_Process(theBoard);
		GraphicProcessingUnit(theBoard);
		isFalling(0, fallingVector, theBoard);
		showDataValue(ON_OFF, enableGetchOpt, fallingVector, theBoard);
		printScore(multiplier, playerScore);
		Sleep(genTIMER);
		Console::SetCursorPosition(0, 0);

		reset_boolean_VALUES(theBoard);
		continueFallingCascade(isCascade, theBoard);

		isCascade = false;

		spawnNewCandy(theBoard); // Procss
		GraphicProcessingUnit(theBoard);
		isFalling(0, fallingVector, theBoard);
		showDataValue(ON_OFF, enableGetchOpt, fallingVector, theBoard);
		Sleep(genTIMER);
		Console::SetCursorPosition(0, 0);

		swapToVoid(theBoard); // Procss
		GraphicProcessingUnit(theBoard);
		isFalling(0, fallingVector, theBoard);
		showDataValue(ON_OFF, enableGetchOpt, fallingVector, theBoard);
		Sleep(genTIMER);
		Console::SetCursorPosition(0, 0);

		if (explodeCandy_14(fallingVector, theBoard))
		{
			for (int i = 0; i < elderRow; i = i + 1)
			{
				for (int c = 0; c < elderColumn; c = c + 1)
				{
					if (theBoard[i][c].itemID == 14)
					{
						Sleep(xplodngTme);
						theBoard[i][c].kind = theBoard[i][c].itemID = 0;
						theBoard[i][c].isExploding = false;

						Xploding_BooM(i, c, theBoard);
					}
				}
			}
		}

		reset_boolean_VALUES(theBoard);
		continueFallingCascade(isCascade, theBoard);

		continueFallingCascade(isCascade, theBoard);
	}

	helperForGetch = toupper(getch());
	return 0;
}

/* 
	You can do it!! You... you genius, hehe! Love you <3!
*/