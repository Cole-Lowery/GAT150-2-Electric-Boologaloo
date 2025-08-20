#include "EnginePCH.h"

namespace viper {
		void Transform::Read(const json::value_t& value)
		{
			json::Read(value, "position", position);
			json::Read(value, "rotation", rotation);
			json::Read(value, "scale", scale);
		}
}