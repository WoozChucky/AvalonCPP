#pragma once

#include "Avalon/Core/Input.h"

namespace Avalon {

	class WindowsInput : public Input 
	{

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) override;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual std::pair<F32, F32> GetMousePositionImpl() override;
		virtual F32 GetMouseXImpl() override;
		virtual F32 GetMouseYImpl() override;

	};

}