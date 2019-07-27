/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
// Angela Hollings 785095434
This is the file that you will be submitting for marking
Complete the definitions of the functions in this file
DO NOT REMOVE ANY FUNCTION DEFINITIONS - they all must be present when you submit this file
*/



int SecondPlacePrize(int prize1, int prize2, int prize3)
{
	if ((prize2 <= prize1 && prize1 <= prize3) || (prize3 <= prize1 && prize1 <= prize2))
	{
		return prize1;
	}
	else if ((prize1 <= prize2 && prize2 <= prize3) || (prize3 <= prize2 && prize2 <= prize1))
	{
		return prize2;
	}
	else
	{
		return prize3;
	}
	
}

int FourInARow(int values[], int length)
{
	int count = 1;
	for (int i = 0; i < length-1; i++)
	{
		if (values[i] == values[i + 1])
		{
			// Increase count until 4 in a row, or the same value isn't the following value
			count++;
			if (count == 4) 
			{
				return (i - 2);
			}
				
		}
		else
		{
			count = 1;
		}
	}
	//Return -1 if there isn't 4 in a row
	return -1;
}

int BinaryToDecimal(int binary)
{
	int n = 1;
	int sum = 0;
	while (binary != 0)
	{
		// Convert the decimal value to binary 
		sum = sum + (binary % 10) * n;
		// Find next binary digit
		binary = binary / 10;
		n = n * 2;
	}
	return sum;
}

void SortArray(double *abilities, int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (abilities[j] > abilities[i])
			{
				double temp = abilities[i];
				abilities[i] = abilities[j];
				abilities[j] = temp;
			}
		}
	}
}

double MedianAbility(double abilities[], int length)
{
	double median;
	SortArray(abilities,length);
	// Return Median depending on whether odd or even
	if (length % 2 == 0)
	{
		median = (abilities[length / 2] + abilities[length / 2 - 1]) / 2;
	}
	else
	{
		median = abilities[length/2];
	}
	return median;
	
}

