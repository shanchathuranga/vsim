#include "EntitySystem.h"
#include "Entity.h"

namespace fire
{

	EntitySystem::EntitySystem() : m_idGenerator(0)
	{
	}

	EntitySystem::~EntitySystem()
	{
		std::vector<Entity*>::iterator sit = m_entities.begin();
		std::vector<Entity*>::iterator eit = m_entities.end();
		while (sit != eit)
		{
			delete *sit;
			++sit;
		}
		m_entities.clear();
	}

	Entity* EntitySystem::createEntity()
	{
		Entity* entity = new Entity(m_idGenerator++);
		m_entities.push_back(entity);
		return entity;
	}

	void EntitySystem::deleteEntity(Entity* entity)
	{
		long eID = entity->getID();
		delete entity;

		std::vector<Entity*>::iterator sit = m_entities.begin();
		std::vector<Entity*>::iterator eit = m_entities.end();
		while (sit != eit)
		{
			Entity* ent = *sit;
			if (ent->getID() == eID)
			{
				m_entities.erase(sit);
				return;
			}
			++sit;
		}
	}

}