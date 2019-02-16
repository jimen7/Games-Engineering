#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "system_renderer.h"
#include "scene.h"


class PickupComponent :public Component {
protected:
	int _score;
public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity *p);

	void update(double dt) override;
	//void render() override;

};