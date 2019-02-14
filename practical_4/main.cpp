#include <SFML/Graphics.hpp>
//#include "Entity.h"
#include "ecm.h"	//Use this instead of entity now
#include "Player.h"
#include "LevelSystem.h"
#include "Ghost.h"
#include <iostream>
#include <time.h> //Test to get time
#include <chrono>
#include "system_renderer.h"
#include "pacman.h"


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

const int gameWidth = 700;
const int gameHeight = 800;
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





void Load(RenderWindow &window) {

	/*
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
	


	for (int i = 0; i < 10; i++) {

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

	*/


	Renderer::initialise(window);

	// Load Scene-Local Assets
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// Start at main menu
	activeScene = menuScene;
	//activeScene = gameScene;
	

}
//
void Reset() {
	//entities.clear();
	//Load();
}


void Update(RenderWindow &window) {

	//// Reset clock, recalculate deltatime
	//static Clock clock;
	//float dt = clock.restart().asSeconds();
	//// check and consume events
	//Event event;
	//while (window.pollEvent(event)) {
	//	if (event.type == Event::Closed) {
	//		window.close();
	//		return;
	//	}
	//}
	//em.update(dt);

	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}



}




void Render(RenderWindow &window) {

	////// Draw Everything using normal pointers
	//////for (auto &e : entities) {
	//////	e->render(window);
	//////}

	//Renderer::queue(&text);


	/*em.render();*/
	activeScene->render();
	//Renderer::initialise(window);
	Renderer::render();			//DEBUG HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PAC-MAN");
	Load(window);
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();

	}
	return 0;
}


