#pragma once
#include "Chessboard.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "TurnHandler.h"

//runs whole program
class GameHandler : public TurnHandler {
//	Chessboard* chessboard; //pointer to current board

	Space** board; //directly gets spaces from board 

	//both players
	Player* player1;
	Player* player2;

	int height; //height of screen
	int scale; //height / 8

	sf::Texture piece_tex; //texture of all pieces
	sf::Sprite pieces[12]; //sprites of all pieces, if either of these go out of scope program seems to break

public:
	//constructor
	GameHandler() : TurnHandler(sf::VideoMode::getDesktopMode().height, nullptr, nullptr, nullptr) {
		player1 = new Player("white");
		player2 = new Player("black");
		//initializes board
		piece_tex.loadFromFile("chesspieces.png");
		SetChessboard(new Chessboard(piece_tex));
		board = GetChessboard()->GetBoard();

		//sets player kings
		player1->SetKing(dynamic_cast<King*>(&board[3][7].GetPiece()));
		player2->SetKing(dynamic_cast<King*>(&board[3][0].GetPiece()));

		SetPlayers(player1, player2);

		//gets height of screen and scale
		height = sf::VideoMode::getDesktopMode().height;
		scale = height / 8;
	}
	void RunProgram(); //starts game

	void InitializeText(sf::Text* options, sf::Font& font); //initializes the menu text

	//switches texts for each menu
	void UpdateGameSelectionText(sf::Text* options);
	void UpdateMenuText(sf::Text* options);
	void UpdateRulesText(sf::Text* options);

	//handles click on each menu
	void MainMenuClick(sf::Vector2f translated_pos, sf::Text* options, bool& in_rules, bool& in_select_gamemode, sf::RenderWindow& window);
	void GameSelectionClick(sf::Vector2f translated_pos, sf::Text* options, bool& in_select_gamemode, sf::RenderWindow& window);
	void RulesClick(sf::Vector2f translated_pos, sf::Text* options, bool& in_rules);

	void StartGame(std::string mode, sf::RenderWindow& window); //starts game in given mode
};