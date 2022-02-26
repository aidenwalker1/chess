#pragma once
#include "ChessPiece.h"

//rook chesspiece
class Rook : public ChessPiece {

public:
	Rook(int x, int y, std::string color) : ChessPiece(x, y, color) {} //constructor
	void Print(); //prints out piece

	int** FindValidPlacement(Chessboard& chessboard); //finds valid placement on board
};
