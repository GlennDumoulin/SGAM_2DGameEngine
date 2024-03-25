#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <thread>
#include <iostream>
#include <steam_api.h>

#include "Engine.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"
#include "SteamAchievements.h"
#include "Achievement.h"

SDL_Window* g_pWindow{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

sgam::Engine::Engine(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_pWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_pWindow == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	// Initialize Singletons
	Renderer::GetInstance().Init(g_pWindow);
	ResourceManager::GetInstance().Init(dataPath);
	Time::GetInstance().Init();
}

sgam::Engine::~Engine()
{
	InputManager::GetInstance().UnbindAll();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = nullptr;
	SDL_Quit();
}

void sgam::Engine::Run(const std::function<void()>& load)
{
	// Initialize Steam api
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n";
		return;
	}
	else
		std::cout << "Successfully initialized steam.\n";

	load();

	// Get the Singleton instances
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = Time::GetInstance();

	// Initialize Steam
	const std::vector<Achievement_t> achievements
	{
		Achievement_t{ static_cast<int>(SteamAchievements::Achievement::ACH_WIN_ONE_GAME), "Winner" }
	};
	SteamAchievements::GetInstance().Init(achievements, true);

	// Initialize gameloop variables
	bool doContinue = true;
	float unhandledTime = 0.0f;
	int nrOfSubsteps = 0;

	// Handle the gameloop
	while (doContinue)
	{
		// Call Steam api
		SteamAPI_RunCallbacks();

		// Update the Time and reset the nrOfSubsteps
		time.Update();
		unhandledTime += time.Delta();
		nrOfSubsteps = 0;

		doContinue = input.ProcessInput();

		// Check if we still need to catch up with fixed updates and haven't handled to many this frame
		while (unhandledTime >= time.FixedTimeStep() && nrOfSubsteps < time.MaxSubsteps())
		{
			sceneManager.FixedUpdate();

			unhandledTime -= time.FixedTimeStep();
			++nrOfSubsteps;
		}

		// Always handle exactly one update and late update
		sceneManager.Update();
		sceneManager.LateUpdate();

		// Handle cleaning up GameObjects and Components that are marked to be destroyed
		sceneManager.Cleanup();
		
		// Handle rendering
		renderer.Render();

		// Sleep to not exceed the desired fps
		std::this_thread::sleep_for(time.SleepTime());
	}

	// Stop Steam api
	SteamAPI_Shutdown();
}
