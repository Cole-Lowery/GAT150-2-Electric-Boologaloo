#include "Pickup.h"
#include "EnemyController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Pickup)

void Pickup::Start() {
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void Pickup::Update(float dt) {
	//
}


void Pickup::OnCollision(viper::Actor* other) {
	/*if (viper::equalsIgnoreCase(other->tag == "player")) {

	}*/
}

void Pickup::Read(const viper::json::value_t& value) {
	Object::Read(value);

}