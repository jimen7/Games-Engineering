#include "cmp_pickup.h"

void PickupComponent::setTempEmp(EntityManager *e) {
	_temp_emp = *e;
}


void PickupComponent::update(double dt) {
	for (int i = 0; i < _temp_emp.list.size();i++) {       //every entity in the scene


		//if () {      //within 30.f unit of me
		//	...               //get the entity ActorMovementComponent, if it has one
		//		if (...) {        //if it has one
		//		  // nom nom
		//			...                      //speed the entity up
		//				_parent->setForDelete(); //delete myself
		//			break;                   //stop looking
		//		}
		//}
	}
}