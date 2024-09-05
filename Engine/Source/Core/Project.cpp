#include "nfpch.h"
#include "Project.h"

#include "Utility/Log.h"

namespace Nifty
{
	Project* Project::s_Instance = nullptr;

	Project::Project(std::string projectName)
		: m_ProjectName(projectName)
	{
		s_Instance = this;

		m_Window = Window(1280, 720, 0, 0, m_ProjectName);
	}

	Project::~Project()
	{
	}

	void Project::Run()
	{
		std::cout << "Current Project Path: " << std::filesystem::current_path() << std::endl;

		InitializeOpenGL();

		/*glfwSetKeyCallback(m_Window.GetNativeWindow(), keycallback_dispatch);
		glfwSetMouseButtonCallback(m_Window.GetNativeWindow(), mousebuttoncallback_dispatch);
		glfwSetCursorPosCallback(m_Window.GetNativeWindow(), mousecallback_dispatch);
		glfwSetScrollCallback(m_Window.GetNativeWindow(), scrollcallback_dispatch);
		glfwSetFramebufferSizeCallback(m_Window.GetNativeWindow(), framebuffersizecallback_dispatch);*/

		while (m_EngineRunning)
		{
			float currentFrameTime = static_cast<float>(glfwGetTime());
			deltaTime = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;

			glfwSwapBuffers(m_Window.GetNativeWindow());
			glfwPollEvents();

			if (glfwWindowShouldClose(m_Window.GetNativeWindow()))
				m_EngineRunning = false;
		}

		glfwTerminate();
	}

	void Project::InitializeOpenGL()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		if (m_AntiAliasingLevel > 0)
			glfwWindowHint(GLFW_SAMPLES, m_AntiAliasingLevel);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		m_Window.SetNativeWindow(glfwCreateWindow(m_Window.GetWidth(), m_Window.GetHeight(), m_ProjectName.c_str(), NULL, NULL));

		if (m_Window.GetNativeWindow() == NULL)
		{
			Log::Error("Error creating GLFW window");
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_Window.GetNativeWindow());

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			Log::Error("Error Initializing GLAD");

		if (m_AntiAliasingLevel > 0)
			glEnable(GL_MULTISAMPLE); // enable antialiasing
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		//glEnable(GL_STENCIL_TEST);

		glViewport(m_Window.GetXOffset(), m_Window.GetYOffset(), m_Window.GetWidth(), m_Window.GetHeight());
	}
}