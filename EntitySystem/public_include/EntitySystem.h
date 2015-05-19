#ifndef _EntitySystem_
#define _EntitySystem_

#include <vector>

namespace fire
{
	class Entity;
	class EntitySystem
	{
	public:
		EntitySystem();
		~EntitySystem();
		Entity* createEntity();
		void deleteEntity(Entity* entity);

	private:
		long m_idGenerator;
		std::vector<Entity*> m_entities;
	};
}

#endif