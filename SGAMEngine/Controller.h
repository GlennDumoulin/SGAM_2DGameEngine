#pragma once
#include <memory>

namespace sgam
{
	class Controller final
	{
	public:
		void Update();

		bool IsButtonDown(unsigned int button) const;
		bool IsButtonUp(unsigned int button) const;
		bool IsButtonPressed(unsigned int button) const;

		bool IsDisconnected() const;

		unsigned int GetIndex() const;

		explicit Controller(unsigned int controllerIdx);
		~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImpl{};
	};
}
