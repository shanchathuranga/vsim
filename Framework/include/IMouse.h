#ifndef _IMouse_
#define _IMouse_

namespace framework
{
	class IMouse
	{
	public:
		virtual ~IMouse(){}
		virtual void setMouseVisibility(bool visible) = 0;
		virtual void setMousePosition(int px, int py) = 0;
		virtual void getMousePosition(int& px, int& py) = 0;
	};
}

#endif