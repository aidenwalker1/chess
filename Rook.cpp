#include "Rook.h"
#include "Chessboard.h"

//prints out R for rook
void Rook::Print() {
	std::cout << "R";
}

//this function finds the valid placements for this piece
//precon: takes the chessboard
//postcon: each value in valid placement array set to 0 if spot invalid, 1 if spot valid
int** Rook::FindValidPlacement(Chessboard& chessboard) {
	Space** board = chessboard.GetBoard();

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

	return valid_locations;
}