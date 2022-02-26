#include "Bishop.h"
#include "Chessboard.h"

//prints out B for bishop
void Bishop::Print() {
	std::cout << "B";
}

//this function finds the valid placements for this piece
//precon: takes the chessboard
//postcon: each value in valid placement array set to 0 if spot invalid, 1 if spot valid
int** Bishop::FindValidPlacement(Chessboard& chessboard) {
	Space** board = chessboard.GetBoard();

	ResetValidLocations(); //resets valid location array

	//indexes to check
	int x_index;
	int y_index;

	//if in bounds, checks +x +y diagonal
	if (x + 1 < 8 && y + 1 < 8) {
		x_index = x + 1;
		y_index = y + 1;

		//runs until out of bounds or hits a piece
		while (x_index < 8 && y_index < 8 && !board[x_index][y_index].GetOccupied()) {
			PlaceIfValid(chessboard, x_index, y_index);
			x_index++;
			y_index++;
		}

		//checks if piece hit
		PlaceIfValid(chessboard, x_index, y_index);
		
	}

	//if in bounds, checks -x +y diagonal
	if (x - 1 >= 0 && y + 1 < 8) {
		x_index = x - 1;
		y_index = y + 1;

		//runs until out of bounds or hits a piece
		while (x_index >= 0 && y_index < 8 && !board[x_index][y_index].GetOccupied()) {
			PlaceIfValid(chessboard, x_index, y_index);
			x_index--;
			y_index++;
		}

		//checks if piece hit
		PlaceIfValid(chessboard, x_index, y_index);
	}

	//if in bounds, checks +x -y diagonal
	if (x + 1 < 8 && y - 1 >= 0) {
		x_index = x + 1;
		y_index = y - 1;

		//runs until out of bounds or hits a piece
		while (x_index < 8 && y_index >= 0 && !board[x_index][y_index].GetOccupied()) {
			PlaceIfValid(chessboard, x_index, y_index);
			x_index++;
			y_index--;
		}

		//checks if piece hit
		PlaceIfValid(chessboard, x_index, y_index);
	}

	//if in bounds, checks -x -y diagonal
	if (x - 1 >= 0 && y - 1 >= 0) {
		x_index = x - 1;
		y_index = y - 1;

		//runs until out of bounds or hits a piece
		while (x_index >= 0 && y_index >= 0 && !board[x_index][y_index].GetOccupied()) {
			PlaceIfValid(chessboard, x_index, y_index);
			x_index--;
			y_index--;
		}

		//checks if piece hit
		PlaceIfValid(chessboard, x_index, y_index);
	}

	return valid_locations;
}
