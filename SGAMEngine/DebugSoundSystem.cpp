#include <iostream>
#include <format>

#include "DebugSoundSystem.h"

using namespace sgam;

DebugSoundSystem::DebugSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem)
	: m_RealSS{ std::move(soundSystem) }
{
}

void DebugSoundSystem::Play(uint32_t id, float volume)
{
	std::cout << std::format("Playing {} at volume {}\n", id, volume);
	m_RealSS->Play(id, volume);
}

void DebugSoundSystem::Load(const std::string& filepath)
{
	std::cout << std::format("Loading {}\n", filepath);
	m_RealSS->Load(filepath);
}

void DebugSoundSystem::LoadAndPlay(const std::string& filepath, float volume)
{
	std::cout << std::format("Loading and playing {} at volume {}\n", filepath, volume);
	m_RealSS->LoadAndPlay(filepath, volume);
}
