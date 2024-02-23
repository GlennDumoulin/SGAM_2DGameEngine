#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <thread>
#include <iostream>

#include "Engine.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"

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
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = nullptr;
	SDL_Quit();
}

void sgam::Engine::Run(const std::function<void()>& load)
{
	load();

	// Get the Singleton instances
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = Time::GetInstance();

	// Initialize gameloop variables
	bool doContinue = true;
	float unhandledTime = 0.0f;
	int nrOfSubsteps = 0;

	// Handle the gameloop
	while (doContinue)
	{
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

		sceneManager.Update();
		sceneManager.LateUpdate();
		
		renderer.Render();

		// Sleep to not exceed the desired fps
		std::cout << static_cast<int>(1.0f / time.Delta()) << "\n";
		std::this_thread::sleep_for(time.SleepTime());
	}
}
