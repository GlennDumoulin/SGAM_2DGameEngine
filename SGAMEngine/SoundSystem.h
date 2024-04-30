#pragma once
#include <string>

namespace sgam
{
	class SoundSystem
	{
	public:
		explicit SoundSystem() = default;
		virtual ~SoundSystem() = default;
		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;

		virtual void Play(uint32_t id, float volume) = 0;
		virtual void Load(std::string& filepath) = 0;
		virtual void LoadAndPlay(std::string& filepath, float volume) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		explicit NullSoundSystem() = default;
		~NullSoundSystem() = default;
		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) = delete;

		virtual void Play(uint32_t, float) override {}
		virtual void Load(std::string&) override {}
		virtual void LoadAndPlay(std::string&, float) override {}
	};
}
