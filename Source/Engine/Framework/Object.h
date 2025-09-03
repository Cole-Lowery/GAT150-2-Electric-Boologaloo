#pragma once
#include "Core/Serializable.h"
#include <string>

#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); }

namespace viper {
	class Object : public ISerializeable {
	public:
		std::string name;
		bool active{ true };

		Object() = default;
		virtual ~Object() = default;

		virtual std::unique_ptr<Object> Clone() = 0;

		void Read(const json::value_t& value) override;
	};
}
