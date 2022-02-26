#include "TurnHandler.h"
#include "Chessboard.h"

//constructor
TurnHandler::TurnHandler(int height, Player* p1, Player* p2, Chessboard* chessboard) {
	chessboard_texture.loadFromFile("brownchessboard.png");

	//sets board sprite and scale
	board_sprite.setTexture(chessboard_texture);
	board_sprite.setScale((float)height / 1214, (float)height / 1215);

	scale = height / 8; //sets scale

	//piece move/start locations
	start_x = -1;
	start_y = -1;
	move_x = -1;
	move_y = -1;

	valid_locations = nullptr;

	invalid_spot;

	//sets the player pointers
	cur_player = p1;
	other_player = p2;

	//initializes bools
	valid_selection = false;
	just_started = false;

	draw_invalid = false;
	draw_valid = false;

	is_moving_piece = false;

	this->chessboard = chessboard;

	time_elapsed = 0;

	moved_piece = nullptr;

	int alternate = 0;

	//initializes vector of valid rectangle shapes
	for (int i = 0; i < 8; i++) {
		std::vector<sf::RectangleShape> vect;
		for (int j = 0; j < 8; j++) {
			//creates new rectangle and adds it to vector
			sf::RectangleShape new_rect((sf::Vector2f(height / 8, height / 8)));
			new_rect.setFillColor(sf::Color(0, 255, 0, 100)); //transparent green

			new_rect.setPosition(sf::Vector2f(scale * i, scale * j));
			vect.push_back(new_rect);
		}
		valid_location_shapes.push_back(vect); //adds vector to 2d vector
	}

	rect = sf::RectangleShape((sf::Vector2f(height / 8, height / 8))); //creates rectangle for invalid spot
	rect.setFillColor(sf::Color(255, 0, 0, 100)); //transparent red

	//loads sound from buffer and sets it
	buffer.loadFromFile("chess_move.wav");
	sound.setBuffer(buffer);
}

//setters and getters
std::string TurnHandler::GetMode() {
	return mode;
}
void TurnHandler::SetMode(std::string mode) {
	this->mode = mode;
}

void TurnHandler::SetMoveX(int x) {
	move_x = x;
}
void TurnHandler::SetMoveY(int y) {
	move_y = y;
}
void TurnHandler::SetStartX(int x) {
	start_x = x;
}
void TurnHandler::SetStartY(int y) {
	start_y = y;
}

int TurnHandler::GetStartX() {
	return start_x;
}

void TurnHandler::SetPlayers(Player* p1, Player* p2) {
	cur_player = p1;
	other_player = p2;
}

void TurnHandler::SetIsMoving(bool is_moving) {
	is_moving_piece = is_moving;
}

Chessboard*& TurnHandler::GetChessboard() {
	return chessboard;
}

void TurnHandler::SetChessboard(Chessboard* chessboard) {
	this->chessboard = chessboard;
}

//this function updates the time for a user
//precon: none
//postcon: increments time by 1 and then checks if out of time, returns 1 if out of time
int TurnHandler::UpdateTime() {
	cur_player->SetTime(cur_player->GetTime() + 1); //increments time

	//prints time to console
	std::cout << cur_player->GetColor() << " time: " << cur_player->GetTime() << "\n";
	std::cout << other_player->GetColor() << " time: " << other_player->GetTime() << "\n";

	//checks if player runs out of time
	if (cur_player->GetTime() > 60) {
		std::cout << other_player->GetColor() << " wins!";
		return 1;
	}
	return 0;
}

//this function draws chessboard onto the window
//precon: takes the window
//postcon: chessboard and pieces are drawn to screen
void TurnHandler::DrawWindow(sf::RenderWindow& window) {
	window.draw(board_sprite); //draws chessboard

	//draws every piece
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (chessboard->GetBoard()[i][j].GetOccupied()) {
				window.draw(chessboard->GetBoard()[i][j].GetPiece().GetSprite()); //draws piece
			}
		}
	}
	
	//if selected invalid piece
	if (draw_invalid) {

		rect.setPosition(scale * invalid_spot[0], scale * invalid_spot[1]);
		window.draw(rect); //draws red rectangle on invalid spot
	}
	//if selected valid piece
	else if (draw_valid) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (valid_locations[i][j]) {
					window.draw(valid_location_shapes[i][j]); //draws green square over valid spot
				}
			}
		}
	}
}

//this function runs a turn
//precon: none
//postcon: turn is completed, returns 1 if someone one
int TurnHandler::RunTurn() {
	bool piece_select = !just_started && start_x != -1 && move_x == -1; //if piece was selected
	bool piece_move = move_x != -1; //if piece was dropped

	if (piece_select) {
		SelectPiece(); //checks if piece is selectable
	}
	else if (piece_move) {
		return MovePiece(); //checks if piece can be placed and then places it
	}
	return 0;
}

