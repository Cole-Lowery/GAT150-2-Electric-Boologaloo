
#include "AudioSystem.h"
#include "AudioClip.h"


namespace viper {
	/// <summary>
	/// Checks if an FMOD operation was successful and prints an error message if it was not.
	/// </summary>
	/// <param name="result">The FMOD_RESULT value returned by an FMOD function call.</param>
	/// <returns>true if the result indicates success (FMOD_OK); false otherwise, after printing the error message.</returns>
	bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			Logger::Error("FMOD Error: {}", FMOD_ErrorString(result));
			
			return false;
		}
		return true;
	}


	/// <summary>
	/// Initializes the audio system using FMOD.
	/// </summary>
	/// <returns>True if the audio system was successfully initialized; otherwise, false.</returns>
	bool AudioSystem::Inititalize() {
		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if (!CheckFMODResult(result)) return false;

		void* extradriverdata = nullptr;
		result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) return false;

		return true;
	}

	/// <summary>
	/// Shuts down the audio system and releases associated resources.
	/// </summary>
	void AudioSystem::Shutdown() {
		CheckFMODResult(m_system->release());
	}

	/// <summary>
	/// Updates the audio system state by processing pending audio operations.
	/// </summary>
	void AudioSystem::Update() {
		CheckFMODResult(m_system->update());
	}

	/// <summary>
	/// Attempts to add a new sound to the audio system from a file, using a specified or default name.
	/// </summary>
	/// <param name="fileName">The path to the audio file to load.</param>
	/// <param name="name">An optional name to associate with the sound. If empty, the file name is used as the key.</param>
	/// <returns>True if the sound was successfully added; false if the name already exists or if loading the sound failed.</returns>
	bool AudioSystem::AddSound(const std::string& fileName, const std::string& name) {


		std::string key = (name.empty() ? fileName : name);

		//convert to lowercase
		key = toLower(key);

		//check if key exists in sounds map
		if (m_sounds.find(key) != m_sounds.end()) {
			Logger::Error("Audio System : name already exists {}", key);
			
			return false;
		}
		FMOD::Sound* sound = nullptr;

		//create sound from key
		FMOD_RESULT result = m_system -> createSound(fileName.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!CheckFMODResult(result)) return false;

		//insert sound into map
		m_sounds[key] = sound;
		//audio->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &sound);
		return true;
	}

	bool AudioSystem::AddBackGroundMusic(const std::string& fileName, const std::string& name) {
		std::string key = (name.empty() ? fileName : name);

		//convert to lowercase
		key = toLower(key);

		//check if key exists in sounds map
		if (m_sounds.find(key) != m_sounds.end()) {
			Logger::Error("Audio System : name already exists {}", key);
			
			return false;
		}
		FMOD::Sound* sound = nullptr;

		//create sound from key
		FMOD_RESULT result = m_system->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
		if (!CheckFMODResult(result)) return false;

		//insert sound into map
		m_sounds[key] = sound;
		//audio->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &sound);
		return true;
	}

	bool AudioSystem::PlaySound(const std::string& name) {

		//audio->playSound(sounds[2], 0, false, nullptr);
		std::string key = name;

		//convert to lowercase
		for (char& c : key) {
			c = std::tolower(c);
		}

		// check if sound exists in sounds map
		if (m_sounds.find(key) == m_sounds.end()) {
			Logger::Error("Audio System : name already exists {}", key);
			
			return false;
		}

		FMOD::Channel* channel = nullptr;

		//play cound from key
		//FMOD_RESULT result = m_system->playSound(m_sounds[key], 0, false, nullptr);

		m_channels[key] = channel;
		
		return true;
	}
	bool AudioSystem::PlaySound(AudioClip& audioClip) {
		//FMOD_RESULT result = m_system->playSound(audioClip.m_sound, 0, false, nullptr);
		//if (!CheckFMODResult(result)) return false;
		return true;
	}
	bool AudioSystem::StopSound() {

		FMOD::ChannelGroup* masterGroup = nullptr;
		if (m_system->getMasterChannelGroup(&masterGroup) == FMOD_OK && masterGroup) {
			masterGroup->stop();
		}
		return true;
	}
	
}