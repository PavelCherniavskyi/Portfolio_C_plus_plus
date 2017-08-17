#include "Headers/source.h"

int main(void)
{
	sf::Image tile_image, choise_image, push_image, choise_main_image_1, choise_main_image_2, choise_main_image_3;

	tile_image.loadFromFile("Resources/images/red.png");
	choise_image.loadFromFile("Resources/images/red.png");
	push_image.loadFromFile("Resources/images/buttons.png");
	choise_main_image_1.loadFromFile("Resources/images/buttons.png");
	choise_main_image_2.loadFromFile("Resources/images/buttons.png");
	choise_main_image_3.loadFromFile("Resources/images/buttons.png");
	choise_image.createMaskFromColor(Color(255, 255, 255));
	
	

	Texture tile_text, choise_text, push_text, choise_main_text_1, choise_main_text_2, choise_main_text_3;
	tile_text.loadFromImage(tile_image);
	choise_text.loadFromImage(choise_image);
	push_text.loadFromImage(push_image);
	choise_main_text_1.loadFromImage(choise_main_image_1);
	choise_main_text_2.loadFromImage(choise_main_image_3);
	choise_main_text_3.loadFromImage(choise_main_image_3);

	Sprite tile_sprite, knight_sprite, choise_sprite, push_sprite, choise_main_sprite_1, choise_main_sprite_2, choise_main_sprite_3;

	tile_sprite.setTexture(tile_text);
	choise_sprite.setTexture(choise_text);
	push_sprite.setTexture(push_text);
	choise_main_sprite_1.setTexture(choise_main_text_1);
	choise_main_sprite_2.setTexture(choise_main_text_2);
	choise_main_sprite_3.setTexture(choise_main_text_3);

	choise_sprite.setTextureRect(IntRect(726, 0, 60, 60));
	knight_sprite.setTextureRect(IntRect(120, 40, 40, 40));
	tile_sprite.setTextureRect(IntRect(0, 0, 570, 580));
	choise_main_sprite_1.setTextureRect(IntRect(0, 261, 220, 64));
	choise_main_sprite_2.setTextureRect(IntRect(0, 325, 220, 64));
	choise_main_sprite_3.setTextureRect(IntRect(0, 392, 220, 64));
	push_sprite.setTextureRect(IntRect(0, 0, 224, 250));
	push_sprite.setPosition(610, 200);

	Font font;
	font.loadFromFile("Resources/JOKERMAN.ttf");
	Text text("", font, 30);
	
	



	int choose;
	bool position = false;
	bool intro = false;
	bool buttonpressed = true;
	int x1, x2, y1, y2;

	Vector2i localPosition;
	Clock clock;
	
	
	matrix_fill();
	while (window.isOpen())
	{
		window.clear(Color(44, 44, 44));
		window.draw(tile_sprite);
		window.draw(push_sprite);
		introdaction();
		localPosition = Mouse::getPosition(window);


		if (localPosition.x > 610 && localPosition.y > 201 && localPosition.x < 831 && localPosition.y < 265){
			choise_main_sprite_1.setPosition(609, 201);
			window.draw(choise_main_sprite_1);

			if (Mouse::isButtonPressed(Mouse::Left)){
				choose = 1;
				intro = true;
			}
		}
		else if (localPosition.x > 610 && localPosition.y > 291 && localPosition.x < 831 && localPosition.y < 355){
			choise_main_sprite_2.setPosition(608, 291);
			window.draw(choise_main_sprite_2);
			if (Mouse::isButtonPressed(Mouse::Left)){
				choose = 0;
				intro = true;
			}
		}
		else if (localPosition.x > 610 && localPosition.y > 382 && localPosition.x < 831 && localPosition.y < 445){
			choise_main_sprite_3.setPosition(610, 385);
			window.draw(choise_main_sprite_3);
			if (Mouse::isButtonPressed(Mouse::Left)){
				window.close();
			}
		}

		window.display();
		if (!Mouse::isButtonPressed(Mouse::Left) && ((localPosition.x > 610 && localPosition.y > 201 && localPosition.x < 831 && localPosition.y < 265) ||
			(localPosition.x > 610 && localPosition.y > 291 && localPosition.x < 831 && localPosition.y < 355)) && intro){

			
			if (choose == 1) CPU = false;
			while (window.isOpen()){

				
				Event event;
				window.clear(Color(44, 44, 44));
				window.draw(tile_sprite);
				localPosition = Mouse::getPosition(window);
								
				while (window.pollEvent(event)){
					switch (event.type)
					{
					case Event::EventType::MouseButtonPressed:
						if (event.key.code == Mouse::Left && buttonpressed){
							localPosition = Mouse::getPosition(window);
							for (int i = 46, n = 0; i <= 525; i += 60, n++){
								for (int j = 46, z = 0; j <= 525; j += 60, z++){
									for (int a = i; a < (60 + i); a++){
										for (int b = j; b < (60 + j); b++){
											if (localPosition.x == b && localPosition.y == a){
												position = true;
												buttonpressed = false;
												x1 = z, y1 = n;
												choise_sprite.setPosition(j, i);
												clock.restart();
											}
										}
									}
								}
							}
						}
						else if (event.key.code == Mouse::Left && !buttonpressed){
							localPosition = Mouse::getPosition(window);
							for (int i = 46, n = 0; i <= 525; i += 60, n++){
								for (int j = 46, z = 0; j <= 525; j += 60, z++){
									for (int a = i; a < (60 + i); a++){
										for (int b = j; b < (60 + j); b++){
											if (localPosition.x == b && localPosition.y == a){
												x2 = z, y2 = n;
												position = true;
												buttonpressed = true;
												choise_sprite.setPosition(j, i);
												clock.restart();
												if (x1 == x2 && y1 == y2);
												else {
													if (!move(x1, y1, x2, y2)) break;
													
													
													if (CPU){
														
														cpu_thinking();
														while (!cpu());
														choise_sprite.setPosition(46 + (setPosition_X * 60), 46 + (setPosition_Y * 60));
														clock.restart();
													}
													
													
												}
											}
										}
									}
								}
							}
						}
						break;
					case Event::EventType::Closed:
						window.close();
						break;
					default: break;
						
					}
				}
				
				if (flag){
					text.setStyle(0);
					text.setFillColor(Color::White);
					text.setPosition(630, 400);
					text.setString("White move");
					
				}

				else {
					text.setStyle(0);
					text.setFillColor(Color::Black);
					text.setPosition(630, 150);
					text.setString("Black move");
				}

				window.draw(text);
				matrix_show();
				if (position && !CPU){
					int time = clock.getElapsedTime().asSeconds();
					if (time < 1) window.draw(choise_sprite);
				} 
				else if (position && CPU){
					int time = clock.getElapsedTime().asSeconds();
					if (time < 1.5) window.draw(choise_sprite);
				}
				window.display();

			}

		}


		


	}

	return 0;
	
}

