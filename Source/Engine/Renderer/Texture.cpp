#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"

#include <SDL3_image/SDL_image.h>
#include <filesystem>



namespace viper {
Texture::~Texture() {
    // if texture exists, destroy texture
    if (m_texture) SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
}

bool Texture::Load(const std::string& filename, Renderer& renderer) {
    // load image onto surface
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        Logger::Error("Could not load image: ", filename);
        
        return false;
    }

    // create texture from surface, texture is a friend class of renderer
    m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
    // once texture is created, surface can be freed up
    SDL_DestroySurface(surface);
    if (m_texture == nullptr)
    {
        Logger::Error("Could not create texture: {}", filename);
        
        return false;
    }

    return true;
}

vec2 Texture::GetSize() {
    float w, h;
    SDL_GetTextureSize(m_texture, &w, &h);
    
    return vec2{ w, h };
}

}
