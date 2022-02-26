#include "Space.h"

//setters and getters
char Space::GetX() const { return x; };
int Space::GetY() const { return y; };

int Space::GetOccupied() { return occupied; };
void Space::SetOccupied(bool occupied) { this->occupied = occupied; };

ChessPiece& Space::GetPiece() { return *piece; };

void Space::SetPiece(ChessPiece* piece) {
	this->piece = piece;
	occupied = piece == nullptr ? 0 : 1; //updates occupied if piece placed/removed
}

//constructor
Space::Space(const int x, const int y) {
	this->x = x;
	this->y = y;
	occupied = false;
	piece = nullptr;
}

//copy constructor
Space::Space(const Space& copy) {
	x = copy.x;
	y = copy.y;
	occupied = copy.occupied;
	piece = copy.piece;
}