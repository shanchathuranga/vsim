#ifndef _Mouse_
#define _Mouse_

#include "IMouse.h"

namespace smoke
{
	class Mouse : public framework::IMouse
	{
	public:
		void setMouseVisibility( bool visible );
		void setMousePosition( int px, int py );
		void getMousePosition( int& px, int& py );

	};
}

#endif