#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "system_renderer.h"
#include "scene.h"


class PickupComponent :public Component {
protected:
	int _score;
	EntityManager _temp_emp;
public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity *p);
	void setTempEmp(EntityManager *e);


	void update(double dt) override;
	//void render() override;

};