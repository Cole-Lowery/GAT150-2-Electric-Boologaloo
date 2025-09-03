#include "Text.h"
#include "Core/Logger.h"
#include "../Math/Vector3.h"

namespace viper {
viper::Text::~Text() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
	}
}

bool viper::Text::Create(Renderer& renderer, const std::string& text, const vec3& color) {
	// create a surface using the font, text string and color
	SDL_Color c{ (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), text.size(), c);
	if (surface == nullptr) {
		Logger::Error("Could not create surface. ");
		
		return false;
	}

	// create a texture from the surface, only textures can render to the renderer
	m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
	if (m_texture == nullptr) {
		SDL_DestroySurface(surface);
		Logger::Error("Could not create texture {}", SDL_GetError());
		
		return false;
	}

	// free the surface, no longer needed after creating the texture
	SDL_DestroySurface(surface);

	return true;
}

void viper::Text::Draw(Renderer& renderer, int x, int y) {

	// get the texture width and height
	float width, height;
	bool success = SDL_GetTextureSize(m_texture, &width, &height);
	assert(success);

	// set the texture into the renderer at rect 
	SDL_FRect rect{ x, y, width, height };
	success = SDL_RenderTexture(renderer.m_renderer, m_texture, NULL, &rect);
	assert(success);

}

}