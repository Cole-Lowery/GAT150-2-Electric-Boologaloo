#pragma once
#include "Font.h"
#include "Renderer.h"
#include "../Math/Vector3.h"

#include <memory>
#include <string>

namespace viper {
	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr <class Font> font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const vec3& color);
		void Draw(Renderer& renderer, int x, int y);

	private:
		std::shared_ptr< class Font > m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}
