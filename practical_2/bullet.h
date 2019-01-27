#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	//updates All bullets
	static void Update(const float &dt);
	//Render's All bullets
	static void Render(sf::RenderWindow &window);
	//Chose an inactive bullet and use it.
	static void Fire(const sf::Vector2f &pos, const bool mode);
	//Bullet Speed
	static float bulletSpeed;

	~Bullet() = default;
protected:
	static unsigned char bulletPointer;
	static Bullet bullets[256];
	//Called by the static Update()
	void _Update(const float &dt);
	//Never called by our code
	Bullet();
	//false=player bullet, true=Enemy bullet
	bool _mode;
};


//class Bullet : public sf::Sprite {
//public:
//	void Update(const float &dt);
//	Bullet(const sf::Vector2f &pos, const bool mode);
//	~Bullet() = default;
//protected:
//	static unsigned char bulletPointer;
//	static Bullet bullets[256];
//	Bullet();
//	//false=player bullet, true=Enemy bullet
//	bool _mode;
//};