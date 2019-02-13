#include "pacman.h"

using namespace sf;
std::shared_ptr<Player> player;	//NEED TO CHANGE THIS TO ENTITY AFTER CHANGING MAIN.CPP
std::vector<std::shared_ptr<Entity>> ghosts;

int ghostCount = 4;

void MenuScene::update(double dt) {
	Scene::update(dt);
	//stringstream stream;
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	// Title text
	Font font;
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString("Almost Pacman");
	text.setPosition((800/*gamewidth*/ * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}


void GameScene::respawn() {

	//player = std::make_shared<Player>();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(ls::getTilePosition(ghost_spawns[rand() % ghostCount]));
	}
}


void GameScene::load() {
	//Load Level
	ls::loadLevelFile("res/levels/pacman.txt");

	//Set up player
	player = std::make_shared<Player>();
	//Push player back to entity manager list
	_ents.list.push_back(player);


	//Set up ghosts
		for (int i = 0; i < ghostCount;i++) {
			auto ghost = std::make_shared<Ghost>();
			_ents.list.push_back(ghost);
			ghosts.push_back(ghost);
	}
	

		respawn();
}


