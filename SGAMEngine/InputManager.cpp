#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>

#include "InputManager.h"

using namespace sgam;

bool InputManager::ProcessInput()
{
	// Update the SDL inputs
	if (!ProcessSDLInputs()) return false;

	// Get the new state of all controllers 
	for (const auto& pController : m_pControllers)
	{
		pController->Update();
	}

	// Handle all binded commands
	HandleCommands();

	return true;
}

bool InputManager::ProcessSDLInputs()
{
	// Clear keyboard up & down keys
	m_KeyboardDown.clear();
	m_KeyboardUp.clear();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		// Early out if we quit the application
		if (e.type == SDL_QUIT) return false;

		// Check pressed keys
		switch (e.key.type)
		{
		case SDL_KEYDOWN:
		{
			m_KeyboardPressed.insert(e.key.keysym.scancode);
			m_KeyboardDown.insert(e.key.keysym.scancode);
			break;
		}
		case SDL_KEYUP:
		{
			m_KeyboardPressed.erase(e.key.keysym.scancode);
			m_KeyboardUp.insert(e.key.keysym.scancode);
			break;
		}
		default:
			break;
		}

		// Handle ImGui inputs
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void InputManager::HandleCommands()
{
	// Check controller commands to be executed
	for (const auto& pControllerCommand : m_pControllerCommands)
	{
		// Cache the targetted controller
		const auto& pController{ GetController(pControllerCommand->controllerIdx) };

		// Check if the targetted controller exists
		if (!pController) continue;

		// Check if the controller is disconnected
		if (pController->IsDisconnected()) continue;

		// Check if the command should be executed
		bool shouldExecute{ false };
		switch (pControllerCommand->inputType)
		{
		case InputType::ButtonDown:
		{
			shouldExecute = pController->IsButtonDown(static_cast<unsigned int>(pControllerCommand->button));
			break;
		}
		case InputType::ButtonUp:
		{
			shouldExecute = pController->IsButtonUp(static_cast<unsigned int>(pControllerCommand->button));
			break;
		}
		case InputType::ButtonPressed:
		{
			shouldExecute = pController->IsButtonPressed(static_cast<unsigned int>(pControllerCommand->button));
			break;
		}
		}

		if (shouldExecute) pControllerCommand->pCommand->Execute();
	}

	// Check keyboard commands to be executed
	for (const auto& pKeyboardCommand : m_pKeyboardCommands)
	{
		// Check if the command should be executed
		bool shouldExecute{ false };
		switch (pKeyboardCommand->inputType)
		{
		case InputType::ButtonDown:
		{
			shouldExecute = m_KeyboardDown.find(pKeyboardCommand->button) != m_KeyboardDown.end();
			break;
		}
		case InputType::ButtonUp:
		{
			shouldExecute = m_KeyboardUp.find(pKeyboardCommand->button) != m_KeyboardUp.end();
			break;
		}
		case InputType::ButtonPressed:
		{
			shouldExecute = m_KeyboardPressed.find(pKeyboardCommand->button) != m_KeyboardPressed.end();
			break;
		}
		}

		if (shouldExecute) pKeyboardCommand->pCommand->Execute();
	}
}

Controller* InputManager::GetController(const unsigned int controllerIdx) const
{
	for (const auto& pController : m_pControllers)
	{
		if (pController->GetIndex() == controllerIdx) return pController.get();
	}

	return nullptr;
}

void InputManager::BindControllerCommand(const unsigned int controllerIdx, const ControllerButton button, const InputType inputType, std::unique_ptr<Command> pCommand)
{
	// Check if the controllerIdx is valid
	if (controllerIdx >= m_MaxControllers) return;

	// Add a new controller for the index we are binding a command to, if we don't have one already
	if (GetController(controllerIdx) == nullptr)
	{
		m_pControllers.push_back(std::make_unique<Controller>(controllerIdx));
	}

	// Bind new command to list of controller commands
	m_pControllerCommands.push_back(std::make_unique<ControllerCommand>(
		controllerIdx, button, inputType, std::move(pCommand)
	));
}

void InputManager::BindKeyboardCommand(const SDL_Scancode button, const InputType inputType, std::unique_ptr<Command> pCommand)
{
	// Bind new command to list of keyboard commands
	m_pKeyboardCommands.push_back(std::make_unique<KeyboardCommand>(
		button, inputType, std::move(pCommand)
	));
}

void InputManager::UnbindAll()
{
	m_pControllerCommands.clear();
	m_pKeyboardCommands.clear();
}
