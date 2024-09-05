#pragma once

#include "Window.h"

namespace Nifty
{
	class Project
	{
	public:
		Project(std::string projectName = "New Project");
		virtual ~Project();

		void Run();

		// Getters
		static Project& Get() { return *s_Instance; }
		bool& GetProjectRunState() { return m_ProjectRunning; }
		bool& GetEngineRunState() { return m_EngineRunning; }
		std::string GetProjectName() const { return m_ProjectName; }

		// Callback functions
		/*void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mousebuttoncallback(GLFWwindow* window, int button, int action, int mods);
		void mousecallback(GLFWwindow* window, double xposin, double yposin);
		void scrollcallback(GLFWwindow* window, double xoffset, double yoffset);
		void framebuffersizecallback(GLFWwindow* window, int width, int height);

		static void keycallback_dispatch(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (s_Instance)
				s_Instance->keycallback(window, key, scancode, action, mods);
		}
		static void mousebuttoncallback_dispatch(GLFWwindow* window, int key, int action, int mods)
		{
			if (s_Instance)
				s_Instance->mousebuttoncallback(window, key, action, mods);
		}
		static void mousecallback_dispatch(GLFWwindow* window, double xposin, double yposin)
		{
			if (s_Instance)
				s_Instance->mousecallback(window, xposin, yposin);
		}
		static void scrollcallback_dispatch(GLFWwindow* window, double xoffset, double yoffset)
		{
			if (s_Instance)
				s_Instance->scrollcallback(window, xoffset, yoffset);
		}
		static void framebuffersizecallback_dispatch(GLFWwindow* window, int width, int height)
		{
			if (s_Instance)
				s_Instance->framebuffersizecallback(window, width, height);
		}*/

	private:
		void InitializeOpenGL();
		

	public:
		float deltaTime = 0.0f;

	private:
		Window m_Window;
		unsigned int m_AntiAliasingLevel = 4;
		bool m_EngineRunning = true;
		bool m_ProjectRunning = false;
		float lastFrameTime = 0.0f;

		std::string m_ProjectName;

		static Project* s_Instance;
	};
}