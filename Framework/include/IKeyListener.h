#ifndef _IKeyListener_
#define _IKeyListener_

#include "Definitions.h"

namespace framework
{
	class KeyEvent
	{
	public:

		KeyEvent(KeyCode code, KeyModifier mod)
		{
			m_code = code;
			m_mod = mod;
		}

		const KeyCode getKeyCode() const
		{
			return m_code;
		}
		const KeyModifier getKeyModifier() const
		{
			return m_mod;
		}

	private:
		KeyCode m_code;
		KeyModifier m_mod;
	};

	class IKeyListener
	{
	public:
		virtual void keyPressed(const KeyEvent* evt) = 0;
		virtual void keyReleased(const KeyEvent* evt) = 0;
	};

}

#endif