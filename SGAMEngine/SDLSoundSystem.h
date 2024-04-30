#pragma once
#include <memory>

#include "SoundSystem.h"

namespace sgam
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		explicit SDLSoundSystem();
		~SDLSoundSystem();
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		virtual void Play(uint32_t id, float volume) override;
		virtual void Load(const std::string& filepath) override;
		virtual void LoadAndPlay(const std::string& filepath, float volume) override;

	private:
		class SDLSoundSystemImpl;
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl{};
	};
}
