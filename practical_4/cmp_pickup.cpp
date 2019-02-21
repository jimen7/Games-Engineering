#include <maths.h>
#include "cmp_pickup.h"
#include "pacman.h"
#include "cmp_actor_movement.h"

PickupComponent::PickupComponent(Entity * p, bool big) : Component(p)
{
	_big = big;
	_score = big ? 20 : 10;
}


void PickupComponent::update(double dt) {
	for (const auto & ent : activeScene->getEnts()) {       //every entity in the scene

		
		if ( length( ent->getPosition() - _parent->getPosition() ) < 30.0f) { //within 30.f unit of me

			auto cmpts = ent->GetCompatibleComponent<ActorMovementComponent>(); //get the entity ActorMovementComponent, if it has one

				if (!cmpts.empty()) {        //if it has one

				  // nom nom
					cmpts[0]->setSpeed(cmpts[0]->getSpeed()*1.01f);                   //speed the entity up
						_parent->setForDelete(); //delete myself
					break;                   //stop looking
				}
		}

	}
}