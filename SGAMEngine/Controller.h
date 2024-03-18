#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

namespace sgam
{
	class Controller final
	{
	public:
		void Update();

		bool IsButtonDown(unsigned int button) const;
		bool IsButtonUp(unsigned int button) const;
		bool IsButtonPressed(unsigned int button) const;

		bool IsDisconnected() const { return m_IsDisconnected; }

		explicit Controller(unsigned int controllerIdx) : m_ControllerIdx{ controllerIdx } {}
		~Controller() = default;
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

	private:
		const unsigned int m_ControllerIdx{};
		bool m_IsDisconnected{ false };

		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};

		unsigned int m_PressedBtns{};
		unsigned int m_ReleasedBtns{};
	};
}
