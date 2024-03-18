#include "Controller.h"

using namespace sgam;

void Controller::Update()
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

bool Controller::IsButtonDown(unsigned int button) const
{
	return m_PressedBtns & button;
}

bool Controller::IsButtonUp(unsigned int button) const
{
	return m_ReleasedBtns & button;
}

bool Controller::IsButtonPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}
