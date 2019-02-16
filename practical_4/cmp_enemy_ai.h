#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"
#include "LevelSystem.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	enum state { ROAMING, ROTATING, ROTATED };
	state _state;
	//float _speed;	Before proper AI implementation
	//float _time;
public:
	explicit EnemyAIComponent(Entity *e);
	EnemyAIComponent() = delete;
	void update(double dt) override;
	
};