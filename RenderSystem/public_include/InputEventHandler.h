#ifndef _InputEventHandler_
#define _InputEventHandler_

#include "Definitions.h"
#include "IMouseListener.h"
#include "IKeyListener.h"
#include <vector>

namespace smoke
{
	class InputEventHandler
	{
	public:
		void addKeyListener(framework::IKeyListener* keyListener);
		void removeKeyListener(framework::IKeyListener* keyListener);
		void addMouseListener(framework::IMouseListener* mouseListener);
		void removeMouseListener(framework::IMouseListener* mouseListener);

	private:
		friend class RenderWindow;

		void injectKeyDown(framework::KeyCode key, framework::KeyModifier mod = framework::Mod_None);
		void injectKeyUp(framework::KeyCode key, framework::KeyModifier mod = framework::Mod_None);
		void injectMouseButtonDown(framework::MouseButton button, int x, int y);
		void injectMouseButtonUp(framework::MouseButton button, int x, int y);
		void injectMouseMotion(framework::MouseButton button, int x, int y, int xr, int yr);

		std::vector<framework::IKeyListener*> m_keyListeners;
		std::vector<framework::IMouseListener*> m_mouseListeners;
	};
}

#endif