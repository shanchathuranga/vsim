#ifndef _IClock_
#define _IClock_

namespace framework
{
	class IClock
	{
	public:
		virtual ~IClock(){}
		virtual void start() = 0;
		virtual float tick() = 0;
	};
}

#endif