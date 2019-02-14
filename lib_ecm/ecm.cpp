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


Entity::~Entity(){	
//In order for an Entity to be deleted, you have to loop through all the components and delete them individually. 
//This happens because componenets might be co-dependent, so we loop through them erasing them until there are no more components to delete

	int compNum = 0;
	while (compNum!=_components.size())		//This took me half an hour to write and I still don't understand fully, ASK SAM
	{
		compNum = _components.size();
		_components.erase(	// Removes the elements in the range (first, last).
			remove_if( //Removes all elements satisfying specific criteria, in this case where predicate returns true..
				_components.begin(),
				_components.end(),
				[](auto &current) { return (current.use_count() <= 1); } //use_count returns the number of different shared_ptr instances managing the current object.
			),
				_components.end()
		);
	}
}


void EntityManager::render() {	
	for (auto &e : list) {	//Iterate through the list to render
		if (e->isVisible()) {	
			e->render();
		}
	}
}



void EntityManager::update(double dt) {
	for (auto &e : list) {
		e->update(dt);
	}
}

Component::Component(Entity *const p) : _parent(p), _fordeletion(false) {}

bool Component::is_fordeletion() const { return _fordeletion; }

Component::~Component() {}
