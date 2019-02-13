#include "scene.h"

using namespace sf;
using namespace std;

void Scene::update(double dt) {
	_ents.update(dt);
}

//std::vector<std::shared_ptr<Entity>> Scene::getEnts() {
//	return ;
//}

void Scene::render() { _ents.render(); }		//This does not work, it should not work, but it's given to us. Why?

