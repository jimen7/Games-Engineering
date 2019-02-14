#include "cmp_player_movement.h"

using namespace std;
using namespace sf;

PlayerMovementComponent::PlayerMovementComponent(Entity *e) : ActorMovementComponent(e) {}

void PlayerMovementComponent::update(double dt) {
	//Trying Vector to see if it accepts multoplocation with dt for move function
	sf::Vector2f displacement = { 0.f,0.f, };

	//Move in four directions based on keys

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
}


