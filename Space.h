#pragma once
#include "ChessPiece.h"

//this class is a space on the chessboard
class Space {
	int x; //1-8
	int y; //1-8

	bool occupied;

	ChessPiece* piece; //either points to a piece or nullptr if empty
public:
	//constructor and copy constructor
	Space(int x = 0, int y = 0);
	Space(const Space& copy);

	//setters and getters
	char GetX() const; 
	int GetY() const; 

	int GetOccupied();
	void SetOccupied(bool occupied);

	ChessPiece& GetPiece();
	void SetPiece(ChessPiece* piece);
};