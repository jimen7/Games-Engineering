#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "scene.h"
#include "LevelSystem.h"
#include "Player.h"
#include "Ghost.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;


class MenuScene : public Scene {
private:
	sf::Text text;
	sf::Font _font;
public:
	MenuScene() = default;
	void update(double dt) override;
	void render() override;
	void load()override;
};


class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	void update(double dt) override;
	void render()override;
	void load()override;
};