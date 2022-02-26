#include "Chessboard.h"

//gets board
Space**& Chessboard::GetBoard() { return board; };

//constructor, takes a texture
Chessboard::Chessboard(sf::Texture& piece_tex) {
	int scale = sf::VideoMode::getDesktopMode().height / 8; //gets scale of screen

	//allocates space for board
	board = (Space**)malloc(sizeof(Space) * 8);

	for (int i = 0; i < 8; i++) {
		board[i] = (Space*)malloc(sizeof(Space) * 8);
		for (int j = 0; j < 8; j++) {
			board[i][j] = Space(i, j);
		}
	}

	sf::IntRect rects[12]; //rectangles of sprite locations

	//sets each sprite for the rect, in chesspieces.png it goes from left to right
	int index = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			rects[index] = sf::IntRect(j * 200, i * 200, 200, 200);
			index++;
		}
	}

	//creates pieces at each needed space, then the line after creates the sprite and sets its values (texture, sprite location, scale)

	//sets pawns
	for (int i = 0; i < 8; i++) {
		board[i][1].SetPiece(new Pawn(i, 1, "black"));
		board[i][1].GetPiece().SetSprite(piece_tex, rects[11], i * scale, 1 * scale);

		board[i][6].SetPiece(new Pawn(i, 6, "white"));
		board[i][6].GetPiece().SetSprite(piece_tex, rects[5], i * scale, 6 * scale);
	}
	

	//sets rooks
	board[0][0].SetPiece(new Rook(0, 0, "black"));
	board[0][0].GetPiece().SetSprite(piece_tex, rects[10], 0 * scale, 0 * scale);

	board[7][0].SetPiece(new Rook(7, 0, "black"));
	board[7][0].GetPiece().SetSprite(piece_tex, rects[10], 7 * scale, 0 * scale);

	board[0][7].SetPiece(new Rook(0, 7, "white"));
	board[0][7].GetPiece().SetSprite(piece_tex, rects[4], 0 * scale, 7 * scale);

	board[7][7].SetPiece(new Rook(7, 7, "white"));
	board[7][7].GetPiece().SetSprite(piece_tex, rects[4], 7 * scale, 7 * scale);

	//sets knights
	board[6][0].SetPiece(new Knight(6, 0, "black"));
	board[6][0].GetPiece().SetSprite(piece_tex, rects[9], 6 * scale, 0 * scale);

	board[1][0].SetPiece(new Knight(1, 0, "black"));
	board[1][0].GetPiece().SetSprite(piece_tex, rects[9], 1 * scale, 0 * scale);

	board[1][7].SetPiece(new Knight(1, 7, "white"));
	board[1][7].GetPiece().SetSprite(piece_tex, rects[3], 1 * scale, 7 * scale);

	board[6][7].SetPiece(new Knight(6, 7, "white"));
	board[6][7].GetPiece().SetSprite(piece_tex, rects[3], 6 * scale, 7 * scale);

	//sets bishops
	board[2][0].SetPiece(new Bishop(2, 0, "black"));
	board[2][0].GetPiece().SetSprite(piece_tex, rects[8], 2 * scale, 0 * scale);

	board[5][0].SetPiece(new Bishop(5, 0, "black"));
	board[5][0].GetPiece().SetSprite(piece_tex, rects[8], 5 * scale, 0 * scale);

	board[2][7].SetPiece(new Bishop(2, 7, "white"));
	board[2][7].GetPiece().SetSprite(piece_tex, rects[2], 2 * scale, 7 * scale);

	board[5][7].SetPiece(new Bishop(5, 7, "white"));
	board[5][7].GetPiece().SetSprite(piece_tex, rects[2], 5 * scale, 7 * scale);

	//sets queens
	board[4][0].SetPiece(new Queen(4, 0, "black"));
	board[4][0].GetPiece().SetSprite(piece_tex, rects[7], 4 * scale, 0 * scale);

	board[4][7].SetPiece(new Queen(4, 7, "white"));
	board[4][7].GetPiece().SetSprite(piece_tex, rects[1], 4 * scale, 7 * scale);

	//sets kings
	board[3][0].SetPiece(new King(3, 0, "black"));
	board[3][0].GetPiece().SetSprite(piece_tex, rects[6], 3 * scale, 0 * scale);

	board[3][7].SetPiece(new King(3, 7, "white"));
	board[3][7].GetPiece().SetSprite(piece_tex, rects[0], 3 * scale, 7 * scale);

}

