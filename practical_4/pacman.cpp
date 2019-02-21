#include "pacman.h"
#include "cmp_enemy_ai.h"
#include "cmp_pickup.h"

#define GHOSTS_COUNT 4

using namespace sf;
using namespace std;
std::shared_ptr<Entity> player;	//Changed this to entity pointers from PLayer
std::vector<std::shared_ptr<Entity>> ghosts;
vector<shared_ptr<Entity>> nibbles;


shared_ptr<Entity> makeNibble(const Vector2ul& nl, bool big) {
	auto cherry = make_shared<Entity>();
	auto s = cherry->addComponent<ShapeComponent>();
	//set colour
	if (!big) {
		s->setShape<sf::CircleShape>(2.f);
		s->getShape().setFillColor(Color::White);
	}
	else {
		s->setShape<sf::CircleShape>(4.f);
		s->getShape().setFillColor(Color::Blue);
	}


	cherry->addComponent<PickupComponent>(big);
	cherry->setPosition(ls::getTilePosition(nl) + Vector2f(10.f, 35.f));
	return cherry;
}

//int ghostCount = 4;	//Before ECM and GHOST_COUNT definition

//NEED TO REDIFINE THIS AS THEY ARE EXTERN'D
std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

Vector2f offset = Vector2f(0.f, 30.f);

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
	player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(ls::getTilePosition(ghost_spawns[rand() % GHOSTS_COUNT]));	//GHOST_COUNT could be "ghosts_spawns.size()"
		g->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
		//g->setAlive(true);
		//g->setVisible(true);
	}

	//clear any remaining nibbles
	for (auto n : nibbles) {
		n->setForDelete();
		n.reset();
	}
	nibbles.clear();

	//white nibbles
	auto nibbleLoc = LevelSystem::findTiles(LevelSystem::EMPTY);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, false);
		//add to _ents and nibbles list
		_ents.list.push_back(cherry);
		nibbles.push_back(cherry);
	}
	//blue nibbles
	nibbleLoc = LevelSystem::findTiles(LevelSystem::WAYPOINT);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, true);
		//add to _ents and nibbles list
		_ents.list.push_back(cherry);		//NEED TO CHANGE FOPR
		nibbles.push_back(cherry);
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
		//player->addComponent<PlayerMovementComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		player->addComponent<PlayerMovementComponent>();

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

		ghost->addComponent<EnemyAIComponent>();

		_ents.list.push_back(ghost);
		ghosts.push_back(ghost);
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
		if (length( (g->getPosition()/*-offset*/) - (player->getPosition()/*-offset*/) ) < 30.f) {
			respawn();
		}
	}

	Scene::update(dt);
}


