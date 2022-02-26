#include "King.h"
#include "Chessboard.h"

//prints out L for king
void King::Print() {
	std::cout << "L";
}

//this function finds the valid placements for this piece
//precon: takes the chessboard
//postcon: each value in valid placement array set to 0 if spot invalid, 1 if spot valid
int** King::FindValidPlacement(Chessboard& chessboard) {

	ResetValidLocations(); //resets valid locations array

	int y_index; //y index to check

	//if in bounds, checks right 1 and the 3 spaces by the king
	if (x + 1 < 8) {
		y_index = y + 1;

		//runs until out of bounds or hits a piece
		for (int i = 0; i < 3; i++) {
			PlaceIfValid(chessboard, x + 1, y_index);

			y_index--;
		}
	}

	//if in bounds, checks left 1 and the 3 spaces by the king
	if (x - 1 >= 0) {
		y_index = y + 1;
		//runs until out of bounds or hits a piece
		for (int i = 0; i < 3; i++) {
			PlaceIfValid(chessboard, x - 1, y_index);

			y_index--;
		}
	}

	//checks above and below king to place
	PlaceIfValid(chessboard, x, y + 1);
	PlaceIfValid(chessboard, x, y - 1);

	return valid_locations;
}

//this function updates the kings valid locations based on the enemy's valid locations
//precon: takes an array of enemy placements
//postcon: valid king spots are updated
void King::UpdateLocations(int**& enemy_placements) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			valid_locations[i][j] -= enemy_placements[i][j]; //subtracts the enemy placement to make it that the king cant be placed there
			if (valid_locations[i][j] == -1) {
				valid_locations[i][j] = 0;
			}
		}
	}
}