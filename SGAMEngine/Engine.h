#pragma once
#include <string>

namespace sgam
{
	class Engine
	{
	public:
		void Run();

		explicit Engine(const std::string& dataPath);
		~Engine();
		Engine(const Engine& other) = delete;
		Engine(Engine&& other) = delete;
		Engine& operator=(const Engine& other) = delete;
		Engine& operator=(Engine&& other) = delete;
	};
}
