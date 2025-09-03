#pragma once
#include <string>
#include <fmod.hpp>
#include <map>

namespace viper {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool Inititalize();
		void Shutdown();

	void Update();

	bool AddSound(const std::string& fileName, const std::string& name = "");
	bool AddBackGroundMusic(const std::string& fileName, const std::string& name = "");
	bool PlaySound(const std::string& name = "");
	bool PlaySound(class AudioClip& audioClip);
	bool StopSound();
	

	private:
		friend class AudioClip;

		static bool CheckFMODResult(FMOD_RESULT result);

		FMOD::System* m_system = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;
		std::map<std::string, FMOD::Channel*> m_channels;
	};
}
