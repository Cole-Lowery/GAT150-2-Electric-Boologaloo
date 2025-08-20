#pragma once
#include "../Math/Vector2.h"
#include "../Core/Serializable.h"

namespace viper
{
	struct Transform : public Serializable
	{
		vec2 position{ 0, 0 };
		float rotation = 0;
		float scale = 1;

		void Read(const viper::Json::value_t& value);

		Transform() = default;
		Transform(const vec2& position, float rotation = 0, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale } 
		{ }
	};
}
