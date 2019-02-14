#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
	float _speed;
	float _time;
public:
	explicit EnemyAIComponent(Entity *e);
	EnemyAIComponent() = delete;
	void update(double dt) override;
	
};