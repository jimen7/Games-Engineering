#include "Player.h"
using namespace sf;
using namespace std;




bool Player::validMove(sf::Vector2f pos) {
	return (ls::getTileAt(pos) != ls::WALL);
}

void Player::update(double dt) {


	//Trying Vector to see if it accepts multoplocation with dt for move function
	sf::Vector2f displacement = { 0.f,0.f, };
	//Move in four directions based on keys
	float xDirection = 0.0f;

	
	//Move Down
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		displacement.x--;
	}
	//Move Up
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		displacement.x++;
	}

	float yDirection = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		displacement.y--;
	}
	//Move Right
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		displacement.y++;
	}

	//Only move with the keyboard if you are not with world tiles


	Vector2f pos = displacement * _speed * float(dt);


	//if (validMove(getPosition() + pos)) {
		move(displacement*float(dt)*_speed);
	//}


		

		

	

		Entity::update(dt);

}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(12.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}