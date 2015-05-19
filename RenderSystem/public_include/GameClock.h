#ifndef _GameClock_
#define _GameClock_

#include "IClock.h"

namespace smoke
{
	class GameClock : public framework::IClock
	{
	public:
		GameClock();

		void start();
		
		float tick();
				
	private:
		unsigned int m_time;

	};
}

#endif