#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "Controller.h"

namespace sgam
{
	class Controller::ControllerImpl final
	{
	public:
		void Update()
		{
			// Update previous & current state
			m_PreviousState = m_CurrentState;
			if (XInputGetState(m_ControllerIdx, &m_CurrentState) == ERROR_DEVICE_NOT_CONNECTED)
			{
				m_IsDisconnected = true;
				return;
			}
			m_IsDisconnected = false;

			// Get the pressed & released buttons this frame
			auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
			m_PressedBtns = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_ReleasedBtns = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
		}

		bool IsButtonDown(unsigned int button) const
		{
			return m_PressedBtns & button;
		}
		bool IsButtonUp(unsigned int button) const
		{
			return m_ReleasedBtns & button;
		}
		bool IsButtonPressed(unsigned int button) const
		{
			return m_CurrentState.Gamepad.wButtons & button;
		}

		bool IsDisconnected() const { return m_IsDisconnected; }

		unsigned int GetIndex() const { return m_ControllerIdx; }

		explicit ControllerImpl(unsigned int controllerIdx) : m_ControllerIdx{ controllerIdx } {}
		~ControllerImpl() = default;
		ControllerImpl(const ControllerImpl& other) = delete;
		ControllerImpl(ControllerImpl&& other) = delete;
		ControllerImpl& operator=(const ControllerImpl& other) = delete;
		ControllerImpl& operator=(ControllerImpl&& other) = delete;

	private:
		const unsigned int m_ControllerIdx{};
		bool m_IsDisconnected{ false };

		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};

		unsigned int m_PressedBtns{};
		unsigned int m_ReleasedBtns{};
	};
}


using namespace sgam;

Controller::Controller(unsigned int controllerIdx)
	: m_pImpl{ std::make_unique<ControllerImpl>(controllerIdx) }
{
}

Controller::~Controller()
{
}

void Controller::Update()
{
	m_pImpl->Update();
}

bool Controller::IsButtonDown(unsigned int button) const
{
	return m_pImpl->IsButtonDown(button);
}

bool Controller::IsButtonUp(unsigned int button) const
{
	return m_pImpl->IsButtonUp(button);
}

bool Controller::IsButtonPressed(unsigned int button) const
{
	return m_pImpl->IsButtonPressed(button);
}

bool Controller::IsDisconnected() const
{
	return m_pImpl->IsDisconnected();
}

unsigned int Controller::GetIndex() const
{
	return m_pImpl->GetIndex();
}
