#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "LevelSystem.h"
#include <iostream>
#include <time.h> //Test to get time
#include <chrono>

using namespace sf;
using namespace std;

bool playedBefore = false;

Text text;
Font font;




const Keyboard::Key controls[5] = {
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::Up,  // Player2 UP
	Keyboard::Down, // Player2 Down
	Keyboard::G,   // Enable/Disable AI
};

const int gameWidth = 800;
const int gameHeight = 600;
time_t beginTime = NULL;

std::vector<Entity*> entities;


Player* player;

chrono::steady_clock::time_point start_time;

chrono::steady_clock::time_point current_time;

_int64 best_time;

void Load() {
	if (!playedBefore){
		player = new Player();
		ls::loadLevelFile("res/levels/maze_2.txt");
		// Load font-face from res dir
		font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
		// Set text element to use font
		text.setFont(font);
		// set the character size to 24 pixels
		text.setCharacterSize(24);
		text.setColor(Color::Black);
		//text.setFillColor(Color::Black);
		// Keep Text Centered
		text.setPosition((gameWidth * .1f) - (text.getLocalBounds().width * .5f), 0);
		}

	start_time = chrono::high_resolution_clock::now();
	


	player->setPosition({gameWidth/5.8,gameHeight/4});
	entities.push_back(player);


	
	////Used to print out maze to cmd
	//for (size_t y = 0; y < ls::getHeight(); ++y) {
	//	for (size_t x = 0; x < ls::getWidth(); ++x) {
	//		cout << ls::getTile({ x, y });
	//	}
	//	cout << "///////////////////////" << endl;
	//}

	

}
//
void Reset() {
	entities.clear();
	Load();
}


void Update(RenderWindow &window) {



	current_time = chrono::high_resolution_clock::now();
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

	_int64 total_time = (current_time - start_time).count();

	if (best_time != NULL) {
		text.setString("Current Time:" + to_string(total_time) + "ms, Best Time:" + to_string(best_time) + "ms");
	}
	else {
		text.setString("Current Time:" + to_string(total_time) + "ms");
	}


	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	for (auto &e : entities) {
		e->update(dt);
	}

	if (!player->validMove(player->getPosition())) {
		playedBefore = true;
		Reset();
	}

	if (ls::getTileAt(player->getPosition()) == ls::END) {
		playedBefore = true;

		if (best_time != NULL) {
			if (total_time < best_time) {
			best_time = total_time;
			}
		}
		else {
			best_time = total_time;
		}
		
		Reset();
	}

}




void Render(RenderWindow &window) {

	//draw input level
	ls::render(window);
	// Draw Everything
	for (auto &e : entities) {
		e->render(window);
	}
	window.draw(text);

}

//void Render() {
//	// Draw Everything
//}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "TILE ENGINE MAZE");
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