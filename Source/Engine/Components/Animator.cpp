#include "Animator.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/TextureAnimation.h"
#include "Engine.h"
namespace viper {
	FACTORY_REGISTER(Animator)
		void Animator::Start() {
		// cache off sprite renderer component, using sprite renderer to draw
		m_spriteRenderer = owner->GetComponent<SpriteRenderer>();
		if (!m_spriteRenderer) {
			Logger::Error("Animator misshing sprite renderer.");
		}
		// get texture animations from texture animation names
		for (auto& animation : m_animations) {
			animation.second.textureAnimation = Resources().Get<TextureAnimation>(animation.second.textureAnimationName, GetEngine().GetRenderer());
			if (!animation.second.textureAnimation) {
				Logger::Warning("Could not load Animator texture animation {}", animation.second.textureAnimationName)
					;
			}
			else {
				Logger::Info("Animator animation {}, texture {} loaded", animation.first, animation.second.textureAnimationName);
			}
		}
		// set initial animation, use first map entry
		auto it = m_animations.begin();
		std::string name = it->first;
		Play(name);
	}
	void Animator::Update(float dt) {
		if (m_paused || !m_currentAnimation.textureAnimation) return;
		// update frame timer
		m_frameTimer -= dt * speedMultiplier;
		if (m_frameTimer <= 0) {
			m_frameTimer = 1.0f / m_currentAnimation.textureAnimation->GetFPS();
			frame++;
			// check if animation is complete, loop or stop on last frame
			if (frame >= m_currentAnimation.textureAnimation->GetTotalFrames()) {
				if (m_currentAnimation.textureAnimation->IsLooping()) {
					frame = 0;
				}
				else {
					frame = m_currentAnimation.textureAnimation->GetTotalFrames() - 1;
				}
			}
			// set texture rect from animation
			if (m_spriteRenderer) {
				m_spriteRenderer->textureRect = m_currentAnimation.textureAnimation->GetFrameRect(frame);
			}
		}
	}
	void Animator::Play(const std::string& name, bool resetFrame) {
		// don't start animation if already current
		if (equalsIgnoreCase(name, m_currentAnimationName)) return;
		// check animation exists
		auto it = m_animations.find(toLower(name));
		if (it == m_animations.end()) {
			Logger::Error("Animation does not exist in animation {}", name);
			return;
		}
		// set the current animation
		m_currentAnimationName = name;
		m_currentAnimation = it->second;
		if (resetFrame) frame = 0;
		m_frameTimer = 1.0f / m_currentAnimation.textureAnimation->GetFPS();
		// set sprite renderer texture
		if (m_spriteRenderer) {
			m_spriteRenderer->texture = m_currentAnimation.textureAnimation->GetTexture();
			m_spriteRenderer->textureRect = m_currentAnimation.textureAnimation->GetFrameRect(frame);
		}
	}
	void Animator::Read(const json::value_t& value) {
		Object::Read(value);
		JSON_READ(value, frame);
		if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray()) {
			for (auto& animatorValue : JSON_GET(value, animations).GetArray()) {
				std::string name;
				std::string textureAnimationName;
				JSON_READ(animatorValue, name);
				JSON_READ_NAME(animatorValue, "texture_animation", textureAnimationName);
				TextureAnimInfo textureAnimInfo;
				textureAnimInfo.textureAnimationName = textureAnimationName;
				m_animations[toLower(name)] = textureAnimInfo;
			}
		}
	}
}