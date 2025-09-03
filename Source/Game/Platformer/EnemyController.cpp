#include "EnemyController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void EnemyController::Update(float dt) {

	float dir = 0;

	auto player = owner->scene->GetActorByName<viper::Actor>("platformplayer");
	if (player) {
		if (player->transform.position.x < owner->transform.position.x) dir = -1;
		else dir = 1;
	}

	if (dir != 0) {
		m_rigidBody->ApplyForce(viper::vec2{ 1, 0 } *dir * 1000);
	}

	if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->ApplyForce(viper::vec2{ 0, -1 } *100000);
	}
}


void EnemyController::OnCollision(viper::Actor* other) {

}

void EnemyController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);

}