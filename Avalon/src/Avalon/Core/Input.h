#pragma once

#include "Avalon/Core/Base.h"
#include "Avalon/Core/KeyCodes.h"
#include "Avalon/Core/MouseCodes.h"

namespace Avalon {

	class Input {
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<F32, F32> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static F32 GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static F32 GetMouseY() { return s_Instance->GetMouseYImpl(); }

		static Scope<Input> Create();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<F32, F32> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Scope<Input> s_Instance;
	};

}