#include "cmp_enemy_ai.h"

using namespace std;
using namespace sf;

float value = 0.0f;

static const Vector2i directions[] = { { 1, 0 },{ 0, 1 },{ 0, -1 },{ -1, 0 } };

//EnemyAIComponent::EnemyAIComponent(Entity *e) : ActorMovementComponent(e),_speed(100.f),_time(0.f) {}	//Before AI

EnemyAIComponent::EnemyAIComponent(Entity *e) : ActorMovementComponent(e), _state(ROAMING), _direction(directions[(rand() % 4)]) {}


void EnemyAIComponent::update(double dt) {
	//amount to move
	const auto mva = (float)(dt * _speed);
	//Curent position
	const Vector2f pos = _parent->getPosition();
	//Next position
	const Vector2f newpos = pos + _direction * mva;
	//Inverse of our current direction
	const Vector2i baddir = -1 * Vector2i(_direction);
	//Random new direction
	Vector2i newdir = directions[(rand() % 4)];


	switch (_state) {
	case ROAMING:
		if (ls::getTileAt(newpos) == ls::WALL)// Wall in front or at waypoint
		{
			_state = ROTATING;
		}
		else {
			move(_direction*mva); //keep moving
		}
		break;

	case ROTATING:
		while (
			// Don't reverse
			newdir == baddir ||
			// and Don't pick a direction that will lead to a wall
			ls::getTileAt(pos + (Vector2f(newdir)*25.0f)) == ls::WALL		//25 is the tile size
			) {
			newdir = directions[rand() % 4]; // pick new direction
		}
		_direction = Vector2f(newdir);
		_state = ROTATED;
		break;

	case ROTATED:
		//have we left the waypoint?
		if (LevelSystem::getTileAt(pos) != LevelSystem::WAYPOINT) {
			_state = ROAMING; //yes
		}
		move(_direction * mva); //No
		break;

	default:
		break;
	}


	ActorMovementComponent::update(dt);
}





////THIS WAS IN UPDATE AND MAKES GHOSTS MOVE TO A DIRECTION EVERY 5 SECONDS
//_time += dt;
//if (_time > 2.0f) {
//	value = ((double)rand() / (RAND_MAX));
//	_time = 0;
//}
//
//if (value < 0.25f)
//	move(Vector2f(_speed * dt, 0.0f));
//else if (value < 0.5f)
//	move(Vector2f(-_speed * dt, 0.0f));
//else if (value < 0.75f)
//	move(Vector2f(0.0f, _speed * dt));
//else if (value < 1.0f)
//	move(Vector2f(0.0f, -_speed * dt));