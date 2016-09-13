//
// Board - The properties and state of a game board
//

#pragma once
#include "Square.h"
#include "Dice.h"

class Board {

public:
	// Default Constructor
	Board() {

		// Defining which ones are the kings
		humans[4].SetKing(true);
		bots[4].SetKing(true);

		// Arranging the orientation of the dices in the board
		for (int index = 0; index < 9; index++) {
			//Supplying the top values since the rear value is 3 by default
			if (!humans[index].IsKing()) {
				humans[index].SetBeginningOrientation(startingTopValuesOfDices[index]);
				bots[index].SetBeginningOrientation(startingTopValuesOfDices[index]);
			}
			//cout << humans[index].GetTop() << humans[index].GetLeft() << humans[index].GetBottom() << humans[index].GetRight() << endl;
		}

		// General board setup with Squares and Dices
		for (int currentRow = 0; currentRow < 8; currentRow++) {
			for (int currentCol = 0; currentCol < 9; currentCol++) {
				gameBoard[currentRow][currentCol].SetCoordinates(currentRow, currentCol);
				
				//cout << "(" << gameBoard[currentRow][currentCol].GetRow() << ", " << gameBoard[currentRow][currentCol].GetColumn() << ")\t";

				//Humans Home Row
				if (currentRow == 0) {
					gameBoard[currentRow][currentCol].SetOccupied(humans[currentCol]);
					humans[currentCol].SetCoordinates(currentRow, currentCol);
					humans[currentCol].SetBotControl(false);
				}

				//Bots Home Row
				if (currentRow == 7) {
					gameBoard[currentRow][currentCol].SetOccupied(bots[currentCol]);
					bots[currentCol].SetCoordinates(currentRow, currentCol);
					bots[currentCol].SetBotControl(true);
				}
			}
			//cout << endl;
		}
	}

	void DrawBoard() {
		//Drawing the board inverted cause zero row is supposed to be at the bottom
		for (int row = 7; row >= 0; row--) {
			cout << abs(row + 1) << "\t";
			for (int col = 0; col < 9; col++) {
				if (gameBoard[row][col].IsOccupied()) {
					//ATTENTION: Need to work on this after establishing a link between a square and a dice.
					//Try creating a dice within the square class and see if that link assists it in some way.
					//Also add isHuman/isComputer functions to find out if a dice is operated by a human or a comp
					
					if (gameBoard[row][col].GetResident()->IsBotOperated()) {
						cout << "C";
					}
					else {
						cout << "H";
					}
					cout << gameBoard[row][col].GetResident()->GetTop() << gameBoard[row][col].GetResident()->GetRight() << "\t";
				}
				else {
					cout << "-\t";
				}
			}
			cout << endl;
		}
		cout << "\t1\t2\t3\t4\t5\t6\t7\t8\t9" << endl << endl;
	}


	// Stores the game state in a multidimensional string array.
	void UpdateBoard() {
		for (int row = 7; row >= 0; row--) {
			for (int col = 0; col < 9; col++) {
				serializedGameBoard[row][col].assign("0");
				if (gameBoard[row][col].IsOccupied()) {
					if (gameBoard[row][col].GetResident()->IsBotOperated()) {
						serializedGameBoard[row][col].assign("C");
					}
					else {
						serializedGameBoard[row][col].assign("H");
					}
					// Append the top and right value of the occupying dice
					serializedGameBoard[row][col].append(to_string(gameBoard[row][col].GetResident()->GetTop()));
					serializedGameBoard[row][col].append(to_string(gameBoard[row][col].GetResident()->GetRight()));
				}
				//cout << serializedGameBoard[row][col] << "\t";
			}
			//cout << endl;
		}
	}

	//ATTENTION: These should be private/protected but accessible from elsewhere at the same time
	Square gameBoard[8][9];
	Dice humans[9];
	Dice bots[9];
private:
	friend class Moves;
	int startingTopValuesOfDices[9] = { 5, 1, 2, 6, 1, 6, 2, 1, 5 };
	string serializedGameBoard[8][9];
};