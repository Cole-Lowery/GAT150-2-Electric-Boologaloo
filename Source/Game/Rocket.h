#pragma once
#include "Framework/Component.h"


class Rocket : public viper::Component, public viper::ICollidable {
public:
	float speed = 20.0f;

public:
	Rocket() = default;

	viper::RigidBody* m_rigidBody{ nullptr };

	CLASS_PROTOTYPE(Rocket)

		void Start() override;

	void Update(float dt) override;

	void OnCollision(viper::Actor* other) override;

	void Read(const viper::json::value_t& value) override;
private:

};