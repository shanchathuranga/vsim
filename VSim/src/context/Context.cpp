#include "context/Context.h"
#include "GameClock.h"

namespace vsim
{
	// Impl start
	
	struct Context::Impl
	{
		fire::EntitySystem m_entitySystem;
		heat::PhysicsSystem m_physicsSystem;
		smoke::RenderSystem m_renderSystem;
		smoke::GameClock m_gameClock;
	};

	// Impl end

	fire::EntitySystem& Context::getEntitySystem()
	{
		return m_impl->m_entitySystem;
	}

	heat::PhysicsSystem& Context::getPhysicsSystem()
	{
		return m_impl->m_physicsSystem;
	}

	smoke::RenderSystem& Context::getRenderSystem()
	{
		return m_impl->m_renderSystem;
	}

	framework::IClock& Context::getClock()
	{
		return m_impl->m_gameClock;
	}

	Context::~Context()
	{
		delete m_impl;
	}

	Context::Context()
	{
		m_impl = new Impl;
		m_impl->m_renderSystem.initialize();
	}

	Context::Context( const Context& )
	{
		
	}

	Context& getContext()
	{
		static Context ctx;
		return ctx;
	}

}