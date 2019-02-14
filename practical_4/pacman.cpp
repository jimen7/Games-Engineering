#include "pacman.h"


#define GHOSTS_COUNT 4

using namespace sf;
using namespace std;
std::shared_ptr<Entity> player;	//Changed this to entity pointers from PLayer
std::vector<std::shared_ptr<Entity>> ghosts;

//int ghostCount = 4;	//Before ECM and GHOST_COUNT definition

//NEED TO REDIFINE THIS AS THEY ARE EXTERN'D
std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

void MenuScene::update(double dt) {

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	//stringstream stream;
	text.setString("Almost Pacman, Press Space to Continue");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}



void MenuScene::load() {
	// Title text
	
	_font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(_font);
	text.setCharacterSize(24);
	text.setString("Almost Pacman");
	text.setPosition((400/*gamewidth*/ * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}


void GameScene::respawn() {

	//player = std::make_shared<Player>();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(ls::getTilePosition(ghost_spawns[rand() % GHOSTS_COUNT]));
	}
}


void GameScene::load() {
	//Load Level
	ls::loadLevelFile("res/levels/pacman.txt",25.0f);


	////Before ecm player set-up
	//player = std::make_shared<Player>();
	////Push player back to entity manager list
	//_ents.list.push_back(player);


	////Before ecm ghost set-up
	//	for (int i = 0; i < ghostCount;i++) {
	//		auto ghost = std::make_shared<Ghost>();
	//		_ents.list.push_back(ghost);
	//		ghosts.push_back(ghost);
	//	}
	
	//Setting up player using cmp_sprite and ecm library
	{
		player = make_shared<Entity>();

		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(player);
	}


	//Ghost colours
	const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
							   {219, 133, 28},   // orange Clyde
							   {70, 191, 238},   // cyan Inky
							   {234, 130, 229} }; // pink Pinky


	//Setting up ghosts using cmp_sprite and acm library
	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(ghost);
	}

		respawn();
}


void GameScene::render() {
	ls::render(Renderer::getWindow()); //After 20 different things this works, ask Sam why
	Scene::render();
}


void GameScene::update(double dt) {
	// Return to main menu
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}

	// Reset game when ghost hists pacman
	for (auto& g : ghosts) {
		if (length(g->getPosition() - player->getPosition()) < 30.f) {
			respawn();
		}
	}

	Scene::update(dt);
}