//this function checks if the user can select the piece they clicked
//precon: piece was selected
//postcon: allows user to move the piece if valid
void TurnHandler::SelectPiece() {
	if (CheckPieceSelection(start_x, start_y)) {
		//updates bools
		just_started = true;
		draw_invalid = false;
		draw_valid = true;
		is_moving_piece = true;

		std::cout << "valid piece selection.\n";

		moved_piece = &chessboard->GetBoard()[start_x][start_y].GetPiece().GetSprite(); //updates the moved piece sprite
	}
	else {
		std::cout << "invalid piece selection.\n";

		draw_invalid = true;

		//sets the invalid square coords
		invalid_spot[0] = start_x;
		invalid_spot[1] = start_y;

		//resets start/move coords
		move_x = -1;
		move_y = -1;
		start_x = -1;
		start_y = -1;

		valid_locations = nullptr;
		just_started = false;
	}
}

//this function checks if the user can move a piece to the selected spot and moves it there
//precon: piece was selected and spot to move was selected
//postcon: piece is moved/not, checks if user won and returns 1 if they did
int TurnHandler::MovePiece() {
	if (valid_locations[move_x][move_y]) { //if the user picked a valid spot
		moved_piece = nullptr; //resets the mouse moving piece

		//moves the piece and the sprite
		chessboard->MovePiece(start_x, start_y, move_x, move_y);
		chessboard->GetBoard()[move_x][move_y].GetPiece().GetSprite().setPosition(sf::Vector2f(move_x * scale, move_y * scale));

		sound.play(); //plays chesspiece place sound

		chessboard->PrintBoard(); //prints chessboard

		//updates the possible move locations of each piece for each player
		chessboard->GetPossibleMoves(cur_player->GetColor(), cur_player->GetPossibleLocations(), *other_player->GetKing());
		other_player->GetKing()->UpdateLocations(cur_player->GetPossibleLocations());

		chessboard->GetPossibleMoves(other_player->GetColor(), other_player->GetPossibleLocations(), *cur_player->GetKing());
		cur_player->GetKing()->UpdateLocations(other_player->GetPossibleLocations());

		//checks in enemy in check
		if (cur_player->GetPossibleLocations()[other_player->GetKing()->GetX()][other_player->GetKing()->GetY()]) {
			std::cout << other_player->GetColor() << " in check!\n";
		}

		//checks if enemy in checkmate
		if (!chessboard->CheckForMate(other_player->GetPossibleLocations())) {
			std::cout << cur_player->GetColor() << " wins!";
			return 1;
		}

		//switches current player
		Player* temp = cur_player;
		cur_player = other_player;
		other_player = temp;
	}
	else {
		moved_piece->setPosition(sf::Vector2f(sf::Vector2f(start_x * scale, start_y * scale))); //moves the moved piece back to the start coords

		std::cout << "invalid move\n";
	}

	valid_locations = nullptr;

	//resets move/start coords
	move_x = -1;
	move_y = -1;
	start_x = -1;
	start_y = -1;

	//updates bools
	just_started = false;
	is_moving_piece = false;
	draw_valid = false;

	return 0;
}

//this function checks if a selected piece can move
//precon: takes the location of the selection
//postcon: returns true if piece can be moved
bool TurnHandler::CheckPieceSelection(int x, int y) {
	//checks out of bounds
	if (chessboard->IsOutOfBounds(x, y)) {
		return false;
	}

	bool occupied = chessboard->GetBoard()[x][y].GetOccupied(); //checks if space is occupied

	//if space is occupied and matches the player color
	if (occupied && chessboard->GetBoard()[x][y].GetPiece().GetColor() == cur_player->GetColor()) {
		valid_locations = chessboard->GetBoard()[x][y].GetPiece().GetValidLocations(); //gets valid locations of the piece

		//checks if there are any spots it can move
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (valid_locations[i][j]) {
					return true;
				}
			}
		}

	}

	return false;
}

//this function updates the sprite position when its moved by the mouse
//precon: takes the mouse position
//postcon: piece sprite is moved to mouse
void TurnHandler::UpdatePiecePosition(sf::Vector2f mouse_pos) {
	if (is_moving_piece) {
		//moves piece
		moved_piece->setPosition(static_cast<float>(mouse_pos.x - (100 / (moved_piece->getScale().x / 0.9))), static_cast<float>(mouse_pos.y - (100 / (moved_piece->getScale().x / 0.9))));
	}
}

//this function resets the values to default
//precon: takes 2 player pointers
//postcon: values are reset
void TurnHandler::ResetHandler(Player*& p1, Player*& p2) {
	//resets location variables
	start_x = -1;
	start_y = -1;
	move_x = -1;
	move_y = -1;

	valid_locations = nullptr;

	invalid_spot;

	//sets the player pointers
	cur_player = p1;
	other_player = p2;

	//initializes bools
	valid_selection = false;
	just_started = false;

	draw_invalid = false;
	draw_valid = false;

	is_moving_piece = false;

	time_elapsed = 0;

	moved_piece = nullptr;

	//points cur_player back to white
	cur_player = p1;
	other_player = p2;
}