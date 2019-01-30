#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;


float initialXpos = 100.0f;
float initialYpos = 50.0f;
float invaderSpace = 60.0f;

std::vector<Ship *> ships;

Vector2f ballVelocity;
bool server = false;


Font font;
Text text;
int player1Score = 0;
int player2Score = 0;


bool changeBallDir = true;
float randNumx;
bool aiEnabled = false;

const Keyboard::Key controls[5] = {
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::Up,  // Player2 UP
	Keyboard::Down, // Player2 Down
	Keyboard::G,   // Enable/Disable AI
};


Ship* play;




void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	//invader.setTexture(spritesheet);
	//invader.setTextureRect(sf::IntRect(0, 0, 32, 32));

	//Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });
	//ships.push_back(inv);

	//Create Invaders
	for (int r = 0; r < invaders_rows; r++) {				
		auto rect = IntRect(0, 0, 32, 32);
		for (int c = 0; c < invaders_columns; c++) {
			Vector2f position = { initialXpos + c*invaderSpace , initialYpos};
			auto inv = new Invader(rect, position);
			Invader::speed = 20.0f;
			ships.push_back(inv);
		}
		initialYpos = initialYpos + 50.0f;
	}

	play = new Player();
	Player::playerSpeed = 300.0f;
	ships.push_back(play);

}
//
void Reset() {
	for (auto &s : ships) {
		delete s;
	};

	ships.clear();
	Load();

}


void Update(RenderWindow &window) {

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		Reset();
	}

	
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	for (auto &s : ships) {
		//if (s != play) {
			s->Update(dt);
		//}
			
	};

	
	//play->Update(dt);

	Bullet::Update(dt);

	
	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	

	

}



void Render(RenderWindow &window) {
	// Draw Everything
	//window.draw(invader);
	for (const auto s : ships) {
		window.draw(*s);
	}
	//window.draw(*play);			//WHY DOES IT WORK WITH A POINTER

	Bullet::Render(window);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}



















//
//int main(){
//  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//  sf::CircleShape shape(100.f);
//  shape.setFillColor(sf::Color::Green);
//
//  while (window.isOpen()){
//      sf::Event event;
//      while (window.pollEvent(event)){
//      if (event.type == sf::Event::Closed){
//        window.close();
//      }
//    }
//    window.clear();
//    window.draw(shape);
//    window.display();
//  }
//  return 0;
//}