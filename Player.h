#pragma once
#include <string>
#include "King.h"

//player class
class Player {
	King* king; //pointer to king of this player to always keep track of

	std::string color; //player side

	int** possible_player_locations; //all possible moves for all pieces

	bool is_in_check; //if user in check

	int time; //time elapsed for bullet
public:
	Player(std::string color); //constructor

	//setters and getters
	std::string GetColor() { return color; };

	King*& GetKing() { return king; };
	void SetKing(King* king) { this->king = king; };

	int**& GetPossibleLocations() { return possible_player_locations; };

	bool IsInCheck() { return is_in_check; };
	void SetCheckStatus(bool check) { is_in_check = check; };

	int GetTime() { return time; };
	void SetTime(int time) { this->time = time; };

	void ResetPlayer(); //resets player
};