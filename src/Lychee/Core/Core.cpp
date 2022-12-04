/**
 * @file Core.cpp
 * @author flexhaufen
 * @brief Core of the engine
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Core/Core.h"

// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {
    Core* Core::s_Instance = nullptr;

    Core::Core() {
        s_Instance = this;

        Lychee::Log::Init();
        LY_CORE_INFO("Lychee {0}", LY_VERSION_STR);
        LY_CORE_INFO("-----------------------------------------------");
        LY_CORE_INFO("Initializing Core");

        std::filesystem::current_path(LY_DEFAULT_PATH);
        LY_CORE_INFO("Running in: {0}",std::filesystem::current_path());


        #ifdef LY_PROFILE
            LY_CORE_WARN("Profiler is enabled and may use unnecessary recources");
        #endif
        LY_PROFILE_BEGIN_SESSION("Profile", "LycheeProfile.json");

        #ifdef LY_DEBUG
            LY_CORE_WARN("Running in DEBUG mode");
            m_Window = new Window(LY_WINDOW_NAME_DEBUG,
                                  LY_WINDOW_SIZE_X,
                                  LY_WINDOW_SIZE_Y);
        #else
            m_Window = new Window(LY_WINDOW_NAME,
                                  LY_WINDOW_SIZE_X,
                                  LY_WINDOW_SIZE_Y);
		#endif
        m_Window->SetEventCallback(LY_BIND_EVENT_FN(Core::OnEvent));


        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
    }

    Core::~Core() {
        LY_PROFILE_FUNCTION();

        // delet m_Window -> doesn't matter becose aplication will
        // terminate anyway
        Renderer::Shutdown();
	    LY_PROFILE_END_SESSION();
        LY_CORE_INFO("Core is going down for Shutdown NOW!");
    }

    void Core::Run() {
        LY_PROFILE_FUNCTION();

        while (m_isRunning) {
            f32 time = (f32)glfwGetTime();
            DeltaTime deltaTime = time - m_lastFrameTime;
            m_lastFrameTime = time;

            if (!m_isMinimized) {
                for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(deltaTime);
                }
               
                m_ImGuiLayer->Begin();
                
                for (Layer* layer : m_LayerStack) {
                    layer->OnImGuiRender();
                }
            
                m_ImGuiLayer->End();
            }
            m_Window->OnUpdate(deltaTime);
        }
        LY_CORE_WARN("Core stopped running");
    }

    void Core::Close() {
		m_isRunning = false;
	}

    // ** LAYERS **
    void Core::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Core::PushOverlay(Layer* layer){
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

    // ** EVENTS **
    void Core::OnEvent(Event& e) {
        LY_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(LY_BIND_EVENT_FN(Core::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(LY_BIND_EVENT_FN(Core::OnWindowResize));


        for (auto i = m_LayerStack.rbegin(); i != m_LayerStack.rend(); ++i) {
			if (e.m_isHandled) 
				break;
			(*i)->OnEvent(e);
		}
        #ifdef LY_LOG_EVENTS
            LY_CORE_TRACE(e);
        #endif
    }

    bool Core::OnWindowClose(WindowCloseEvent& e) {
        m_isRunning = false;
        return true;
    }

	bool Core::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_isMinimized = true;
			return true;
		}

        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		m_isMinimized = false;
		return false;
	}
}