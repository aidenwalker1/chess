#include "Queen.h"
#include "Chessboard.h"

//prints out Q for queen
void Queen::Print() {
	std::cout << "Q";
}

//this function finds the valid placements for this piece
//precon: takes the chessboard
//postcon: each value in valid placement array set to 0 if spot invalid, 1 if spot valid
int** Queen::FindValidPlacement(Chessboard& chessboard) {
	Space**& board = chessboard.GetBoard();

	ResetValidLocations(); //sets all values in valid locations array to 0

	//if in bounds, checks +x
	int i = x + 1;
	if (x + 1 < 8) {
		//runs until out of bounds or hit a piece
		for (i; i < 8 && !board[i][y].GetOccupied(); i++) {
			PlaceIfValid(chessboard, i, y);
		}

		//checks if piece hit
		PlaceIfValid(chessboard, i, y);
	}

	//if in bounds, checks -x
	if (x - 1 >= 0) {
		//runs until out of bounds or hit a piece
		for (i = x - 1; i >= 0 && !board[i][y].GetOccupied(); i--) {
			PlaceIfValid(chessboard, i, y);
		}

		//checks if piece hit
		PlaceIfValid(chessboard, i, y);
	}

	//if in bounds, checks +y
	if (y + 1 < 8) {
		//runs until out of bounds or hit a piece
		for (i = y + 1; i < 8 && !board[x][i].GetOccupied(); i++) {
			PlaceIfValid(chessboard, x, i);
		}

		//checks if piece hit
		PlaceIfValid(chessboard, x, i);
	}

	//if in bounds, checks -y
	if (y - 1 >= 0) {
		//runs until out of bounds or hit a piece
		for (i = y - 1; i >= 0 && !board[x][i].GetOccupied(); i--) {
			PlaceIfValid(chessboard, x, i);
		}

		//checks if piece hit
		PlaceIfValid(chessboard, x, i);
	}

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