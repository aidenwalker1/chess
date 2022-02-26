#include "GameHandler.h"
#include "Test.h"
//this function runs the program
//precon: none
//postcon: game is run and quit
void GameHandler::RunProgram() {
	sf::RenderWindow window(sf::VideoMode(height, height), "Chess"); //opens up the window

	//music
	sf::Music music;
	music.setVolume(33);
	music.openFromFile("music.wav"); //opens music
	music.play(); //plays music

	//text
	sf::Text options[4];
	sf::Font font;

	font.loadFromFile("arial.ttf"); //loads text font

	//initializes text and menu
	InitializeText(options, font);
	UpdateMenuText(options);

	bool in_select_gamemode = false; //main menu = false, game menu = true
	bool in_rules = false;

	//runs until window is closed
	while (window.isOpen()) {
		sf::Event event;

		//polls the user event/input
		while (window.pollEvent(event)) {
			//if user closes window
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//if user clicks
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					//gets x and y
					float x = event.mouseButton.x;
					float y = event.mouseButton.y;

					//gets mouse pos and translates it to the screen coords
					sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
					sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos);

					//gamemode select
					if (in_select_gamemode) {
						GameSelectionClick(translated_pos, options, in_select_gamemode, window);
					}
					else if (in_rules) {
						RulesClick(translated_pos, options, in_rules);
					}
					else { //main menu select
						MainMenuClick(translated_pos, options,in_rules, in_select_gamemode, window);
					}
				}
				
			}
		}

		//draws text and renders window
		window.clear();
		for (int i = 0; i < 4; i++) {
			window.draw(options[i]);
		}

		window.display();
	}
}

//this functions handles a main menu click
//precon: takes the mouse pos, the menu text, the select gamemode bool, and the window
//postcon: user either selects game, prints rules, or quits
void GameHandler::MainMenuClick(sf::Vector2f translated_pos, sf::Text* options, bool& in_rules,bool& in_select_gamemode, sf::RenderWindow& window) {
	if (options[0].getGlobalBounds().contains(translated_pos)) { //switches to gamemode select
		UpdateGameSelectionText(options);
		in_select_gamemode = true;
	}
	else if (options[1].getGlobalBounds().contains(translated_pos)) { //prints rules
		UpdateRulesText(options);
		in_rules = true;
	}
	else if (options[2].getGlobalBounds().contains(translated_pos)) { //exits program
		window.close();
	}
}

//this function handles a main menu click
//precon: takes the mouse pos, the menu text, the select gamemode bool, and the window
//postcon: user either selects gamemode, or quits
void GameHandler::GameSelectionClick(sf::Vector2f translated_pos, sf::Text* options, bool& in_select_gamemode, sf::RenderWindow& window) {
	if (options[0].getGlobalBounds().contains(translated_pos)) { //default
		StartGame("default",window);
	}
	else if (options[1].getGlobalBounds().contains(translated_pos)) { //bullet
		StartGame("bullet",window);
	}
	else if (options[2].getGlobalBounds().contains(translated_pos)) { //random
		StartGame("random",window);
	}
	else if (options[3].getGlobalBounds().contains(translated_pos)) { //back
	}
	else { //clicked nothing
		return;
	}

	//resets menu text and exits game mode menu
	UpdateMenuText(options);
	in_select_gamemode = false;
}

//this function handles a rules click
//precon: takes the mouse pos, the menu text, the select in rules bool, and the window
//postcon: user looks at rules or backs out
void GameHandler::RulesClick(sf::Vector2f translated_pos, sf::Text* options, bool& in_rules) {
	if (options[2].getGlobalBounds().contains(translated_pos)) { //back
		//resets text
		UpdateMenuText(options);
		options[0].setCharacterSize(scale); 

		in_rules = false;
	}

}

//this function initializes the game text
//precon: takes the text array and a font
//postcon: text is set up
void GameHandler::InitializeText(sf::Text* options, sf::Font& font) {
	//sets fields of text
	options[0].setFont(font);

	options[0].setCharacterSize(scale);

	options[0].setStyle(sf::Text::Bold | sf::Text::Underlined);


	options[0].setFillColor(sf::Color::Red);

	//copies other text to be same as original
	options[1] = options[0];
	options[2] = options[0];
	options[3] = options[0];

	//sets position on screen, based on height
	options[0].setPosition(sf::Vector2f(height / 2 - scale, height / 3));
	options[1].setPosition(sf::Vector2f(height / 2 - scale, height / 2));
	options[2].setPosition(sf::Vector2f(height / 2 - scale, (2 * height) / 3));
	options[3].setPosition(sf::Vector2f(height / 2 - scale, (5 * height) / 6));
}

