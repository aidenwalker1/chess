#include "Knight.h"
#include "Chessboard.h"

//prints out K for knight
void Knight::Print() {
	std::cout << "K";
}

//this function finds the valid placements for this piece
//precon: takes the chessboard
//postcon: each value in valid placement array set to 0 if spot invalid, 1 if spot valid
int** Knight::FindValidPlacement(Chessboard& chessboard) {
	Space** board = chessboard.GetBoard();

	ResetValidLocations(); //resets valid locations array

	//if in bounds, checks if knight can go up 2 then over 1
	if (x + 2 < 8) {
		PlaceIfValid(chessboard, x + 2, y + 1);
		PlaceIfValid(chessboard, x + 2, y - 1);
	}

	//if in bounds, checks if knight can go down 2 then over 1
	if (x - 2 >= 0) {
		PlaceIfValid(chessboard, x - 2, y + 1);
		PlaceIfValid(chessboard, x - 2, y - 1);
	}

	//if in bounds, checks if knight can go right 2 then over 1
	if (y + 2 < 8) {
		PlaceIfValid(chessboard, x + 1, y + 2);
		PlaceIfValid(chessboard, x - 1, y + 2);
	}

	//if in bounds, checks if knight can go left 2 then over 1
	if (y - 2 >= 0) {
		PlaceIfValid(chessboard, x + 1, y - 2);
		PlaceIfValid(chessboard, x - 1, y - 2);
	}

	return valid_locations;
}