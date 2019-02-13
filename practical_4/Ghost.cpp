#include "Ghost.h"
using namespace sf;
using namespace std;




bool Ghost::validMove(sf::Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL);
}

float Ghost::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void Ghost::update(double dt) {

	float randNumx = RandomFloat(-15.0, 15.0f);
	float randNumy = RandomFloat(-15.0, 15.0f);
	//Trying Vector to see if it accepts multoplocation with dt for move function

	sf::Vector2f displacement = { randNumx,randNumy, };
	//Move in four directions based on keys


	
	//Only move with the keyboard if you are not with world tiles


	Vector2f pos = displacement * _speed * float(dt);


	//if (validMove(getPosition() + pos)) {
	move(displacement*float(dt)*_speed);
	//}








	Entity::update(dt);

}

Ghost::Ghost()
	: _speed(200.0f), Entity(make_unique<CircleShape>(12.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Ghost::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
	//Renderer::queue(_shape.get());
}