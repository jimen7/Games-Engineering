//ship.h
#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	//Default constructor is hidden
	Ship();
	//Explosion variables
	bool _exploded;
	float _explosiontime = 0.2f;
public:
	//Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	//Pure virtual deconstructor -- makes this an abstract class
	virtual ~Ship() = 0;
	//Update, virtual so can be overrided, but not pure virtual
	virtual void Update(const float &dt);

	//Explosion variables
	bool isExploded() const;
	virtual void Explode();
};

class Invader : public Ship {
public:
	static bool direction;
	static float speed;
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;
	void Explode();
};


class Player : public Ship {
public:
	Player();
	static float playerSpeed;
	void Update(const float &dt) override;
	void Explode();
};