//this function updates the menu text
//precon: takes the array of text
//postcon: text is set to the main menu text
void GameHandler::UpdateMenuText(sf::Text* options) {
	options[0].setString("Play");
	options[1].setString("Rules");
	options[2].setString("Quit");
	options[3].setString("");
}

//this function updates the rules text
//precon: takes the text array
//postcon: text is set to rules text
void GameHandler::UpdateRulesText(sf::Text* options) {
	//rules of chess
	std::string rules = "Objective: The objective of chess is to checkmate your opponent's king\nmeaning your opponent's king is in check\nand has no legal moves to move them out of check.\n";
	rules += "Checks: A check is a move that attacks the king with a piece.\nCaptures: Pieces are captured when a piece from the opposing player lands\non the same square occupied by one of the pieces from the other player.\n";
	rules += "Board coordinates: Starting from the bottom left corner from whites perspective horizontal squares are denoted\nfrom left to right as follows a,b,c,d,e,f,g,hand starting from the bottom left the vertical scares are\ndenoted as numbers starting at 1 and going up to 8.";
	//updates size and strings to fit
	options[0].setString(rules);
	options[1].setString("");

	options[0].setCharacterSize(scale / 10);

	options[2].setString("Back");
}

//this function updates the menu text
//precon: takes the array of text
//postcon: text is set to the game selection text
void GameHandler::UpdateGameSelectionText(sf::Text* options) {
	options[0].setString("Default");
	options[1].setString("Bullet");
	options[2].setString("Random");
	options[3].setString("Back");
}

//this function starts the game
//precon: takes the gamemode and window
//postcon: game is played and completed
void GameHandler::StartGame(std::string mode, sf::RenderWindow& window) {
	SetMode(mode); 

	//randomizes board for random mode
	if (mode == "random") {
		GetChessboard()->RandomizeBoard(scale);
	}

	int win = 0;

	//finds initial moves for each player
	GetChessboard()->FindInitialMoves(player1->GetColor(), player1->GetPossibleLocations());
	GetChessboard()->FindInitialMoves(player2->GetColor(), player2->GetPossibleLocations());

	//prints chessboard to console
	GetChessboard()->PrintBoard();

	//initializes timers for bullet chess
	time_t timer;
	time(&timer);
	int time_elapsed = timer;

	//runs until window closed or someone wins
	while (window.isOpen() && !win) {
		if (mode == "bullet") {
			time(&timer); //updates time

			if (timer == time_elapsed + 1) { //if time increments by 1 second
				time_elapsed++;
				win = UpdateTime(); //updates time for players
			}
			if (win) {
				break;
			}
		}

		sf::Event event;

		//gets mouse position
		sf::Vector2i mouse_location = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_pos = window.mapPixelToCoords(mouse_location);

		//checks if mouse is in the window
		bool valid_pos = mouse_pos.x > -1 && mouse_pos.y > -1 && mouse_pos.x <= height && mouse_pos.y <= height;
		if (valid_pos) {
			UpdatePiecePosition(mouse_pos);
		}

		//window polls for user input/event
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { //closes window
				window.close();
				break;
			}
			else  if (event.type == sf::Event::MouseButtonPressed) { //if mouse clicked
				if (event.mouseButton.button == sf::Mouse::Left && valid_pos) { //if left click
					//gets mouse position, sets it to the starting x/y
					SetStartX(event.mouseButton.x / scale);
					SetStartY(event.mouseButton.y / scale);

					UpdatePiecePosition(mouse_pos); //updates the moved piece for the mouse
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) { //if mouse released
				if (GetStartX() != -1 && valid_pos) {
					//gets mouse position, sets it to the moved x/y
					SetMoveX(event.mouseButton.x / scale);
					SetMoveY(event.mouseButton.y / scale);
				}
			}
		}

		//renders window
		window.clear();
		DrawWindow(window); //draws chessboard

		window.display();

		win = RunTurn(); //runs a turn
	}
	//deletes player and chessboard memory
	delete GetChessboard();

	//creates new player/chessboard and sets their fields
	player1->ResetPlayer();
	player2->ResetPlayer();

	SetChessboard(new Chessboard(piece_tex));

	board = GetChessboard()->GetBoard();

	player1->SetKing(dynamic_cast<King*>(&board[3][7].GetPiece()));
	player2->SetKing(dynamic_cast<King*>(&board[3][0].GetPiece()));
	ResetHandler(player1, player2);
}