#include "Test.h"

//constructor
Test::Test() {
	piece_tex.loadFromFile("chesspieces.png");
	board = new Chessboard(piece_tex); //creates chessboard

	//valid locations for each player, allocates space
	p1_locations = (int**)malloc(sizeof(int) * 8);
	p2_locations = (int**)malloc(sizeof(int) * 8);

	for (int i = 0; i < 8; i++) {
		p1_locations[i] = (int*)malloc(sizeof(int) * 8);
		p2_locations[i] = (int*)malloc(sizeof(int) * 8);
	}

	//gets initial possible moves
	board->FindInitialMoves("white", p1_locations);
	board->FindInitialMoves("black", p2_locations);
}

//this function tests the move function
void Test::TestMove() {
	//top right pawn (black)
	int start_x = 0;
	int start_y = 1;

	//moves 2 in front
	int move_x = 0;
	int move_y = 3;

	int** valid_spots = board->GetBoard()[start_x][start_y].GetPiece().FindValidPlacement(*board); //gets possible spots
	
	//checks if move spot is valid
	if (valid_spots[move_x][move_y]) {
		board->MovePiece(start_x, start_y, move_x, move_y); //moves piece

		//checks if pawn moved there
		if (dynamic_cast<Pawn*>(&board->GetBoard()[move_x][move_y].GetPiece())) {
			std::cout << "test success\n";
		}
		else {
			std::cout << "Test failed : moving piece\n";
		}
	}
	else {
		std::cout << "Test failed : finding placement\n";
	}
}

//this function tests the check function
void Test::TestCheck() {
	//gets both kings
	King* k1 = dynamic_cast<King*>(&board->GetBoard()[3][7].GetPiece());
	King* k2 = dynamic_cast<King*>(&board->GetBoard()[3][0].GetPiece());

	board->MovePiece(2, 6, 2, 4); //moves pawn in front of bishop

	//updates possible location
	board->GetPossibleMoves("white", p1_locations, *k2);
	k2->UpdateLocations(p1_locations);
	board->GetPossibleMoves("black", p2_locations, *k1);
	k1->UpdateLocations(p2_locations);

	board->MovePiece(3, 6, 3, 5); //moves pawn in front of king

	//updates possible location
	board->GetPossibleMoves("black", p2_locations, *k1);
	k1->UpdateLocations(p2_locations);
	board->GetPossibleMoves("white", p1_locations, *k2);
	k2->UpdateLocations(p1_locations);

	board->MovePiece(4, 0, 0, 4); //moves queen to put king in check

	//updates possible location
	board->GetPossibleMoves("white", p1_locations, *k2);
	k1->UpdateLocations(p2_locations);
	board->GetPossibleMoves("black", p2_locations, *k1);
	k2->UpdateLocations(p1_locations);

	board->PrintBoard();

	//makes sure its not in mate
	if (!board->CheckForMate(p2_locations)) {
		std::cout << "test failed : in checkmate\n";
	}
	else if(p2_locations[3][7]) { //checks if the enemy can move onto the king
		std::cout << "test success: king in check\n";
	}
	else {
		std::cout << "test failed : not in check\n";
	}
}

//this function tests if the king is in checkmate
void Test::TestCheckmate() {
	//gets both kings
	King* k1 = dynamic_cast<King*>(&board->GetBoard()[3][7].GetPiece());
	King* k2 = dynamic_cast<King*>(&board->GetBoard()[3][0].GetPiece());

	board->MovePiece(1,6,1,4); //moves pawn in front of knight

	//updates possible location
	board->GetPossibleMoves("white", p1_locations, *k2);
	k2->UpdateLocations(p1_locations);
	board->GetPossibleMoves("black", p2_locations, *k1);
	k1->UpdateLocations(p2_locations);

	board->MovePiece(2,6,2,5); //moves pawn in front of bishop

	//updates possible location
	board->GetPossibleMoves("black", p2_locations, *k1);
	k1->UpdateLocations(p2_locations);
	board->GetPossibleMoves("white", p1_locations, *k2);
	k2->UpdateLocations(p1_locations);

	board->MovePiece(4, 0, 0, 4); //moves queen to put king in checkmate

	//updates possible location
	board->GetPossibleMoves("white", p1_locations, *k2);
	k1->UpdateLocations(p2_locations);
	board->GetPossibleMoves("black", p2_locations, *k1);
	k2->UpdateLocations(p1_locations);

	board->PrintBoard();

	//tests if there is nowhere the player can go, they are in checkmate if they cant move anywhere
	if (!board->CheckForMate(p1_locations)) {
		std::cout << "test success\n";
	}
	else {
		std::cout << "test failed: king not in mate\n";
	}

}

//this function tests if a user can not move to an invalid spot
void Test::TestInvalidMove() {
	//black top right knight
	int start_x = 1;
	int start_y = 0;

	//invalid spot to move knight
	int move_x = 1;
	int move_y = 2;

	int** valid_spots = board->GetBoard()[start_x][start_y].GetPiece().FindValidPlacement(*board); //gets valid moves for knight

	//checks if knight cant move to the created invalid spot
	if (!valid_spots[move_x][move_y]) {
		std::cout << "test success\n";
	}
	else {
		std::cout << "Test failed : moving piece\n";
	}
}

//this function checks if the user can select a piece
void Test::TestSelectPiece() {
	//1 left of black top right pawn
	int x = 1;
	int y = 1;

	//tests if white can choose black pieces
	if (!board->CheckValidSelection(x, y, "white")) {
		std::cout << "test success\n";
	}
	else {
		std::cout << "test failed: white can select black\n";
	}

	//tests if black can choose black pieces
	if (board->CheckValidSelection(x, y, "black")) {
		std::cout << "test success\n";
	}
	else {
		std::cout << "test failed: black cant select black\n";
	}
}