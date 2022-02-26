#pragma once
#include "Chessboard.h"
//test class
class Test {
	Chessboard* board;
	sf::Texture piece_tex;
	int** p1_locations;
	int** p2_locations;
public:
	Test();
	void TestMove();
	void TestCheck();
	void TestCheckmate();
	void TestInvalidMove();
	void TestSelectPiece();
};