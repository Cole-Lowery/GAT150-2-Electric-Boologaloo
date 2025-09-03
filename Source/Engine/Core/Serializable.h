#pragma once
#include "Json.h"

namespace viper {
	class ISerializeable {
	public:
		virtual ~ISerializeable() = default;

		virtual void Read(const json::value_t& value) = 0;
	};
}
