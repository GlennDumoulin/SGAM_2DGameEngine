#include "ImGuiExercises.h"
#include <algorithm>
#include <numeric>

using namespace sgam;

void ImGuiExercises::RenderGUI()
{
	RenderEx1();
	RenderEx2();
}

void ImGuiExercises::RenderEx1()
{
	if (!ImGui::Begin("Exercise 1"))
	{
		ImGui::End();
		return;
	}

	if (ImGui::InputInt("# samples", &m_NrSamplesEx1))
	{
		if (m_NrSamplesEx1 < m_MinSamples) m_NrSamplesEx1 = m_MinSamples;
	}

	if (!m_IsTrashingInts)
	{
		if (ImGui::Button("Trash the cache"))
		{
			TrashInts();
		}
		if (!m_IntResults.empty())
		{
			if (ImPlot::BeginPlot("##IntPlot"))
			{
				ImPlot::SetNextLineStyle(ImVec4(1, 0.5, 0, 1));
				ImPlot::PlotLine("", m_IntResults.data(), static_cast<int>(m_IntResults.size()));
				ImPlot::EndPlot();
			}
		}
	}
	else
	{
		ImGui::Text("Wait for it...");
	}

	ImGui::End();
}

void ImGuiExercises::RenderEx2()
{
	if (!ImGui::Begin("Exercise 2"))
	{
		ImGui::End();
		return;
	}

	if (ImGui::InputInt("# samples", &m_NrSamplesEx2))
	{
		if (m_NrSamplesEx2 < m_MinSamples) m_NrSamplesEx2 = m_MinSamples;
	}

	if (!m_IsTrashingGOs)
	{
		if (ImGui::Button("Trash the cache with GameObject3D"))
		{
			TrashGOs();
		}
		if (!m_GOResults.empty())
		{
			if (ImPlot::BeginPlot("##GOPlot"))
			{
				ImPlot::SetNextLineStyle(ImVec4(0, 1, 0, 1));
				ImPlot::PlotLine("", m_GOResults.data(), static_cast<int>(m_GOResults.size()));
				ImPlot::EndPlot();
			}
		}
	}
	else
	{
		ImGui::Text("Wait for it...");
	}

	if (!m_IsTrashingGOAs)
	{
		if (ImGui::Button("Trash the cache with GameObject3DAlt"))
		{
			TrashGOAs();
		}
		if (!m_GOAResults.empty())
		{
			if (ImPlot::BeginPlot("##GOAPlot"))
			{
				ImPlot::SetNextLineStyle(ImVec4(1, 0.5, 0, 1));
				ImPlot::PlotLine("", m_GOAResults.data(), static_cast<int>(m_GOAResults.size()));
				ImPlot::EndPlot();
			}
		}
	}
	else
	{
		ImGui::Text("Wait for it...");
	}

	if (!m_GOResults.empty() && !m_GOAResults.empty())
	{
		ImGui::Text("Combined:");

		if (ImPlot::BeginPlot("##CombinedPlot"))
		{
			ImPlot::SetNextLineStyle(ImVec4(0, 1, 0, 1));
			ImPlot::PlotLine("", m_GOResults.data(), static_cast<int>(m_GOResults.size()));
			ImPlot::SetNextLineStyle(ImVec4(1, 0.5, 0, 1));
			ImPlot::PlotLine("", m_GOAResults.data(), static_cast<int>(m_GOAResults.size()));
			ImPlot::EndPlot();
		}
	}

	ImGui::End();
}

void ImGuiExercises::TrashInts()
{
	m_IsTrashingInts = true;
	
	// Reset the results
	m_IntResults.clear();

	// Prepare large buffer
	std::unique_ptr<std::vector<int>> intArray{ std::make_unique<std::vector<int>>() };
	intArray->resize(m_ArraySize);

	// Handle all step sizes
	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<int> sampleResults{};

		// Calculate durations
		for (int sampleIdx{ 0 }; sampleIdx < m_NrSamplesEx1; ++sampleIdx)
		{
			const auto startTime{ std::chrono::high_resolution_clock::now() };

			for (int i{ 0 }; i < m_ArraySize; i += stepsize)
			{
				intArray->at(i) += stepsize;
			}

			const auto endTime{ std::chrono::high_resolution_clock::now() };

			const auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() };
			sampleResults.push_back(static_cast<int>(duration));
		}

		// Calculate average
		m_IntResults.push_back(CalculateAverage(sampleResults));
	}

	m_IsTrashingInts = false;
}

void ImGuiExercises::TrashGOs()
{
	m_IsTrashingGOs = true;

	// Reset the results
	m_GOResults.clear();

	// Prepare large buffer
	std::unique_ptr<std::vector<GameObject3D>> goArray{ std::make_unique<std::vector<GameObject3D>>() };
	goArray->resize(m_ArraySize);

	// Handle all step sizes
	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<int> sampleResults{};

		// Calculate durations
		for (int sampleIdx{ 0 }; sampleIdx < m_NrSamplesEx2; ++sampleIdx)
		{
			const auto startTime{ std::chrono::high_resolution_clock::now() };

			for (int i{ 0 }; i < m_ArraySize; i += stepsize)
			{
				goArray->at(i).id += stepsize;
			}

			const auto endTime{ std::chrono::high_resolution_clock::now() };

			const auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() };
			sampleResults.push_back(static_cast<int>(duration));
		}

		// Calculate average
		m_GOResults.push_back(CalculateAverage(sampleResults));
	}

	m_IsTrashingGOs = false;
}

void ImGuiExercises::TrashGOAs()
{
	m_IsTrashingGOAs = true;

	// Reset the results
	m_GOAResults.clear();

	// Prepare large buffer
	std::unique_ptr<std::vector<GameObject3DAlt>> goArray{ std::make_unique<std::vector<GameObject3DAlt>>() };
	goArray->resize(m_ArraySize);

	// Handle all step sizes
	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<int> sampleResults{};

		// Calculate durations
		for (int sampleIdx{ 0 }; sampleIdx < m_NrSamplesEx2; ++sampleIdx)
		{
			const auto startTime{ std::chrono::high_resolution_clock::now() };

			for (int i{ 0 }; i < m_ArraySize; i += stepsize)
			{
				goArray->at(i).id += stepsize;
			}

			const auto endTime{ std::chrono::high_resolution_clock::now() };

			const auto duration{ std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() };
			sampleResults.push_back(static_cast<int>(duration));
		}

		// Calculate average
		m_GOAResults.push_back(CalculateAverage(sampleResults));
	}

	m_IsTrashingGOAs = false;
}

float ImGuiExercises::CalculateAverage(std::vector<int>& results)
{
	std::sort(results.begin(), results.end());

	const auto& beginIt{ results.begin() + 1 };
	const auto& endIt{ results.end() - 1 };

	const int sum{ std::accumulate(beginIt, endIt, 0) };

	const int avg{ sum / static_cast<int>(std::distance(beginIt, endIt)) };

	return static_cast<float>(avg);
}
