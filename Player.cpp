#include "Player.h"

//constructor
Player::Player(std::string color) {
	this->color = color;
	possible_player_locations = (int**)malloc(sizeof(int) * 8);
	for (int i = 0; i < 8; i++) {
		possible_player_locations[i] = (int*)malloc(sizeof(int) * 8);
		for (int j = 0; j < 8; j++) {
			possible_player_locations[i][j] = 0;
		}
	}
	time = 0;
	is_in_check = false;
}

//this function resets the player
//precon: none
//postcon: player fields reset to default
void Player::ResetPlayer() {
	time = 0;
	is_in_check = false;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			possible_player_locations[i][j] = 0;
		}
	}
}