#pragma once
#include <vector>
#include <chrono>

#include "RenderableComponent.h"

struct Transform3D
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D final
{
public:
	Transform3D local{};
	int id{};
};

class GameObject3DAlt final
{
public:
	Transform3D* local{};
	int id{};
};

namespace sgam
{
	class ImGuiExercises final : public RenderableComponent
	{
	public:
		virtual void RenderGUI() override;

		explicit ImGuiExercises(GameObject* pOwner) : RenderableComponent(pOwner) {}
		~ImGuiExercises() = default;
		ImGuiExercises(const ImGuiExercises& other) = delete;
		ImGuiExercises(ImGuiExercises&& other) = delete;
		ImGuiExercises& operator=(const ImGuiExercises& other) = delete;
		ImGuiExercises& operator=(ImGuiExercises&& other) = delete;

	private:
		void RenderEx1();
		void RenderEx2();

		void TrashInts();
		void TrashGOs();
		void TrashGOAs();

		float CalculateAverage(std::vector<int>& results);

		const int m_ArraySize{ 1 << 26 };
		const int m_MinSamples{ 10 };

		int m_NrSamplesEx1{ 10 };
		int m_NrSamplesEx2{ 10 };

		bool m_IsTrashingInts{ false };
		bool m_IsTrashingGOs{ false };
		bool m_IsTrashingGOAs{ false };

		std::vector<float> m_IntResults{};
		std::vector<float> m_GOResults{};
		std::vector<float> m_GOAResults{};
	};
}
