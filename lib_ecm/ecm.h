#pragma once

#include <SFML/Graphics.hpp>
//#include "system_renderer.h"	//Specific to practical 4 until Checkpoint 1





#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>

class Component; //forward declare

class Entity {

protected:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;
	float _rotation;
	bool _alive;       // should be updated
	bool _visible;     // should be rendered
	bool _fordeletion; // should be deleted
public:
	Entity();
	virtual ~Entity();
	virtual void update(double dt);
	virtual void render();

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f &_position);
	bool is_fordeletion() const;
	float getRotation() const;
	void setRotation(float _rotation);
	bool isAlive() const;
	void setAlive(bool _alive);
	void setForDelete();
	bool isVisible() const;
	void setVisible(bool _visible);
};


struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
};


class Component {
protected:
	Entity *const _parent;
	bool _fordeletion; // should be removed
	explicit Component(Entity *const p);

public:
	Component() = delete;
	bool is_fordeletion() const;
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual ~Component();
};

































//
//#include "maths.h"
//#include <algorithm>
//#include <memory>
//#include <typeindex>
//#include <vector>
//
//class Component; //forward declare
//
//
//class Entity {
//protected:
//	std::unique_ptr<sf::Shape> _shape;
//	sf::Vector2f _position;
//	Entity(std::unique_ptr<sf::Shape> shp);
//
//public:
//	Entity() = delete;
//	virtual ~Entity() = default;
//
//	virtual void update(const double dt);
//	virtual void render(sf::RenderWindow &window) const = 0;
//
//	void render();
//
//	//virtual void render() const;
//
//
//
//	const sf::Vector2f getPosition();
//	void setPosition(const sf::Vector2f &pos);
//	void move(const sf::Vector2f &pos);
//};
//
//
//struct EntityManager {
//	std::vector<std::shared_ptr<Entity>> list;
//	void update(double dt);
//	void render();
//};