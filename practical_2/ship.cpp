//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;





Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
	_exploded = false;
};

void Ship::Update(const float &dt) {
	if (_exploded) {
		_explosiontime -= dt;
	}
	if (_explosiontime <= 0.f) {
		setColor(Color(0, 0, 0, 0));
	}
}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

void Ship::Explode() {
	_exploded = true;
}


bool Ship::isExploded() const {
	return _exploded;
}

//Invader
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}


bool Invader::direction;
float Invader::speed;

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size()-1; ++i) {
			ships[i]->move(0, 24);
		}
	}

	static float firetime = 0.f;
	firetime -= dt;
	if (firetime <= 0 && rand() % 100 == 0 && !_exploded) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.f + (rand() % 60);
	}

}


void Invader::Explode() {
	Ship::Explode();
	setTextureRect(IntRect(128, 32, 32, 32));
}



Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}


float Player::playerSpeed;

void Player::Update(const float &dt) {
	Ship::Update(dt);
	float direction = 0.0f;
	//Move left
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		direction--;
	}
	//Move Right
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		direction++;
	}
	//if (getPosition().x < gameWidth) {
		move(direction * playerSpeed * dt, 0);
	//}

		

		//Bullets
		static float firetime = 0.f;
		firetime -= dt;
		if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
			Bullet::Fire(getPosition(), false);
			firetime = 0.7f;
		}
	
}


void Player::Explode() {
	Ship::Explode();
	setTextureRect(IntRect(0, 32, 32, 32));
}

