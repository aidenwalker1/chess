#pragma once
#include "ChessPiece.h"

//knight chesspiece
class Knight : public ChessPiece {
public:
	Knight(int x, int y, std::string color) : ChessPiece(x, y, color) {} //constructor
	void Print(); //prints out piece
	int** FindValidPlacement(Chessboard& chessboard); //finds valid placement on board
};