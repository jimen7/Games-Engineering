#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;




const Keyboard::Key controls[5] = {
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::Up,  // Player2 UP
	Keyboard::Down, // Player2 Down
	Keyboard::G,   // Enable/Disable AI
};

const int gameWidth = 800;
const int gameHeight = 600;

std::vector<Entity*> entities;


Player* player;


void Load() {
	player = new Player();
	player->setPosition({gameWidth/2,gameHeight/2});
	entities.push_back(player);
}
//
void Reset() {

}


void Update(RenderWindow &window) {
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


	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	for (auto &e : entities) {
		e->update(dt);
	}

}




void Render(RenderWindow &window) {
	// Draw Everything
	for (auto &e : entities) {
		e->render(window);
	}

}

//void Render() {
//	// Draw Everything
//}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "TILE ENGINE");
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