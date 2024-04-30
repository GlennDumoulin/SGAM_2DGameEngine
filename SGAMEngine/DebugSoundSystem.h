#pragma once
#include <memory>

#include "SoundSystem.h"

namespace sgam
{
	class DebugSoundSystem final : public SoundSystem
	{
	public:
		explicit DebugSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem);
		~DebugSoundSystem() = default;
		DebugSoundSystem(const DebugSoundSystem& other) = delete;
		DebugSoundSystem(DebugSoundSystem&& other) = delete;
		DebugSoundSystem& operator=(const DebugSoundSystem& other) = delete;
		DebugSoundSystem& operator=(DebugSoundSystem&& other) = delete;

		virtual void Play(uint32_t id, float volume) override;
		virtual void Load(const std::string& filepath) override;
		virtual void LoadAndPlay(const std::string& filepath, float volume) override;

	private:
		std::unique_ptr<SoundSystem> m_RealSS{};
	};
}
