#pragma once

namespace viper {
	class Serializable {
	public:
		virtual ~Serializable() = default;

		void Read(const json::value_t& value);
	};

}