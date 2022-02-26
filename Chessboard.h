#pragma once
#include "Space.h"
#include "Pieces.h"
#include <time.h>

//[0][0] = top left

//chessboard class
class Chessboard {
	Space** board; //array of spaces to make board

public:
	Chessboard(sf::Texture& piece_tex); //constructor

	Space**& GetBoard(); //getter

	bool CheckValidSelection(int x, int y, std::string color); //checks if piece was valid to select by user

	void RandomizeBoard(int scale); //randomizes pieces

	bool IsOutOfBounds(int x, int y); //checks if coords are out of bounds

	bool CheckEmptyTakeablePlacement(int x, int y, std::string color); //checks if can take piece or if space is empty

	bool CanTakePiece(int x, int y, std::string color); //checks if can take piece (mostly for pawn)

	bool CheckForCheck(std::string color); //checks if in check
	
	void GetPossibleMoves(std::string color, int**& all_locations, King& other); //gets all possible moves the player can do

	void MergeLocations(int**& all_locations, int**& valid_locations); //merges 2 arrays together

	void MovePiece(int x_org, int y_org, int x_move, int y_move); //moves piece to a space

	void PlaceIfValid(int**& valid_locations, int x, int y, std::string& color); //checks if a piece can be placed 

	void PrintBoard(); //prints out board

	bool CheckForMate(int**& valid_placements); //checks for checkmate

	void FindInitialMoves(std::string color, int**& all_locations); //finds all initial moves without looking for check
};

