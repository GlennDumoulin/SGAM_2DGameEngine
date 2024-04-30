#include "ServiceLocator.h"

using namespace sgam;

std::unique_ptr<SoundSystem> ServiceLocator::m_SoundSystem{ nullptr };

SoundSystem& ServiceLocator::GetSoundSystem()
{
	// If there is no sound system, register the default one
	if (m_SoundSystem == nullptr)
	{
		auto nullSS{ std::make_unique<NullSoundSystem>() };
		RegisterSoundSystem(std::move(nullSS));
	}

	return *m_SoundSystem;
}

void ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem)
{
	m_SoundSystem = std::move(soundSystem);
}
