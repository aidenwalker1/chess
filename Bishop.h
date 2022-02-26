#pragma once

#include "ChessPiece.h"

//bishop chesspiece
class Bishop : public ChessPiece {
public:
	Bishop(int x, int y, std::string color) : ChessPiece(x, y, color) {} //constructor

	int** FindValidPlacement(Chessboard& chessboard); //finds valid locations to be placed
	void Print(); //prints out piece
};