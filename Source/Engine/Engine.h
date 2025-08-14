#pragma once
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Resources/ResourceManager.h"
#include <memory>

namespace viper {

	class Engine : public Singleton<Engine> {
	public:
		bool Initialize();
		void Shutdown();

		void Update();
		void Draw();

		Renderer& GetRenderer() { return *m_renderer; }
		InputSystem& GetInput() { return *m_input; }
		AudioSystem& GetAudio() { return *m_audio; }
		ParticleSystem& GetParticleSystem() { return *m_particleSystem; }

		Time& GetTime() { return m_time; }

	private:
		friend class Singleton<Engine>;
		Engine() = default;

	private:
		Time m_time;

		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<InputSystem> m_input;
		std::unique_ptr<AudioSystem> m_audio;
		std::unique_ptr<ParticleSystem> m_particleSystem;
	};

	inline Engine& GetEngine() { return Engine::Instance(); }
}