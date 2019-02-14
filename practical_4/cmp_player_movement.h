#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"

class PlayerMovementComponent : public ActorMovementComponent {
public:
	explicit PlayerMovementComponent(Entity *e);
	PlayerMovementComponent() = delete;
	//void render() override;
	void update(double dt) override;
};