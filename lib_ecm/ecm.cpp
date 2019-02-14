#include "ecm.h"

using namespace std;
using namespace sf;

Entity::Entity() : _position({ 0.0f,0.0f }), _rotation(0.0f), _alive(true), _visible(true),_fordeletion(false){}

const Vector2f& Entity::getPosition() const { return _position + Vector2f(0.0f, 30.0f); }

void Entity::setPosition(const Vector2f &pos) { _position = pos; }

//void Entity::move(const Vector2f &pos) { _position += pos; }

void Entity::update(const double dt) {
	//_shape->setPosition(_position);
	for (auto c : _components) {
		c->update(dt);
	}
}

bool Entity::is_fordeletion() const { return _fordeletion; }
//Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}


void Entity::render() {
//	Renderer::queue(_shape.get());	//Removed this as its specific to Practical 4
	for (auto c : _components) {
		c->render();
	}
}

float Entity::getRotation() const { return _rotation; }

void Entity::setRotation(float rotation) { _rotation = rotation; }

bool Entity::isAlive() const { return _alive; }

void Entity::setAlive(bool alive) { _alive = alive; }

void Entity::setForDelete() { 
	_fordeletion = true;
	_alive = false;
	_visible = false;
}

bool Entity::isVisible() const { return _visible; }

void Entity::setVisible(bool visible) { _visible = visible; }

void EntityManager::render() {	//was working
	for (auto &e : list) {
		e->render();
	}
}



void EntityManager::update(double dt) {
	for (auto &e : list) {
		e->update(dt);
	}
}

Component::Component(Entity *const p) : _parent(p), _fordeletion(false) {}

Entity::~Entity(){}