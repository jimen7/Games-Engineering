#include "cmp_sprite.h"


using namespace std;

//void SpriteComponent::update(double dt) {		//Was given to us like this, think it was a mistake
//	_sprite->setPosition(_parent->getPosition());	
//}

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition()-sf::Vector2f(0.f,30.f));		//OFFSET IS HERE 
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(make_shared<sf::CircleShape>()) {}