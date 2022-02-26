#pragma once
#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//this class handles each turn of the game
class TurnHandler {
	sf::SoundBuffer buffer; //chess sound
	sf::Sound sound;

	sf::Texture chessboard_texture; //sprites
	sf::Sprite board_sprite;

	double time_elapsed;//time elapsed for bullet chess

	//start position
	int start_x;
	int start_y;

	//move position
	int move_x;
	int move_y;


	int invalid_spot[2]; //coords of invalid space selected

	int scale; //scale of screen

	int** valid_locations; //valid locations to move

	//both players
	Player* cur_player;
	Player* other_player;

	
	bool valid_selection;
	bool just_started;

	//draw invalid/valid squares
	bool draw_invalid;
	bool draw_valid;

	bool is_moving_piece;

	//chessboard
	Chessboard* chessboard;

	std::string mode; //current game mode

	//rectangles of red/green to show invalid/valid spots
	std::vector<std::vector<sf::RectangleShape>> valid_location_shapes; 
	sf::RectangleShape rect;

	//user moves/selects piece
	void SelectPiece();
	int MovePiece();

	//pointer to sprite being moved by mouse
	sf::Sprite* moved_piece;

public:
	TurnHandler(int height, Player* p1, Player* p2, Chessboard* board);

	int UpdateTime();

	//setters and getters
	std::string GetMode();
	void SetMode(std::string mode);
	void SetMoveX(int x);
	void SetMoveY(int y);
	void SetStartX(int x);
	void SetStartY(int y);
	void SetIsMoving(bool is_moving);
	bool GetIsMoving() { return is_moving_piece; };
	int GetStartX();
	void SetPlayers(Player* p1, Player* p2);
	Chessboard*& GetChessboard();
	void SetChessboard(Chessboard* chessboard);

	void UpdatePiecePosition(sf::Vector2f mouse_pos); //updates the moving piece

	void DrawWindow(sf::RenderWindow& window); //draws chessboard

	int RunTurn(); //runs the whole turn

	bool CheckPieceSelection(int x, int y); //checks if piece can be moved

	void ResetHandler(Player*& p1, Player*& p2); //resets fields
};