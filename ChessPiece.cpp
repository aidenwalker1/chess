#include "ChessPiece.h"
#include "Chessboard.h"

//constructor
ChessPiece::ChessPiece(int x, int y, std::string& color) {
	this->color = color;
	this->x = x;
	this->y = y;
	initial = true; 

	//allocates space for array
	valid_locations = (int**)malloc(sizeof(int) * 8);

	for (int i = 0; i < 8; i++) {
		valid_locations[i] = (int*)malloc(sizeof(int) * 8);
		for (int j = 0; j < 8; j++) {
			valid_locations[i][j] = 0;
		}
	}
}

//setters and getters
int ChessPiece::GetX() { 
	return x; 
}
void ChessPiece::SetX(int x) { 
	this->x = x; 
}

int ChessPiece::GetY() { 
	return y; 
}
void ChessPiece::SetY(int y) { 
	this->y = y; 
}

std::string& ChessPiece::GetColor() { 
	return color; 
}

sf::Sprite& ChessPiece::GetSprite() { 
	return sprite; 
}

void ChessPiece::SetSprite(sf::Texture& text, sf::IntRect& rect, int x, int y) {
	float scale = 0.9 * (sf::VideoMode::getDesktopMode().height / (double)1440); //scale of piece

	sprite.setScale(sf::Vector2f(scale, scale));

	//sets texture of sprite
	sprite.setTexture(text);
	sprite.setTextureRect(rect);

	sprite.setPosition(sf::Vector2f(x, y)); //sets pos of piece
}

int**& ChessPiece::GetValidLocations() { 
	return valid_locations; 
}

void ChessPiece::SetValidLocations(int** valid_locations) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->valid_locations[i][j] = valid_locations[i][j]; //sets each value of valid locations to new one
		}
	}
}

//switches the initial bool
void ChessPiece::UpdateInitial() {
	initial = !initial;
}

//moves piece to given x/y
void ChessPiece::Move(int x, int y) {
	this->SetX(x);
	this->SetY(y);
}

//this functions resets the valid locations of the array
//precon: none
//postcon: each value in array set to 0
void ChessPiece::ResetValidLocations() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			valid_locations[i][j] = 0;
		}
	}
}

//this function sets the valid locations array at x,y to 1 or 0 depending on if its valid or not
//precon: takes the chessboard and the x/y to check
//postcon: location determined if valid or not
void ChessPiece::PlaceIfValid(Chessboard& chessboard, int x, int y) {
	//if out of bounds
	if (chessboard.IsOutOfBounds(x, y)) {
		return;
	}
	//if need to avoid checking for checkmate
	if (initial) {
		chessboard.PlaceIfValid(valid_locations, x, y, color); //sets valid placements to 1 if x/y is valid

		return;
	}

	Space**& board = chessboard.GetBoard();

	//original location
	int x_org = this->x;
	int y_org = this->y;

	// gets piece at location going to move to, and then moves that piece there temporarily
	ChessPiece& temp_piece = board[x][y].GetPiece(); 

	board[x][y].SetPiece(this);

	board[x_org][y_org].SetPiece(nullptr);

	bool in_check = false;

	//checks for check
	if (color == "white") {
		in_check = chessboard.CheckForCheck("black");
	}
	else {
		in_check = chessboard.CheckForCheck("white");
	}

	//resets the piece movement
	board[x][y].SetPiece(&temp_piece);

	board[x_org][y_org].SetPiece(this);

	//if not in check, sets valid placements to 1 if x/y is valid
	if (in_check) {
		valid_locations[x][y] = 0; //invalid spot
	}
	else {
		chessboard.PlaceIfValid(valid_locations, x, y, color);
	}
}

