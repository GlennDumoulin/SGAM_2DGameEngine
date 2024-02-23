#pragma once
#include <string>
#include <functional>

namespace sgam
{
	class Engine
	{
	public:
		void Run(const std::function<void()>& load);

		explicit Engine(const std::string& dataPath);
		~Engine();
		Engine(const Engine& other) = delete;
		Engine(Engine&& other) = delete;
		Engine& operator=(const Engine& other) = delete;
		Engine& operator=(Engine&& other) = delete;
	};
}
