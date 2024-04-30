#include <SDL.h>
#include <SDL_mixer.h>
#include <sstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#include "SDLSoundSystem.h"
#include "CyclicBuffer.h"

namespace sgam
{
	class SDLSoundSystem::SDLSoundSystemImpl final
	{
	public:
		explicit SDLSoundSystemImpl()
		{
			// Initialize SDL_mixer
			if (SDL_Init(SDL_INIT_AUDIO) != 0)
			{
				std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
				return;
			}

			if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) != 0)
			{
				std::cout << "Failed to open audio device: " << Mix_GetError() << std::endl;
				return;
			}

			// Start the sound thread
			m_IsRunning = true;
			m_Thread = std::jthread(&SDLSoundSystemImpl::RunThread, this);
		}

		~SDLSoundSystemImpl()
		{
			// Stop the sound thread
			m_IsRunning = false;
			m_Condition.notify_one();
			m_Thread.join();

			// Release all the loaded sounds
			for (SDLSound& sound : m_Sounds)
			{
				Mix_FreeChunk(sound.pSound);
			}

			// Quit SDL_mixer
			Mix_Quit();
		}

		SDLSoundSystemImpl(const SDLSoundSystemImpl& other) = delete;
		SDLSoundSystemImpl(SDLSoundSystemImpl&& other) = delete;
		SDLSoundSystemImpl& operator=(const SDLSoundSystemImpl& other) = delete;
		SDLSoundSystemImpl& operator=(SDLSoundSystemImpl&& other) = delete;

		void Play(uint32_t id, float volume)
		{
			// Add play event to buffer
			{
				std::lock_guard lock{ m_Mutex };
				m_SoundEvents.Push(SoundEvent{ SoundEventType::play, id, "", volume });
			}

			// Notify sound thread
			m_Condition.notify_one();
		}

		void Load(std::string& filepath)
		{
			// Add load event to buffer
			{
				std::lock_guard lock{ m_Mutex };
				m_SoundEvents.Push(SoundEvent{ SoundEventType::load, UINT32_MAX, filepath, 0.f });
			}

			// Notify sound thread
			m_Condition.notify_one();
		}

		void LoadAndPlay(std::string& filepath, float volume)
		{
			// Add load_and_play event to buffer
			{
				std::lock_guard lock{ m_Mutex };
				m_SoundEvents.Push(SoundEvent{ SoundEventType::load_and_play, UINT32_MAX, filepath, volume });
			}

			// Notify sound thread
			m_Condition.notify_one();
		}

	private:
		enum class SoundEventType
		{
			play,
			load,
			load_and_play,
		};

		struct SoundEvent
		{
			SoundEventType type{};

			uint32_t id{};
			std::string filepath{};
			float volume{};
		};

		struct SDLSound
		{
			uint32_t id{};
			std::string filepath{};

			Mix_Chunk* pSound{};
		};

		void RunThread()
		{
			while (m_IsRunning)
			{
				// Make thread wait for a new event to be added
				{
					std::unique_lock lock{ m_Mutex };
					m_Condition.wait(lock);
				}

				// Handle sound events
				SoundEvent se{};
				while (!m_SoundEvents.IsEmpty())
				{
					// Get an event from the buffer
					{
						std::lock_guard lock{ m_Mutex };
						se = m_SoundEvents.Pop();
					}

					// Handle the event
					switch (se.type)
					{
					case SoundEventType::play:
					{
						// Check if the requested sound exists
						if (se.id >= static_cast<uint32_t>(m_Sounds.size()))
						{
							std::cout << "Requested id (" << se.id << ") does not exist!\n";
							break;
						}

						// Play the sound
						const SDLSound& sound{ m_Sounds.at(se.id) };
						PlayEvent(sound.pSound, se.volume);

						break;
					}
					case SoundEventType::load:
					{
						// Check if the requested sound was loaded already
						const auto& soundIt{ std::find_if(m_Sounds.begin(), m_Sounds.end(),
							[&](const SDLSound& sound) {
								return se.filepath == sound.filepath;
							})
						};

						// If so, do nothing
						if (soundIt != m_Sounds.end()) break;

						// Else load the sound
						LoadEvent(se.filepath);

						break;
					}
					case SoundEventType::load_and_play:
					{
						// Check if the requested sound was loaded already
						const auto& soundIt{ std::find_if(m_Sounds.begin(), m_Sounds.end(),
							[&](const SDLSound& sound) {
								return se.filepath == sound.filepath;
							})
						};

						if (soundIt == m_Sounds.end()) // If not, load the sound
						{
							LoadEvent(se.filepath);

							// Re-add the event in the buffer
							std::lock_guard lock{ m_Mutex };
							m_SoundEvents.Push(se);
						}
						else // Else play the sound
						{
							PlayEvent(soundIt->pSound, se.volume);
						}

						break;
					}
					}
				}
			}
		}

		void PlayEvent(Mix_Chunk* pSound, float volume)
		{
			// Get an available channel
			const int channel = Mix_GroupAvailable(-1);

			if (channel == -1)
			{
				std::cout << "Failed to find an open channel!\n";
				return;
			}

			// Set the channel's volume
			Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));

			// Play the sound
			Mix_PlayChannel(channel, pSound, 0);
		}

		void LoadEvent(const std::string& filepath)
		{
			// Get the complete path to the requested file
			std::stringstream path{};
			path << "../Data/" << filepath;

			// Load the sound file
			Mix_Chunk* pSound{ Mix_LoadWAV(path.str().c_str()) };

			// Check if the sound was loaded succesfully
			if (!pSound)
			{
				std::cout << "Failed to load sound file!\n";
				return;
			}

			// Store loaded sound
			const SDLSound sound{ static_cast<uint32_t>(m_Sounds.size()), filepath, pSound };
			m_Sounds.push_back(sound);
		}

		CyclicBuffer<SoundEvent> m_SoundEvents{ 16 };
		std::vector<SDLSound> m_Sounds{};

		std::jthread m_Thread{};
		std::mutex m_Mutex{};
		std::condition_variable m_Condition{};

		bool m_IsRunning{};
	};
}

using namespace sgam;

SDLSoundSystem::SDLSoundSystem()
	:m_pImpl{ std::make_unique<SDLSoundSystemImpl>() }
{
}

SDLSoundSystem::~SDLSoundSystem()
{
}

void SDLSoundSystem::Play(uint32_t id, float volume)
{
	m_pImpl->Play(id, volume);
}

void SDLSoundSystem::Load(std::string& filepath)
{
	m_pImpl->Load(filepath);
}

void SDLSoundSystem::LoadAndPlay(std::string& filepath, float volume)
{
	m_pImpl->LoadAndPlay(filepath, volume);
}