int move(int x1, int y1, int x2, int y2)
{
	if (DOSKA[y1][x1] == 0){
		wrong_enter();
		return 0;
	}

	for (int a = 0; a < 6; a++) {
		if (DOSKA[y1][x1] == blacks[a] && flag == true){
			not_your_turn();
			return 0;
		}
		else if (DOSKA[y1][x1] == whites[a] && flag == false){
			not_your_turn();
			return 0;
		}
		
	}
	
	if (flag) flag = false;
	else flag = true;
	
	
	
	switch (DOSKA[y1][x1])
	{
	case 2659:	if (!pawn(x1, y1, x2, y2)){
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2657:	if (!bishop(x1, y1, x2, y2)){
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2658:	if (!knight(x1, y1, x2, y2)){
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2656:	if (!rock(x1, y1, x2, y2)){
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2655:	if (!queen(x1, y1, x2, y2)) {
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2654:	if (!king(x1, y1, x2, y2)){
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2653:    if (!pawn(x1, y1, x2, y2)) {
					  if (flag) flag = false;
					  else flag = true;
					  return 0;
	}
				  if (CPU){
					  if (flag) flag = false;
					  else flag = true;
				  }
				  break;
	case 2652:	if (!bishop(x1, y1, x2, y2)) {
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2651:	if (!knight(x1, y1, x2, y2)) {
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2650:	if (!rock(x1, y1, x2, y2)) {
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2649:	if (!queen(x1, y1, x2, y2)) {
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	case 2648:	if (!king(x1, y1, x2, y2)) {
					if (flag) flag = false;
					else flag = true;
					return 0;
	}
				if (CPU){
					if (flag) flag = false;
					else flag = true;
				}
				break;
	default:        return 0;
	}

	return 1;
}

void matrix_fill(void)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i == 0 && j == 0) || (i == 0 && j == 7)) DOSKA[i][j] = bR;
			if ((i == 0 && j == 1) || (i == 0 && j == 6)) DOSKA[i][j] = bN;
			if ((i == 0 && j == 2) || (i == 0 && j == 5)) DOSKA[i][j] = bB;
			if (i == 0 && j == 3) DOSKA[i][j] = bQ;
			if (i == 0 && j == 4) DOSKA[i][j] = bK;
			if (i == 1) DOSKA[i][j] = bP;

			if ((i == 7 && j == 0) || (i == 7 && j == 7)) DOSKA[i][j] = wR;
			if ((i == 7 && j == 1) || (i == 7 && j == 6)) DOSKA[i][j] = wN;
			if ((i == 7 && j == 2) || (i == 7 && j == 5)) DOSKA[i][j] = wB;
			if (i == 7 && j == 3) DOSKA[i][j] = wQ;
			if (i == 7 && j == 4) DOSKA[i][j] = wK;
			if (i == 6) DOSKA[i][j] = wP;

		}
	}
}

void matrix_show(void)
{
	Image white_pawn_image, white_bishop_image, white_knight_image, white_rock_image, white_queen_image, white_king_image;
	Image black_pawn_image, black_bishop_image, black_knight_image, black_rock_image, black_queen_image, black_king_image;
	

	white_pawn_image.loadFromFile("Resources/images/1.png");
	white_bishop_image.loadFromFile("Resources/images/1.png");
	white_knight_image.loadFromFile("Resources/images/1.png");
	white_rock_image.loadFromFile("Resources/images/1.png");
	white_queen_image.loadFromFile("Resources/images/1.png");
	white_king_image.loadFromFile("Resources/images/1.png");
	black_pawn_image.loadFromFile("Resources/images/1.png");
	black_bishop_image.loadFromFile("Resources/images/1.png");
	black_knight_image.loadFromFile("Resources/images/1.png");
	black_rock_image.loadFromFile("Resources/images/1.png");
	black_queen_image.loadFromFile("Resources/images/1.png");
	black_king_image.loadFromFile("Resources/images/1.png");

	

	Texture white_pawn_text, white_bishop_text, white_knight_text, white_rock_text, white_queen_text, white_king_text;
	Texture black_pawn_text, black_bishop_text, black_knight_text, black_rock_text, black_queen_text, black_king_text;
	

	white_pawn_text.loadFromImage(white_pawn_image);
	white_bishop_text.loadFromImage(white_bishop_image);
	white_knight_text.loadFromImage(white_knight_image);
	white_rock_text.loadFromImage(white_rock_image);
	white_queen_text.loadFromImage(white_queen_image);
	white_king_text.loadFromImage(white_king_image);
	black_pawn_text.loadFromImage(black_pawn_image);
	black_bishop_text.loadFromImage(black_bishop_image);
	black_knight_text.loadFromImage(black_knight_image);
	black_rock_text.loadFromImage(black_rock_image);
	black_queen_text.loadFromImage(black_queen_image);
	black_king_text.loadFromImage(black_king_image);



	Sprite white_pawn_sprite, white_bishop_sprite, white_knight_sprite, white_rock_sprite, white_queen_sprite, white_king_sprite;
	Sprite black_pawn_sprite, black_bishop_sprite, black_knight_sprite, black_rock_sprite, black_queen_sprite, black_king_sprite;
	

	white_pawn_sprite.setTexture(white_pawn_text);
	white_bishop_sprite.setTexture(white_bishop_text);
	white_knight_sprite.setTexture(white_knight_text);
	white_rock_sprite.setTexture(white_rock_text);
	white_queen_sprite.setTexture(white_queen_text);
	white_king_sprite.setTexture(white_king_text);
	black_pawn_sprite.setTexture(black_pawn_text);
	black_bishop_sprite.setTexture(black_bishop_text);
	black_knight_sprite.setTexture(black_knight_text);
	black_rock_sprite.setTexture(black_rock_text);
	black_queen_sprite.setTexture(black_queen_text);
	black_king_sprite.setTexture(black_king_text);




	white_pawn_sprite.setTextureRect(IntRect(200, 40, 40, 40));
	white_bishop_sprite.setTextureRect(IntRect(80, 40, 40, 40));
	white_knight_sprite.setTextureRect(IntRect(120, 40, 40, 40));
	white_rock_sprite.setTextureRect(IntRect(160, 40, 40, 40));
	white_queen_sprite.setTextureRect(IntRect(40, 40, 40, 40));
	white_king_sprite.setTextureRect(IntRect(0, 40, 40, 40));
	black_pawn_sprite.setTextureRect(IntRect(200, 0, 40, 40));
	black_bishop_sprite.setTextureRect(IntRect(80, 0, 40, 40));
	black_knight_sprite.setTextureRect(IntRect(120, 0, 40, 40));
	black_rock_sprite.setTextureRect(IntRect(160, 0, 40, 40));
	black_queen_sprite.setTextureRect(IntRect(40, 0, 40, 40));
	black_king_sprite.setTextureRect(IntRect(0, 0, 40, 40));



	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (DOSKA[i][j] == wP){ white_pawn_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(white_pawn_sprite); }
			if (DOSKA[i][j] == wB){ white_bishop_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(white_bishop_sprite); }
			if (DOSKA[i][j] == wN){ white_knight_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(white_knight_sprite); }
			if (DOSKA[i][j] == wR){ white_rock_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(white_rock_sprite); }
			if (DOSKA[i][j] == wQ){ white_queen_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(white_queen_sprite); }
			if (DOSKA[i][j] == wK){ white_king_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(white_king_sprite); }
			if (DOSKA[i][j] == bP){ black_pawn_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(black_pawn_sprite); }
			if (DOSKA[i][j] == bB){ black_bishop_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(black_bishop_sprite); }
			if (DOSKA[i][j] == bN){ black_knight_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(black_knight_sprite); }
			if (DOSKA[i][j] == bR){ black_rock_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(black_rock_sprite); }
			if (DOSKA[i][j] == bQ){ black_queen_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(black_queen_sprite); }
			if (DOSKA[i][j] == bK){ black_king_sprite.setPosition(56 + (j * 60), 56 + (i * 60)); window.draw(black_king_sprite); }
		}
	}
	
}

void introdaction(void)
{
	Font font;
	font.loadFromFile("Resources/JOKERMAN.ttf");
	Text text("Choose your option", font, 27);
	text.setFillColor(Color::White);
	text.setStyle(0);
	text.setPosition(590, 100);
	window.draw(text);
}

void wrong_move(void)
{
	Clock clock;
	int time = clock.getElapsedTime().asSeconds();
	clock.restart();
	Font font;
	font.loadFromFile("Resources/JOKERMAN.ttf");
	Text text("", font, 30);
	text.setFillColor(Color::Red);
	text.setStyle(0);
	text.setPosition(600, 260);
	text.setString("Wrong move!!!");
	while (time != 1){
		window.display();
		window.draw(text);
		time = clock.getElapsedTime().asSeconds();
		matrix_show();
	}
	
	
}

void win(void)
{
	Font font;
	font.loadFromFile("Resources/JOKERMAN.ttf");
	Text text("", font, 35);
	text.setFillColor(Color::Red);
	text.setStyle(0);

	Image tile_image;
	tile_image.loadFromFile("Resources/images/red.png");
	Texture tile_text;
	tile_text.loadFromImage(tile_image);
	Sprite tile_sprite;
	tile_sprite.setTexture(tile_text);
	tile_sprite.setTextureRect(IntRect(0, 0, 570, 580));
	if (!flag) text.setString("Whites win!!!");
	else text.setString("Blacks win!!!");
	text.setPosition(600, 260);
	

	while (window.isOpen()){
		Event event;
		window.clear(Color(44, 44, 44));
		window.draw(text);
		window.draw(tile_sprite);
		matrix_show();
		window.display();
		while (window.pollEvent(event)){
			if (event.type == Event::EventType::Closed)
			window.close();
		}
	}
	

	
	
	exit(0);
}

void cpu_thinking(void)
{
	Font font;
	font.loadFromFile("Resources/JOKERMAN.ttf");
	Text text("", font, 30);
	text.setFillColor(Color(153,217,234));
	text.setStyle(0);
	text.setString("CPU thinking...");
	text.setPosition(600, 260);
	
	window.draw(text);
	matrix_show();
	window.display();
	
	
}

void wrong_enter(void)
{
	Clock clock;
	int time = clock.getElapsedTime().asSeconds();
	clock.restart();
	Font font;
	font.loadFromFile("Resources/JOKERMAN.ttf");
	Text text("", font, 30);
	text.setFillColor(Color::Red);
	text.setStyle(0);
	text.setString("Choose you figure");
	text.setPosition(600, 260);
	while (time != 1){
		window.display();
		window.draw(text);
		time = clock.getElapsedTime().asSeconds();
		matrix_show();
	}
}

void not_your_turn(void)
{
	Clock clock;
	int time = clock.getElapsedTime().asSeconds();
	clock.restart();
	Font font;
	font.loadFromFile("Resources/JOKERMAN.ttf");
	Text text("", font, 30);
	text.setFillColor(Color::Red);
	text.setStyle(0);
	text.setString("It's not your turn");
	text.setPosition(600, 260);
	while (time != 1){
		window.display();
		window.draw(text);
		time = clock.getElapsedTime().asSeconds();
		matrix_show();
	}

}


