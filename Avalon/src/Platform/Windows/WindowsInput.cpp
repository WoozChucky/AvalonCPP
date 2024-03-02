#include "avpch.h"
#include "Avalon/Core/Input.h"

#include <GLFW/glfw3.h>

#include "Avalon/Core/Application.h"

namespace Avalon {

	bool Input::IsKeyPressed(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<U32>(keycode));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<U32>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (F32)xpos, (F32)ypos };
	}

	F32 Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	F32 Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

}