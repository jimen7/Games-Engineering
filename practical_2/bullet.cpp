#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

//Create definition for the constructor
//...

float Bullet::bulletSpeed;

Bullet::Bullet() : Sprite()
{
	setOrigin(16, 16);
	setTexture(spritesheet);
};

unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];


void Bullet::Update(const float &dt) {
	for (Bullet &b : bullets) {			
		b._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow &window) {
	for (Bullet &b : bullets) {			//Not sure this is right
		window.draw(b);
	}
}


void Bullet::Fire(const sf::Vector2f &pos, const bool mode) {
	//WRITE HERE
	bullets[++bulletPointer].setPosition(pos);
	bullets[bulletPointer]._mode = mode;
	if (mode) {
		bullets[bulletPointer].setTextureRect(IntRect(32, 32, 32, 32));
	}
	else {
		bullets[bulletPointer].setTextureRect(IntRect(64, 32, 32, 32));
	}
}

void Bullet::_Update(const float &dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		//off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == play) {
				//player bulelts don't collide with player
				continue;
			}
			if (_mode && s != play) {
				//invader bullets don't collide with other invaders
				continue;
			}
			if (!s->isExploded() &&
				s->getGlobalBounds().intersects(boundingBox)) {
				//Explode the ship
				s->Explode();
				//warp bullet off-screen
				setPosition(-100, -100);
				return;
			}
		}
	}
};



//Bullet::Bullet(const sf::Vector2f &pos, const bool mode) : Sprite() {
//	setPosition(pos);
//	_mode = mode;
//}
//
//void Bullet::Update(const float &dt) {
//	move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
//}