//this function randomizes all pieces on the board
//precon: board is fully made, takes scale of screen
//postcon: pieces put in random spots
void Chessboard::RandomizeBoard(int scale) {
	srand((unsigned int)time(NULL)); //seeds random

	for (int i = 0; i < 3; i++) { //randomizes board 3 times
		for (int j = 0; j < 8; j++) {
			for (int k = 0; k < 8; k++) {
				if (board[j][k].GetOccupied()) {
					//gets random index
					int rand_x = rand() % 8; 
					int rand_y = rand() % 8;

					//checks if space is empty
					if (!board[rand_x][rand_y].GetOccupied()) {
						MovePiece(j, k, rand_x, rand_y); //moves piece

						board[rand_x][rand_y].GetPiece().GetSprite().setPosition(sf::Vector2f(rand_x * scale, rand_y * scale)); //updates sprite location
					}
				}
			}
		}
	}
}

//this function checks if the selected place is valid
//precon: takes the location and color of the user
//postcon: returns true if user can select this piece to move
bool Chessboard::CheckValidSelection(int x, int y, std::string color) {
	return board[x][y].GetOccupied() && board[x][y].GetPiece().GetColor() == color;
}

//this function checks if coordinates are out of bounds
//precon: takes x and y positions
//postcon: returns true if x/y are in the board
bool Chessboard::IsOutOfBounds(int x, int y) {
	return !((x > -1 && x < 8) && (y > -1 && y < 8));
}

//this function prints the board to the console
//precon: none
//postcon: board is printed to screen
void Chessboard::PrintBoard() {
	std::cout << "-----------------\n";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << "|";

			//prints space for empty space
			if (!board[i][j].GetOccupied()) {
				std::cout << " ";
			}
			else {
				//prints out piece
				board[i][j].GetPiece().Print();
			}
		}
		std::cout << "|";
		std::cout << "\n-----------------\n";
	}

}

//this function checks if a space at x,y is empty or a takeable piece
//precon: takes x/y and color of user
//postcon: returns true if user could move here
bool Chessboard::CheckEmptyTakeablePlacement(int x, int y, std::string color) {
	if (!IsOutOfBounds(x, y) && !board[x][y].GetOccupied()) {
		return true;
	}
	return CanTakePiece(x, y, color);

}

//this function checks if a piece can take another piece at a certain index
//precon: takes x/y and the color of the user
//postcon: returns true if the user can take the piece
bool Chessboard::CanTakePiece(int x, int y, std::string color) {
	return !IsOutOfBounds(x, y) && board[x][y].GetOccupied() && board[x][y].GetPiece().GetColor() != color;
}

//this function updates the valid locations
//precon: takes the valid locations array, the location to place at, and the user color
//postcon: array at index x,y is 1 if can place piece there
void Chessboard::PlaceIfValid(int**& valid_locations, int x, int y, std::string& color) {
	if (CheckEmptyTakeablePlacement(x, y, color)) {
		valid_locations[x][y] = 1;
	}
}

//this function moves a piece to a given x,y
//precon: takes the original spot, and the spot to move to
//postcon: piece is moved to new spot
void Chessboard::MovePiece(int x_org, int y_org, int x_move, int y_move) {
	board[x_move][y_move].SetPiece(nullptr); //sets new spot to nullptr

	board[x_org][y_org].GetPiece().Move(x_move, y_move); //moves piece to new spot

	board[x_move][y_move].SetPiece(&board[x_org][y_org].GetPiece()); //updates board

	board[x_org][y_org].SetPiece(nullptr); //sets old spot to nullptr
}

