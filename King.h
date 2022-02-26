#pragma once
#include "ChessPiece.h"

//king chesspiece
class King : public ChessPiece {
public:
	King(int x, int y, std::string color) : ChessPiece(x, y, color) {} //constructor
	void Print(); //prints out piece
	int** FindValidPlacement(Chessboard& chessboard); //finds valid placement on board

	void UpdateLocations(int**& enemy_placements); //updates where the king can go based on where the enemy can go
};