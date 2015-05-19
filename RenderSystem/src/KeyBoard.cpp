#include "KeyBoard.h"

namespace smoke
{
	bool KeyBoard::isKeyDown( framework::KeyCode key ) const
	{
		return m_keyStatus[key] == true;
	}

	bool KeyBoard::isKeyUp( framework::KeyCode key ) const
	{
		return m_keyStatus[key] == false;
	}

	void KeyBoard::keyPressed( const framework::KeyEvent* evt )
	{
		m_keyStatus[evt->getKeyCode()] = true;
	}

	void KeyBoard::keyReleased( const framework::KeyEvent* evt )
	{
		m_keyStatus[evt->getKeyCode()] = false;
	}

	KeyBoard::KeyBoard()
	{
		for (int i=0; i<framework::SK_KEY_COUNT; ++i)
		{
			m_keyStatus[i] = false;
		}
	}

}

