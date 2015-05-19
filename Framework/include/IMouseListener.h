#ifndef _IMouseListener_
#define _IMouseListener_

#include "Definitions.h"

namespace framework
{

	class MouseButtonEvent
	{
	public:
		MouseButtonEvent(MouseButton button, int x, int y)
		{
			m_button = button;
			m_x = x;
			m_y = y;
		}
		const MouseButton getButton() const	{ return m_button; }
		const int getX() const { return m_x; }
		const int getY() const { return m_y; }

	private:
		MouseButton m_button;
		int m_x;
		int m_y;
	};

	class MouseMoveEvent
	{
	public:
		MouseMoveEvent(MouseButton button, int x, int y, int xr, int yr)
		{
			m_button = button;
			m_x = x;
			m_y = y;
			m_xrel = xr;
			m_yrel = yr;
		}
		const bool isLeftButtonDown() const { return m_button == MouseButton_Left; }
		const bool isRightButtonDown() const { return m_button == MouseButton_Right; }
		const int getX() const { return m_x; }
		const int getY() const { return m_y; }
		const int getRelX() const { return m_xrel; }
		const int getRelY() const { return m_yrel; }
	private:
		MouseButton m_button;
		int m_x;
		int m_y;
		int m_xrel;
		int m_yrel;
	};

	class IMouseListener
	{
	public:
		virtual void mouseButtonPressed(const MouseButtonEvent* event) = 0;
		virtual void mouseButtonReleased(const MouseButtonEvent* event) = 0;
		virtual void mouseMoved(const MouseMoveEvent* event) = 0;
	};
}

#endif