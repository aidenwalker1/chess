#pragma once
#include "ChessPiece.h"

//queen chesspiece
class Queen : public ChessPiece {
public:
	Queen(int x, int y, std::string color) : ChessPiece(x, y, color) {} //constructor
	void Print(); //prints out piece
	int** FindValidPlacement(Chessboard& chessboard); //finds valid placement on board
};