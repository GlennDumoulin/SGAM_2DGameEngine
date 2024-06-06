#pragma once
#include <string>

namespace sgam
{
	class Engine
	{
	public:
		void Run();

		explicit Engine(const std::string& dataPath, int windowWidth, int windowHeight);
		~Engine();
		Engine(const Engine& other) = delete;
		Engine(Engine&& other) = delete;
		Engine& operator=(const Engine& other) = delete;
		Engine& operator=(Engine&& other) = delete;
	};
}
