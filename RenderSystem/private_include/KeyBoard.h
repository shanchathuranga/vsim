#ifndef _KeyBoard_
#define _KeyBoard_

#include "IKeyBoard.h"
#include "IKeyListener.h"

namespace smoke
{
	class KeyBoard : public framework::IKeyBoard, public framework::IKeyListener
	{
	public:
		KeyBoard();
		bool isKeyDown( framework::KeyCode key ) const;
		bool isKeyUp( framework::KeyCode key ) const;
		void keyPressed( const framework::KeyEvent* evt );
		void keyReleased( const framework::KeyEvent* evt );

	private:
		bool m_keyStatus[framework::SK_KEY_COUNT];
	};
}

#endif