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

		m_Window = Window(WindowProperties(1280, 720, 0, 0, m_ProjectName));
		float viewportWidth = m_Window.GetWidth() * viewportSizeAdjust;
		float viewportHeight = m_Window.GetHeight() * viewportSizeAdjust;
		m_ViewportProps = WindowProperties(viewportWidth, viewportHeight, m_Window.GetWidth() - viewportWidth, m_Window.GetHeight() - viewportHeight, "Viewport");

		m_Renderer = new Renderer();
		m_EngineUI = new EngineUI();
	}

	Project::~Project()
	{
		for (Node* node : m_Nodes)
		{
			node->OnDetach();
			delete node;
		}
	}

	void Project::PushNode(Node* node)
	{
		m_Nodes.emplace_back(node);
	}
	void Project::PopNode(Node* node)
	{
		auto it = std::find(m_Nodes.begin(), m_Nodes.end(), node);
		if (it != m_Nodes.end())
		{
			node->OnDetach();
			m_Nodes.erase(it);
		}
	}

	void Project::Run()
	{
		std::cout << "Current Project Path: " << std::filesystem::current_path() << std::endl;

		InitializeOpenGL();

		glfwSetKeyCallback(m_Window.GetNativeWindow(), keycallback_dispatch);
		glfwSetMouseButtonCallback(m_Window.GetNativeWindow(), mousebuttoncallback_dispatch);
		glfwSetCursorPosCallback(m_Window.GetNativeWindow(), mousecallback_dispatch);
		glfwSetScrollCallback(m_Window.GetNativeWindow(), scrollcallback_dispatch);
		glfwSetFramebufferSizeCallback(m_Window.GetNativeWindow(), framebuffersizecallback_dispatch);

		m_EngineUI->OnAttach();
		m_Renderer->OnAttach();
		for (Node* node : m_Nodes)
			node->OnAttach();

		while (m_EngineRunning)
		{
			float currentFrameTime = static_cast<float>(glfwGetTime());
			deltaTime = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;

			m_Renderer->OnUpdate();
			for (Node* node : m_Nodes)
				node->OnUpdate();
			m_EngineUI->OnUpdate();

			glfwSwapBuffers(m_Window.GetNativeWindow());
			glfwPollEvents();

			if (glfwWindowShouldClose(m_Window.GetNativeWindow()))
				m_EngineRunning = false;
		}

		for (Node* node : m_Nodes)
			node->OnDetach();
		m_Renderer->OnDetach();
		m_EngineUI->OnDetach();
		glfwTerminate();
	}

	void Project::keycallback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			KeyPressedInput input(keycode);

			m_Renderer->OnInput(input);
			m_EngineUI->OnInput(input);
			for (Node* node : m_Nodes)
				node->OnInput(input);
		}
		else if (action == GLFW_RELEASE)
		{
			KeyReleasedInput input(keycode);

			m_Renderer->OnInput(input);
			m_EngineUI->OnInput(input);
			for (Node* node : m_Nodes)
				node->OnInput(input);
		}
	}

	void Project::mousebuttoncallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			MouseButtonPressedInput input(button);

			m_Renderer->OnInput(input);
			m_EngineUI->OnInput(input);
			for (Node* node : m_Nodes)
				node->OnInput(input);
		}
		else if (action == GLFW_RELEASE)
		{
			MouseButtonReleasedInput input(button);

			m_Renderer->OnInput(input);
			m_EngineUI->OnInput(input);
			for (Node* node : m_Nodes)
				node->OnInput(input);
		}
	}

	void Project::mousecallback(GLFWwindow* window, double xposin, double yposin)
	{
		MouseMovedInput input(xposin, yposin);

		m_Renderer->OnInput(input);
		m_EngineUI->OnInput(input);
		for (Node* node : m_Nodes)
			node->OnInput(input);
	}

	void Project::scrollcallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		MouseScrolledInput input(xoffset, yoffset);

		m_Renderer->OnInput(input);
		m_EngineUI->OnInput(input);
		for (Node* node : m_Nodes)
			node->OnInput(input);
	}

	void Project::framebuffersizecallback(GLFWwindow* window, int width, int height)
	{
		m_Window.GetWidth() = width;
		m_Window.GetHeight() = height;
		float viewportWidth = m_Window.GetWidth() * viewportSizeAdjust;
		float viewportHeight = m_Window.GetHeight() * viewportSizeAdjust;
		m_ViewportProps.Width = viewportWidth;
		m_ViewportProps.Height = viewportHeight;
		m_ViewportProps.xOffset = m_Window.GetWidth() - viewportWidth;
		m_ViewportProps.yOffset = m_Window.GetHeight() - viewportHeight;
		glViewport(m_ViewportProps.xOffset, m_ViewportProps.yOffset, m_ViewportProps.Width, m_ViewportProps.Height);
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