void RemoveSpaces(char *name)
{
	int length = strlen(name);
	int i;
	for (i = length-1; i >= 0; i--)
	{
		// shift the following values in the array back if there are 2 spaces in a row
		if (name[i] == ' ' && name[i-1] == ' ')
		{
			for (int j = i; j < (length -1); j++)
			{
				name[j] = name[j + 1];
			}
			// Shorten the character array
			name[length - 1] = '\0';
			length--;
		}
	}
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	int i,j;
	for (i = 0; i < MAX_SIZE; i++)
	{
		for (j = 0; j < MAX_SIZE; j++)
		{
			if (i < size && j < size)
			{
				if (size % 2 == 0)
				{
					// Places the boundary tokens for an even board
					if ((i == size / 2 || i == (size / 2 - 1)) && (j == size / 2 || j == (size / 2 - 1)))
					{
						board[i][j] = 3;
					}
					else
					{
						board[i][j] = 0;
					}
				}
				else
				{
					// Places the boundary tokens for an odd board. 
					if (i == size / 2 && j == size / 2)
					{
						board[i][j] = 3;
					}
					else
					{
						board[i][j] = 0;
					}
				}
			}
			else
			{
				board[i][j] = -1;
			}
		}
	}
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	if (side =='N')
	{
		if (board[0][move] == 0)
		{
			board[0][move] = player;
			// Changes each element in the specified column to the player until a boundary is met
			for (int j = 0; j < size-1; j++)
			{
				if (board[j + 1][move] == 0)
				{
					board[j + 1][move] = player;
					board[j][move] = 0;
				}
				else
				{
					
					*lastRow = j;
					*lastCol = move;
					return;
				}
			}
			*lastRow = size-1;
			*lastCol = move;
			return;
		}
	}
	else if (side =='S')
	{
		if (board[size-1][move] == 0)
		{
			board[size - 1][move] = player;
			for (int j = size - 1; j >= 1; j--)
			{
				if (board[j - 1][move] == 0)
				{
					board[j - 1][move] = player;
					board[j][move] = 0;
				}
				else
				{
					*lastRow= j;
					*lastCol = move;
					return;
				}
			}
			*lastRow = 0;
			*lastCol = move;
			return;
		}
	}
	else if (side =='E')
	{
		// Checks if the first move can be placed on the board (only if it's 0 (valid move))
		if (board[move][size - 1] == 0)
		{
			// iterates from the right to the left (last column to 0th)
			board[move][size - 1] = player;
			for (int j = size - 1; j >= 1; j--)
			{
				// Checks if the next position is 0
				if (board[move][j - 1] == 0)
				{
					// Moves the player to the next position 
					board[move][j - 1] = player;
					// Changes previous position to 0
					board[move][j] = 0;
				}
				else
				{
					//stores this row and column as the last one
					*lastRow = move;
					*lastCol = j;
					return;
				}
			}
			// Stores the last row if no boundary/tokens in that column
			*lastRow = move;
			*lastCol = 0;
			return;
		}
	}
	else if (side =='W')
	{
		if (board[move][0] == 0)
		{
			board[move][0] = player;
			for (int j = 0; j < size-1; j++)
			{
				if (board[move][j + 1] == 0)
				{
					board[move][j + 1] = player;
					board[move][j] = 0;
				}
				else
				{

					*lastRow = move;
					*lastCol = j;
					return;
				}
			}
			*lastRow = move;
			*lastCol = size-1;
			return;
		}
	}
	*lastRow = -1;
	*lastCol = -1;
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	
		
	int i, j;
	int count = 0;
	int vertical = 0;
	int horz = 0;
	if (row == -1 || col == -1)
	{
		return 0;
	}
	// Loop over every element in the board
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			// Check if there are 4 in a row horizontally, vertically, and diagonally. 
			
			if (board[i][j] == player)
			{
				horz++;
				if (horz == 4)
				{
					return player;
				}
			}
			else
			{
				horz = 0;
			}
			if (board[j][i] == player)
			{
				vertical++;
				if (vertical == 4)
				{
					return player;
				}
			}
			else
			{
				vertical = 0;
			}

			if ((size-3>i) && (j < size-3) && (board[i][j] == player) && (board[i + 1][j + 1] == player) && (board[i + 2][j + 2] == player) && (board[i + 3][j + 3] == player))
			{
				return player;
			}

			if (((size-3 > i) && (j>2))&&(board[i][j] == player) && (board[i + 1][j - 1] == player) && (board[i + 2][j - 2] == player) && (board[i + 3][j - 3] == player))
			{
				return player;
			}
		}
		//Check for valid moves
		if (board[0][i] == 0 || board[size - 1][i] == 0 || board[i][size - 1] == 0 || board[i][0] == 0)
		{
			count = 1;
		}
		// Reset for new row/column
		vertical = 0;
		horz = 0;
	}

	if (count == 0)
	{
		return player;
	}
	else
	{
		return 0;
	}
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	int x = 48;
	int length = size * size + (size)* 8 + size + 20;
	for (int j = size + 4; j < length; j = j + size + 5)
	{
		boardString[j] = '\n';
		// Printing the East and west 
		if ((j > size + size + 10) && (j<(length-size-size-10)))
		{
			boardString[j - 1] = 'E';
			boardString[j - 2] = (char)x;
			boardString[j - size-4] = 'W';
			boardString[j - size - 3] = (char)x;
			x++;

		}
		// Printing the hyphens
		else
		{
			boardString[j - 1] = '-';
			boardString[j - 2] = '-';
			boardString[j - size - 4] = '-';
			boardString[j - size - 3] = '-';
		}
	}
	x = 48;
	// Printing the North and South 
	for (int i = 2; i < size + 2; i++)
	{
		boardString[i] = 'N';
		boardString[i+size+5] = (char)x;
		boardString[length-size-5+i] = 'S';
		boardString[length - 2*size - 10 + i] = (char)x;
		x++;
	}
	int y = 0;
	int z = 0;
	int i = 0;
	int j = 0;
	for (i = 2*size + 12; i < length - size - size - 12; i = i + size + 5)
	{
		// Printing the Board
		for (j = i; j < i + size; j++)
		{
			if (board[y][z] == 0)
			{
				boardString[j] = '.';
			}
			else if (board[y][z] == 1)
			{
				boardString[j] = 'X';
			}
			else if (board[y][z] == 2)
			{
				boardString[j] = 'O';
			}
			else if (board[y][z]== 3)
			{
				boardString[j] = '#';
			}
			z++;
		}
		y++;
		z = 0;
	}
	boardString[length] = '\0';
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int otherplayer = 0;
	if (player == 2)
	{
		otherplayer = 1;
	}
	else
	{
		otherplayer = 2;
	}
	// Create a new board
	int NewBoard[MAX_SIZE][MAX_SIZE] = { 0 };
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			NewBoard[i][j] = board[i][j];
		}
	}
	int Row = 1;
	int Col = 1;
	
	for (int mymove = 0; mymove < size; mymove++)
	{
		//Add move to copy of the board
		AddMoveToBoard(NewBoard, size, 'N', mymove, player, &Row, &Col);
		//Check if this move results in a win
		if (Row != -1 && (CheckGameOver(NewBoard, size, player, 1, 1) == player))
		{
			// Return side and move if the givne move would result in a win
			*side = 'N';
			*move = mymove;
			return;
		}
		else if ((Row != -1) && (Col != -1))
		{
			NewBoard[Row][Col] = 0;
			Row = 1;
			Col = 1;
		}
		else
		{
			Row = 1;
			Col = 1;
		}
		AddMoveToBoard(NewBoard, size, 'E', mymove, player, &Row, &Col);
		if (Row != -1 && (CheckGameOver(NewBoard, size, player, 1, 1) == player))
		{
			*side = 'E';
			*move = mymove;
			return;
		}
		else if ((Row != -1) && (Col != -1))
		{
			NewBoard[Row][Col] = 0;
			Row = 1;
			Col = 1;
		}
		else
		{
			Row = 1;
			Col = 1;
		}
		AddMoveToBoard(NewBoard, size, 'S', mymove, player, &Row, &Col);
		if (Row != -1 && (CheckGameOver(NewBoard, size, player, 1, 1) == player))
		{
			*side = 'S';
			*move = mymove;
			return;
		}
		else if ((Row != -1) && (Col != -1))
		{
			NewBoard[Row][Col] = 0;
			Row = 1;
			Col = 1;
		}
		else
		{
			Row = 1;
			Col = 1;
		}
		AddMoveToBoard(NewBoard, size, 'W', mymove, player, &Row, &Col);
		if (Row != -1 && (CheckGameOver(NewBoard, size, player, 1, 1) == player))
		{
			*side = 'W';
			*move = mymove;
			return;
		}
		else if ((Row != -1) && (Col != -1))
		{
			NewBoard[Row][Col] = 0;
			Row = 1;
			Col = 1;
		}
		else
		{
			Row = 1;
			Col = 1;
		}
	}
	for (int y = 0; y < size; y++)
	{
		// Add move to board to block the opposing player if there are 3 in a row
		AddMoveToBoard(NewBoard, size, 'N', y, otherplayer, &Row, &Col);
		if (Row != -1 && (CheckGameOver(NewBoard, size, otherplayer, 1, 1) == otherplayer))
		{
			*side = 'N';
			*move = y;
			return;
		}
		else if ((Row != -1) && (Col != -1))
		{
			NewBoard[Row][Col] = 0;
			Row = 1;
			Col = 1;
		}
		else
		{
			Row = 1;
			Col = 1;
		}
		AddMoveToBoard(NewBoard, size, 'E', y, otherplayer, &Row, &Col);
		if (Row != -1 && (CheckGameOver(NewBoard, size, otherplayer, 1, 1) == otherplayer))
		{
			*side = 'E';
			*move = y;
			return;
		}
		else if ((Row != -1) && (Col != -1))
		{
			NewBoard[Row][Col] = 0;
			Row = 1;
			Col = 1;
		}
		else
		{
			Row = 1;
			Col = 1;
		}
		AddMoveToBoard(NewBoard, size, 'S', y, otherplayer, &Row, &Col);
		if (Row != -1 && (CheckGameOver(NewBoard, size, otherplayer, 1, 1) == otherplayer))
		{
			*side = 'S';
			*move = y;
			return;
		}
		else if ((Row != -1) && (Col != -1))
		{
			NewBoard[Row][Col] = 0;
			Row = 1;
			Col = 1;
		}
		else
		{
			Row = 1;
			Col = 1;
		}
		AddMoveToBoard(NewBoard, size, 'W', y, otherplayer, &Row, &Col);
		if (Row != -1 && (CheckGameOver(NewBoard, size, otherplayer, 1, 1) == otherplayer))
		{
			*side = 'W';
			*move = y;
			return;
		}
		else if ((Row != -1) && (Col != -1))
		{
			NewBoard[Row][Col] = 0;
			Row = 1;
			Col = 1;
		}
		else
		{
			Row = 1;
			Col = 1;
		}
	}
	
	// Find the amount of each player in each row and column
	int sums[4][MAX_SIZE] = { 0 }; 
	for (int p = 0; p < size; p++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[j][p] == otherplayer)
			{
				// gives the sum of that players presence in the row/column 
				sums[0][p] = sums[0][p] + 1; 
			}
			else if (board[p][j] == otherplayer)
			{
				sums[1][p] = sums[1][p] + 1;
			}
			if (board[j][p] == player)
			{
				sums[2][p] = sums[2][p] + 1;
			}
			else if (board[p][j] == player)
			{
				sums[3][p] = sums[3][p] + 1;
			}
		}
	}
	int sidee[4] = { 0 };
	int maxim[4] = { 0 };
	// Finds the row/column with the max number of tokens of player for each side 
	for (int k = 0; k < 4; k++)
	{
		for (int n = 0; n < size; n++)// store the side
		{
			if (sums[k][n] > maxim[k])
			{
				sidee[k] = n;
				maxim[k] = sums[k][n];
			}
		}
	}
	int maxy = maxim[0];
	int mob = 0;

	for (int j = 1; j < 4; j++)
	{
		// find the maximum amount of one player in the 4, preffering the opposing player
		if (maxim[j] > maxy)
		{
			maxy = maxim[j];
			mob = j;
		}
	}
	int play = 0;
	int other = 0;
	if (mob == 2 || mob == 3)
	{
		other = player;
		play = otherplayer;
	}
	else
	{
		play = otherplayer;
		other = player;
	}
	// If the move is valid, it's the max side specified, and the maximum row/column specified, place the token there. 
	for (int i = 0; i < size-1; i++)
	{
		if (mob == 1 || mob == 3)
		{
			if (((board[sidee[mob]][i] == play) && (board[sidee[mob] + 1][i] == 0)) && (board[sidee[mob]][size - 1] == 0)) // place the token un a zero next to the player. Need to change this so it's the player specified
			{
				*side = 'E';
				*move = sidee[mob];
				return;
			}
			else if ((board[sidee[mob]][size-1-i] == play) && (board[sidee[mob]][size-i-1-1] == 0) && (board[sidee[mob]][0] == 0))
			{
				*side = 'W';
				*move = sidee[mob];
				return;
			}
			else if ((board[sidee[mob]][i] == other) && (board[sidee[mob] + 1][i] == 0) && (board[sidee[mob]][size - 1] == 0))
			{
				*side = 'E';
				*move = sidee[mob];
				return;
			}
			else if ((board[sidee[mob]][size - 1 - i] == other) && (board[sidee[mob]][size - i - 1 - 1] == 0) && (board[sidee[mob]][0] == 0))
			{
				*side = 'W';
				*move = sidee[mob];
				return;
			}
		}
		else if (mob == 0 || mob == 2)
		{
			if ((board[i+1][sidee[mob]] == play) && (board[i][sidee[mob]] == 0) && (board[0][sidee[mob]] == 0)) // place the token un a zero next to the player. Need to change this so it's the player specified
			{
				*side = 'N';
				*move = sidee[mob];
				return;
			}
			else if ((board[size-1 - i-1][sidee[mob]] == play) && (board[size-1 - i][sidee[mob]] == 0) && (board[size - 1][sidee[mob]] == 0))
			{
				*side = 'S';
				*move = sidee[mob];
				return;
			}
			else if ((board[i+1][sidee[mob]] == other) && (board[i][sidee[mob] + 1] == 0) && (board[0][sidee[mob]] == 0)) // place the token un a zero next to the player. Need to change this so it's the player specified
			{
				*side = 'N';
				*move = sidee[mob];
				return;
			}
			else if ((board[size - i][sidee[mob]] == other) && (board[size - i][sidee[mob] - 1] == 0) && (board[size - 1][sidee[mob]] == 0))
			{
				*side = 'S';
				*move = sidee[mob];
				return;
			}
		}
	}
	// If the move was invalid, place the token in the first valid spot.
	for (int d = 0; d < size; d++)
	{
		if (board[0][d] == 0)
		{
			*side = 'N';
			*move = d;
			return;
		}
		else if (board[size - 1][d] == 0)
		{
			*side = 'S';
			*move = d;
			return;
		}
		else if (board[d][0] == 0)
		{
			*side = 'W';
			*move = d;
			return;
		}
		else if (board[d][size - 1] == 0)
		{
			*side = 'E';
			*move = d;
			return;
		}
	}
}
void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	// Loop over every element in the board
	GetMoveBot1(board, size, player, side, move);
}
