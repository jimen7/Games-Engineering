#pragma once
#include "entity.h"
#include "LevelSystem.h"

class Ghost : public Entity {
private:
	float _speed;

public:
	float RandomFloat(float a, float b);
	void update(double dt) override;
	Ghost();
	void render(sf::RenderWindow &window) const override;
	bool validMove(sf::Vector2f pos);
};