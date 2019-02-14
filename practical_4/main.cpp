#include <SFML/Graphics.hpp>
//#include "Entity.h"
#include "ecm.h"	//Use this instead of entity now
//#include "Player.h"
#include "LevelSystem.h"
//#include "Ghost.h"
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



//std::vector<Entity*> entities;
//std::vector<Ghost*> ghosts;
////Normal Pointers
//Player* player;
//Ghost* ghost;

//Shared Pointers
//std::shared_ptr<Entity> player;
//std::shared_ptr<Entity> ghost;

const int gameWidth = 700;
const int gameHeight = 800;
time_t beginTime = NULL;


EntityManager em;






void Load(RenderWindow &window) {	//passing window so that we can initialise renderer here so that we don't do it in every frame



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

	
	//// check and consume events
	//Event event;
	//while (window.pollEvent(event)) {
	//	if (event.type == Event::Closed) {
	//		window.close();
	//		return;
	//	}
	//}
	//em.update(dt);

	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}



}




void Render(RenderWindow &window) {


	//Renderer::queue(&text);


	/*em.render();*/
	activeScene->render();
	//Renderer::initialise(window);		//We do this in load to save up memory
	Renderer::render();			

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


