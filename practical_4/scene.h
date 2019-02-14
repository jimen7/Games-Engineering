#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
//#include "Entity.h"
#include "ecm.h"
#include "system_renderer.h"

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void update(double dt);
	virtual void render();
	virtual void load() = 0;
	std::vector<std::shared_ptr<Entity>> &getEnts();

protected:
	EntityManager _ents;
};