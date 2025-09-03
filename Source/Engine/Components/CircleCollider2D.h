#pragma once
#include "ColliderComponent.h"

namespace viper{
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius{ 0.0f };

		// Inherited via ColliderComponent
		void Update(float dt) override;

		bool CheckCollision(ColliderComponent& other) override;

		CLASS_PROTOTYPE(CircleCollider2D)

		void Read(const json::value_t& value) override;

	};
}
