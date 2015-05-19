#include "InputEventHandler.h"

namespace smoke
{

	void InputEventHandler::addKeyListener( framework::IKeyListener* keyListener )
	{
		m_keyListeners.push_back( keyListener );
	}

	void InputEventHandler::removeKeyListener( framework::IKeyListener* keyListener )
	{
		std::vector<framework::IKeyListener*>::iterator it = m_keyListeners.end();
		for (std::vector<framework::IKeyListener*>::iterator sit = m_keyListeners.begin(), eit = m_keyListeners.end(); sit != eit; ++sit)
		{
			framework::IKeyListener* currentKeyListener = *sit;
			if (currentKeyListener == keyListener)
			{
				it = sit;
				break;
			}
		}
		if (it != m_keyListeners.end())
		{
			m_keyListeners.erase(it);
		}
	}

	void InputEventHandler::injectKeyDown( framework::KeyCode key, framework::KeyModifier mod )
	{
		framework::KeyEvent* ke = new framework::KeyEvent(key, mod);
		for (std::vector<framework::IKeyListener*>::iterator sit = m_keyListeners.begin(), eit = m_keyListeners.end(); sit != eit; ++sit)
		{
			framework::IKeyListener* currentKeyListener = *sit;
			if (currentKeyListener)
			{
				currentKeyListener->keyPressed(ke);
			}
		}
		delete ke;
	}

	void InputEventHandler::injectKeyUp( framework::KeyCode key, framework::KeyModifier mod )
	{
		framework::KeyEvent* ke = new framework::KeyEvent(key, mod);
		for (std::vector<framework::IKeyListener*>::iterator sit = m_keyListeners.begin(), eit = m_keyListeners.end(); sit != eit; ++sit)
		{
			framework::IKeyListener* currentKeyListener = *sit;
			if (currentKeyListener)
			{
				currentKeyListener->keyReleased(ke);
			}
		}
		delete ke;
	}

	void InputEventHandler::addMouseListener( framework::IMouseListener* mouseListener )
	{
		m_mouseListeners.push_back( mouseListener );
	}

	void InputEventHandler::removeMouseListener( framework::IMouseListener* mouseListener )
	{
		std::vector<framework::IMouseListener*>::iterator it = m_mouseListeners.end();
		for (std::vector<framework::IMouseListener*>::iterator sit = m_mouseListeners.begin(), eit = m_mouseListeners.end(); sit != eit; ++sit)
		{
			framework::IMouseListener* currentMouseListener = *sit;
			if (currentMouseListener == mouseListener)
			{
				it = sit;
				break;
			}
		}
		if (it != m_mouseListeners.end())
		{
			m_mouseListeners.erase(it);
		}
	}

	void InputEventHandler::injectMouseButtonDown( framework::MouseButton button, int x, int y )
	{
		framework::MouseButtonEvent* me = new framework::MouseButtonEvent(button, x, y);
		for (std::vector<framework::IMouseListener*>::iterator sit = m_mouseListeners.begin(), eit = m_mouseListeners.end(); sit != eit; ++sit)
		{
			framework::IMouseListener* currentMouseListener = *sit;
			if (currentMouseListener)
			{
				currentMouseListener->mouseButtonPressed(me);
			}
		}
		delete me;
	}

	void InputEventHandler::injectMouseButtonUp( framework::MouseButton button, int x, int y )
	{
		framework::MouseButtonEvent* me = new framework::MouseButtonEvent(button, x, y);
		for (std::vector<framework::IMouseListener*>::iterator sit = m_mouseListeners.begin(), eit = m_mouseListeners.end(); sit != eit; ++sit)
		{
			framework::IMouseListener* currentMouseListener = *sit;
			if (currentMouseListener)
			{
				currentMouseListener->mouseButtonReleased(me);
			}
		}
		delete me;
	}

	void InputEventHandler::injectMouseMotion( framework::MouseButton button, int x, int y, int xr, int yr )
	{
		framework::MouseMoveEvent* mme = new framework::MouseMoveEvent(button, x, y, xr, yr);
		for (std::vector<framework::IMouseListener*>::iterator sit = m_mouseListeners.begin(), eit = m_mouseListeners.end(); sit != eit; ++sit)
		{
			framework::IMouseListener* currentMouseListener = *sit;
			if (currentMouseListener)
			{
				currentMouseListener->mouseMoved(mme);
			}
		}
		delete mme;
	}

}