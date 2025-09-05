#pragma once
#include "Framework/Component.h"


class Pickup : public viper::Component, public viper::ICollidable {
public:
	

	viper::RigidBody* m_rigidBody{ nullptr };

public:
	Pickup() = default;

	void Start() override;

	void Update(float dt) override;

	CLASS_PROTOTYPE(Pickup)

		void OnCollision(class viper::Actor* other) override;

	void Read(const viper::json::value_t& value)override;

};


