#include "entity.h"
using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position + Vector2f(0.0f, 30.0f); }

void Entity::setPosition(const Vector2f &pos) { _position = pos; }

void Entity::move(const Vector2f &pos) { _position += pos; }

void Entity::update(const double dt) {
	_shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}


void EntityManager::render(sf::RenderWindow &window) {
	for (auto &e : list) {
		e->render(window);
	}
}

void EntityManager::update(double dt) {
	for (auto &e : list) {
		e->update(dt);
	}
}