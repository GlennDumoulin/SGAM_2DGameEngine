#pragma once
#include <vector>
#include <unordered_set>
#include <memory>

#include "Singleton.h"
#include "Controller.h"
#include "Command.h"

namespace sgam
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputType
		{
			ButtonDown,
			ButtonUp,
			ButtonPressed
		};

		enum class ControllerButton
		{
			DPAD_UP = 0x0001,
			DPAD_DOWN = 0x0002,
			DPAD_LEFT = 0x0004,
			DPAD_RIGHT = 0x0008,
			START = 0x0010,
			BACK = 0x0020,
			LEFT_SHOULDER = 0x0100,
			RIGHT_SHOULDER = 0x0200,
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000
		};

		bool ProcessInput();

		void BindControllerCommand(const unsigned int controllerIdx, const ControllerButton button, const InputType inputType, std::unique_ptr<Command> pCommand);
		void BindKeyboardCommand(const SDL_Scancode button, const InputType inputType, std::unique_ptr<Command> pCommand);
		void UnbindAll();

		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

	private:
		friend class Singleton<InputManager>;
		explicit InputManager() = default;

		struct ControllerCommand final
		{
			ControllerCommand(const unsigned int controllerIdx, const ControllerButton button, const InputType inputType, std::unique_ptr<Command> pCommand)
				: controllerIdx{ controllerIdx }, button{ button }, inputType{ inputType }, pCommand{ std::move(pCommand) }
			{}
			~ControllerCommand() = default;

			const unsigned int controllerIdx;

			ControllerButton button;
			InputType inputType;

			std::unique_ptr<Command> pCommand;
		};
		struct KeyboardCommand final
		{
			KeyboardCommand(const SDL_Scancode button, const InputType inputType, std::unique_ptr<Command> pCommand)
				: button{ button }, inputType{ inputType }, pCommand{ std::move(pCommand) }
			{}
			~KeyboardCommand() = default;

			SDL_Scancode button;
			InputType inputType;

			std::unique_ptr<Command> pCommand;
		};

		bool ProcessSDLInputs();

		void HandleCommands();

		Controller* GetController(const unsigned int controllerIdx) const;

		const unsigned int m_MaxControllers{ 4 };

		std::vector<std::unique_ptr<Controller>> m_pControllers{};

		std::unordered_set<SDL_Scancode> m_KeyboardDown{};
		std::unordered_set<SDL_Scancode> m_KeyboardUp{};
		std::unordered_set<SDL_Scancode> m_KeyboardPressed{};

		std::vector<std::unique_ptr<ControllerCommand>> m_pControllerCommands{};
		std::vector<std::unique_ptr<KeyboardCommand>> m_pKeyboardCommands{};
	};
}
