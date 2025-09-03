#pragma once
#include "Vector2.h"
#include "Core/Serializable.h"

namespace viper {
	struct Transform : public ISerializeable {
	
		vec2 position{ 0, 0 };
		float rotation = 0;
		float scale = 1;

		Transform() = default;
		Transform(const vec2& position, float rotation = 0, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale } {}

		// Inherited via Serializeable
		void Read(const json::value_t& value);
	};
}