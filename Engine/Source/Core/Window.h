#pragma once

namespace Nifty
{
	class Window
	{
	public:
		Window(unsigned int width = 1280, unsigned int height = 720, unsigned int xoffset = 0, unsigned int yoffset = 0, std::string title = "New Project")
			: m_Width(width), m_Height(height), m_xOffset(xoffset), m_yOffset(yoffset), m_Title(title)
		{

		}
		~Window() = default;

		void SetNativeWindow(GLFWwindow* window) { m_Window = window; }

		// Getters
		GLFWwindow* GetNativeWindow() { return m_Window; }
		unsigned int& GetWidth() { return m_Width; }
		unsigned int& GetHeight() { return m_Height; }
		unsigned int& GetXOffset() { return m_xOffset; }
		unsigned int& GetYOffset() { return m_yOffset; }
		std::string& GetTitle() { return m_Title; }
		
		// VSync
		void SetVSync(bool enabled) { m_IsVSync = enabled; }
		bool IsVSync() const { return m_IsVSync; }

	private:
		GLFWwindow* m_Window;
		bool m_IsVSync = false;

		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_xOffset;
		unsigned int m_yOffset;
		std::string m_Title;

	};
}