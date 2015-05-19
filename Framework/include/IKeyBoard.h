#ifndef _IKeyBoard_
#define _IKeyBoard_

#include "Definitions.h"

namespace framework
{
	class IKeyBoard
	{
	public:
		virtual ~IKeyBoard(){}
		virtual bool isKeyDown(KeyCode key) const = 0;
		virtual bool isKeyUp(KeyCode key) const = 0;
	};
}

#endif