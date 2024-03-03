/**
 * @file RuntimeLayer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-03-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include <Lychee/Lychee.h>

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	class RuntimeLayer : public Layer {
	public:
		RuntimeLayer();
		~RuntimeLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(DeltaTime dt) override;
		void OnEvent(Event& e) override;
	private:


		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void OnMenuBarRender();

	private:

		// ** Members **
		Ref<Scene> m_ActiveScene;					// Current active Scene

		bool m_ViewportFocused = false;				// True if viewport is focused
		bool m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		// Panels
	};

}
