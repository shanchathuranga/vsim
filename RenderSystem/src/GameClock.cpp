#include "GameClock.h"
#include "SDL.h"

namespace smoke
{
	GameClock::GameClock()
	{
		m_time = SDL_GetTicks();
	}

	void GameClock::start()
	{
		m_time = SDL_GetTicks();
	}

	float GameClock::tick()
	{
		float timeStep = (SDL_GetTicks() - m_time) * 0.001f;
		m_time = SDL_GetTicks();
		return timeStep;
	}
}
