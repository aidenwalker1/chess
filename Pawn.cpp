#include "Pawn.h"
#include "Chessboard.h"

//this function finds the valid placements for this piece
//precon: takes the chessboard
//postcon: each value in valid placement array set to 0 if spot invalid, 1 if spot valid
int** Pawn::FindValidPlacement(Chessboard& chessboard) {
	Space** board = chessboard.GetBoard();

	ResetValidLocations(); //resets valid location array
	
	int increment_y = color == "black" ? 1 : -1; //either increments up or down the board depending on the color

	//checks if the pawn can take a piece on the right diagonal
	if (chessboard.CanTakePiece(x + 1, y + increment_y, color)) {
		PlaceIfValid(chessboard, x + 1, y + increment_y);
	}

	//checks if the pawn can take a piece on the left diagonal
	if (chessboard.CanTakePiece(x - 1, y + increment_y, color)) {
		PlaceIfValid(chessboard, x - 1, y + increment_y);
	}

	//checks if pawn has empty space in front
	if (!chessboard.IsOutOfBounds(x, y + increment_y) && !board[x][y + increment_y].GetOccupied()) {
		PlaceIfValid(chessboard, x, y + increment_y);
	}
	else {
		return valid_locations;
	}

	//checks if pawn can move 2 spaces up
	if ((y == 1 && color == "black") || (y == 6 && color == "white")) {
		if (!board[x][y + (increment_y * 2)].GetOccupied()) {
			PlaceIfValid(chessboard, x, y + (increment_y * 2));
		}
	}

	return valid_locations;
}

//prints out P for pawn
void Pawn::Print() {
	std::cout << "P";
}