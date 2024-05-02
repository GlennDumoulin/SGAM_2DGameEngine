#pragma once
#include <memory>

#include "SoundSystem.h"

namespace sgam
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem);

	private:
		ServiceLocator() = default;
		~ServiceLocator() = default;
		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) = delete;
		ServiceLocator operator=(const ServiceLocator& other) = delete;
		ServiceLocator operator=(ServiceLocator&& other) = delete;

		static std::unique_ptr<SoundSystem> m_SoundSystem;
	};
}
