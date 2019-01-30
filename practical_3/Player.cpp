#include "player.h"
using namespace sf;
using namespace std;

void Player::update(double dt) {
	//Move in four directions based on keys
	float yDirection = 0.0f;
	//Move Down
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		yDirection--;
	}
	//Move Up
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		yDirection++;
	}

	float xDirection = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		xDirection--;
	}
	//Move Right
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		xDirection++;
	}

	move({ xDirection * 200.f /** dt*/,yDirection * 200.f /** dt*/ });

		Entity::update(dt);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}