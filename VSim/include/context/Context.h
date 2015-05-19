#ifndef _Context_
#define _Context_

#include "EntitySystem.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "IClock.h"

namespace vsim
{
	class Context
	{
	public:
		friend Context& getContext();

		fire::EntitySystem& getEntitySystem();
		
		heat::PhysicsSystem& getPhysicsSystem();
		
		smoke::RenderSystem& getRenderSystem();

		framework::IClock& getClock();
		
		~Context();

	private:
		Context();
		
		Context(const Context&);

		class Impl;
		Impl* m_impl;
	};

	Context& getContext();
}

#endif