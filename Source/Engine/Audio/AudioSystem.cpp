#include "AudioSystem.h"
#include "AudioClip.h"

namespace viper {

    /// <summary>
    /// Checks if an FMOD operation was successful and logs an error message if it was not.
    /// </summary>
    /// <param name="result">The FMOD_RESULT value returned by an FMOD function call.</param>
    /// <returns>true if the FMOD operation was successful (FMOD_OK); false otherwise.</returns>
    bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
        if (result != FMOD_OK) {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }
        return true;
    }

    /// <summary>
    /// Initializes the audio system using FMOD.
    /// </summary>
    /// <returns>Returns true if the audio system was successfully initialized; otherwise, returns false.</returns>
    bool AudioSystem::Initialize() {
        FMOD_RESULT result = FMOD::System_Create(&m_system);
        if (!CheckFMODResult(result))return false;
        void* extradriverdata = nullptr;
        result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
        if (!CheckFMODResult(result))return false;
        return true;
    }

    void AudioSystem::Shutdown() {
        CheckFMODResult(m_system->release());
    }

    void AudioSystem::Update() {
        CheckFMODResult(m_system->update());
    }

    bool AudioSystem::AddSound(const char* filename, const std::string& name)
    {
        std::string key = name.empty() ? filename : name;
        key = tolower(key);
        if (m_sounds.find(key) != m_sounds.end()) {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }
        FMOD::Sound* sound = nullptr;
        FMOD_RESULT result = m_system->createSound(filename, FMOD_DEFAULT, 0, &sound);
        if (!CheckFMODResult(result)) return false;
        m_sounds[key] = sound;
        return true;
    }
    bool AudioSystem::PlaySound(const std::string& name)
    {
        std::string key = name;
        if (m_sounds.find(key) == m_sounds.end()) {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }
        FMOD_RESULT result = m_system->playSound(m_sounds[name], 0, false, nullptr);
        if (!CheckFMODResult(result)) return false;
        return true;

    }

    bool AudioSystem::PlaySound(AudioClip& audioClip)
    {
        FMOD_RESULT result = m_system->playSound(audioClip.m_sound, 0, false, nullptr);
        if (!CheckFMODResult(result)) return false;

        return true;
    }

}
