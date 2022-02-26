#pragma once
#include "ChessPiece.h"

//pawn chesspiece
class Pawn : public ChessPiece {
public:
	Pawn(int x, int y, std::string color) : ChessPiece(x, y, color) {} //constructor
	void Print(); //prints out piece
	int** FindValidPlacement(Chessboard& chessboard); //finds valid placement on board
};