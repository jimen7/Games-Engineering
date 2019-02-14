#include "ecm.h"

using namespace std;
using namespace sf;

Entity::Entity() : _position({ 0.0f,0.0f }), _rotation(0.0f), _alive(true), _visible(true),_fordeletion(false){}

const Vector2f& Entity::getPosition() const { return (_position); }	//BEFORE DEBUG>>WALL WORKING
//const Vector2f Entity::getPosition() const { return (_position + Vector2f(0.0f, 30.0f)); } // Doesn't start from top left, but doesn't actually change


void Entity::setPosition(const Vector2f &pos) { _position = pos /*+ Vector2f(0.0f, 15.0f)*/; }		//BUT WORKS HER? WHAT? ASK SAM

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


Entity::~Entity(){	//This took me half an hour to write and I still don't understand fully, ASK SAM

//In order for an Entity to be deleted, you have to loop through all the components and delete them individually. 
//This happens because componenets might be co-dependent, so we loop through them erasing them until there are no more components to delete

	int compNum = 0;	//Current Component Size(basically)
	while (compNum!=_components.size())		
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

	if (_components.size() > 0) {
		throw std::runtime_error(
			"Can't delete entity, components being used somewhere");
	}

	_components.clear();

}


void EntityManager::render() {	
	for (auto &e : list) {	//Iterate through the list to render only if the objects are on the screen
		if (e->isVisible()) {	
			e->render();
		}
	}
}

void EntityManager::update(double dt) {		//Needed to change due to componenets

	for (size_t i = 0; i < list.size();i++) {	//Need to change to basic for loop to delete next from list :(
		
		//Handles objects that are for deletion, then continues
		if (list[i]->is_fordeletion()) {
			list.erase(list.begin()+i);	//This is why we needed advanced for loop, to find out posistion in list
			--i;	//Go back to proper number for update
			continue;
		}

		//Update all object that should be updated and are alive
		if (list[i]->isAlive()) {
			list[i]->update(dt);
		}

	}

}


//void EntityManager::update(double dt) {	//Old method
//	for (auto &e : list) {
//		e->update(dt);
//	}
//}

Component::Component(Entity *const p) : _parent(p), _fordeletion(false) {}

bool Component::is_fordeletion() const { return _fordeletion; }

Component::~Component() {}
