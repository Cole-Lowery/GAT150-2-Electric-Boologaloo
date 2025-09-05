#include "FlyingEnemyController.h"
#include "PlatformerGame.h"
#include "../GamePCH.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void FlyingEnemyController::Update(float dt) {



	auto player = owner->scene->GetActorByName<viper::Actor>("platformplayer");
	if (player) {
		viper::vec2 direction = player->transform.position - owner->transform.position;
		m_rigidBody->ApplyForce(direction.Normalized() * speed);
		//if (player->transform.position.x < owner->transform.position.x) dir = -1;
		//else dir = 1;
	}

	/*
	if (dir != 0) {
		m_rigidBody->ApplyForce(viper::vec2{ 1, 0 } *dir * 1000);
	}
	*/

		m_rigidBody->ApplyForce(viper::vec2{ 0, -1 } * 10);
	
}


void FlyingEnemyController::OnCollision(viper::Actor* other) {
	//EVENT_NOTIFY_DATA(touch_enemy, 1);
	//std::cout << "Touching the player" << std::endl;
}

void FlyingEnemyController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);

}