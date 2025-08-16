#include "Audio/AudioClip.h"
#include "AudioSource.h"
#include "Engine.h"

namespace viper {
	void AudioSource::Update(float dt) {
		//
	}
	void AudioSource::Play() {
		auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());
		if (audioClip) {
			GetEngine().GetAudio().PlaySound(*audioClip);
		}
	}
}