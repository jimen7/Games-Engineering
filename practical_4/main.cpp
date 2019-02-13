#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "LevelSystem.h"
#include "Ghost.h"
#include <iostream>
#include <time.h> //Test to get time
#include <chrono>
#include "system_renderer.h"

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

//std::vector<Entity*> entities;


std::vector<Ghost*> ghosts;

EntityManager em;

////Normal Pointers
//Player* player;
//Ghost* ghost;

//Shared Pointers
std::shared_ptr<Entity> player;
std::shared_ptr<Entity> ghost;





void Load() {
	if (!playedBefore){

		////Normal Pointer
		//player = new Player();

		//Shared pointer
		player = std::make_shared<Player>();
		//ls::loadLevelFile("res/levels/maze_2.txt");
		// Load font-face from res dir
		font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
		// Set text element to use font
		text.setFont(font);
		// set the character size to 24 pixels
		text.setCharacterSize(18);
		text.setColor(Color::Black);
		//text.setFillColor(Color::Black);
		// Keep Text Centered
		text.setPosition((gameWidth * .1f) - (text.getLocalBounds().width * .5f), 0);
		}
	


	for (int i = 0; i < 4; i++) {

		////Normal Pointers
		//ghost = new Ghost();
		//entities.push_back(ghost);
		//Shared Pointers
		ghost = std::make_shared<Ghost>();
		ghost->setPosition({ gameWidth / 2,gameHeight / 2 });
		em.list.push_back(ghost);
	}


	player->setPosition({gameWidth/5.8,gameHeight/4});

	//player->setPosition({400.f,400.f});
	
	////Normal Pointer
	//entities.push_back(player);

	//Shared POinter
	em.list.push_back(player);
	


	
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
	//entities.clear();
	Load();
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

	em.update(dt);




}




void Render(RenderWindow &window) {

	// Draw Everything using normal pointers
	//for (auto &e : entities) {
	//	e->render(window);
	//}
	//window.draw(text);
	Renderer::queue(&text);
	//Renderer::render();

	em.render(window);

}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PAC-MAN");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();

	}
	return 0;
}


