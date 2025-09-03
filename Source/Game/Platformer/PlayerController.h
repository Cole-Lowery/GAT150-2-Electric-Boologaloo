#pragma once
#include "Framework/Component.h"


	class PlayerController : public viper::Component, public viper::ICollidable {
	public:
		float speed = 0;
		float maxSpeed = 0;
		float fireTime = 0.5f;
		float fireTimer = 0.0f;
		float jump = 0;

		viper::RigidBody* m_rigidBody{ nullptr };

	public:
		PlayerController() = default;

		void Start() override;

		void Update(float dt) override;

		CLASS_PROTOTYPE(PlayerController)

			void OnCollision(class viper::Actor* other) override;

		void Read(const viper::json::value_t& value)override;

	};


