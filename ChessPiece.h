#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Chessboard; //needed instead of include so that program wont break

//chesspiece class
class ChessPiece {
protected:
	//location of piece
	int x;
	int y;

	int** valid_locations; //0 = invalid, 1 = valid

	std::string color;

	bool initial; //used for avoiding checking for check, in order to find initial possible moves

	sf::Sprite sprite; //sprite of piece, cant inherit from sprite since setting texture would break program doing it that way
public:
	ChessPiece(int x, int y, std::string& color);

	//setters and getters
	int GetX();
	void SetX(int x);

	int GetY();
	void SetY(int y);

	int**& GetValidLocations();
	void SetValidLocations(int** valid_locations);

	sf::Sprite& GetSprite();
	void SetSprite(sf::Texture& text, sf::IntRect& rect, int x, int y);

	std::string& GetColor();

	void ResetValidLocations(); //resets valid location array

	void UpdateInitial(); 
	virtual void Print() = 0; //prints chesspiece


	virtual int** FindValidPlacement(Chessboard& chessboard) = 0; //finds each move the piece cold go

	void PlaceIfValid(Chessboard& chessboard, int x, int y); //checks if placement will be valid

	void Move(int x, int y); //moves piece

} ;