//this function checks for check
//precon: takes the enemy color
//postcon: returns true if in check
bool Chessboard::CheckForCheck(std::string color) {
	int** all_locations = (int**)malloc(sizeof(int) * 8); //all locations of enemy
	int** prev_locations = (int**)malloc(sizeof(int) * 8); //prev locations of a piece

	//allocations space
	for (int i = 0; i < 8; i++) {
		all_locations[i] = (int*)malloc(sizeof(int) * 8);
		prev_locations[i] = (int*)malloc(sizeof(int) * 8);
		for (int j = 0; j < 8; j++) {
			all_locations[i][j] = 0;
		}
	}

	//index of user king
	int king_x = 0;
	int king_y = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].GetOccupied()) { //if piece here
				if (board[i][j].GetPiece().GetColor() == color) { //if piece matches enemy color
					//sets prev array to values of the current piece
					for (int k = 0; k < 8; k++) {
						prev_locations[k] = (int*)malloc(sizeof(int) * 8);
						for (int l = 0; l < 8; l++) {
							prev_locations[k][l] = board[i][j].GetPiece().GetValidLocations()[k][l];
						}
					}

					//updates the piece placement without checking for check, in order to see if the newly placed piece will put the king in check
					board[i][j].GetPiece().UpdateInitial();
					int** valid_locations = board[i][j].GetPiece().FindValidPlacement(*this);

					MergeLocations(all_locations, valid_locations); //merges the new valid spots with the all locations array

					//resets the the pieces values to the previous values
					board[i][j].GetPiece().UpdateInitial();
					board[i][j].GetPiece().SetValidLocations(prev_locations);
				}
				else if (dynamic_cast<King*>(&board[i][j].GetPiece())) { //if user's king found
					king_x = i;
					king_y = j;
				}
			}
		}
	}

	return all_locations[king_x][king_y]; //returns if enemy could move onto king's space
}

//this function gets all the possible moves for a user
//precon: takes the user color, its valid locations, and the enemy king
//postcon: all possible moves are put into all locations array
void Chessboard::GetPossibleMoves(std::string color, int**& all_locations, King& other) {
	//resets locations array
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			all_locations[i][j] = 0;
		}
	}

	board[other.GetX()][other.GetY()].SetOccupied(false); //sets the enemy king occupied to false

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].GetOccupied()) { //if space has piece
				if (board[i][j].GetPiece().GetColor() == color) { //if piece matches user color
					//gets valid locations for piece
					int** valid_locations = board[i][j].GetPiece().FindValidPlacement(*this);
					//merges valid locations with the all locations array
					MergeLocations(all_locations, valid_locations);
				}
			}
		}
	}

	board[other.GetX()][other.GetY()].SetOccupied(true); //resets kings occupancy
}

//this function finds the initial moves of each piece for a user
//precon: takes the user color and its array of valid locations
//postcon: initial valid locations are loaded into array
void Chessboard::FindInitialMoves(std::string color, int**& all_locations) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].GetOccupied()) { //if space has piece
				if (board[i][j].GetPiece().GetColor() == color) { //if piece matches user color

					int** valid_locations = board[i][j].GetPiece().FindValidPlacement(*this); //finds valid locations of piece
					MergeLocations(all_locations, valid_locations); //merges piece valid locations with all valid locations

					board[i][j].GetPiece().UpdateInitial(); //updates initial to check for checkmate
				}
			}
		}
	}
}

//this function merges 2 arrays by adding the values together
//precon: takes 2 arrays to merge
//postcon: values of valid array are added to all array
void Chessboard::MergeLocations(int**& all_locations, int**& valid_locations) {
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			all_locations[i][j] += valid_locations[i][j]; //adds arrays together

			if (all_locations[i][j] > 1) { //makes sure values are 0 or 1
				all_locations[i][j] = 1;
			}
		}
	}
}

//this function checks for checkmate
//precon: takes the valid locations of all pieces
//postcon: returns false if user in checkmate
bool Chessboard::CheckForMate(int**& valid_placements) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (valid_placements[i][j]) {
				return true;
			}
		}
	}
	return false;
}