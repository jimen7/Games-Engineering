#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

//Create definition for the constructor
//...

float Bullet::bulletSpeed;

Bullet::Bullet() {};


//ACCESSING "BULLETS" and bullets char at all SEEMS TO BREAK IT

void Bullet::Update(const float &dt) {
	//for (Bullet b : bullets) {			//Not sure this is right
	//	b.move(0.f, b._mode * bulletSpeed * 50.0f);	//CAN I MULTIPLY BOOLEAN WITH FLOAT?
	//}
}

void Bullet::Render(sf::RenderWindow &window) {
	//for (Bullet b : bullets) {			//Not sure this is right
	//	window.draw(b);
	//}
}


void Bullet::Fire(const sf::Vector2f &pos, const bool mode) {
	//WRITE HERE
	//bullets[bulletPointer].setPosition(pos);
	//bullets[bulletPointer]._mode = mode;
}





//Bullet::Bullet(const sf::Vector2f &pos, const bool mode) : Sprite() {
//	setPosition(pos);
//	_mode = mode;
//}
//
//void Bullet::Update(const float &dt) {
//	move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
//}