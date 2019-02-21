#pragma once
#include <SFML/Graphics.hpp>
#include <ecm.h>
#include "system_renderer.h"
#include "scene.h"


class PickupComponent :public Component {
protected:
	int _score;
	bool _big;
public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity *p, bool big);
	void update(double dt) override;
	void render()  override {};

};