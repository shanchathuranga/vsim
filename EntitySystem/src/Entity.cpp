#include "Entity.h"

namespace fire
{
	Entity::Entity(long eid)
	{
		m_eID = eid;
	}

	Entity::~Entity()
	{
		for (ComponentVector::iterator it = m_components.begin(), eit = m_components.end(); it != eit; ++it)
		{
			delete *it;
		}
	}

	long Entity::getID()
	{
		return m_eID;
	}

	void Entity::deliverMessage(std::string& receiverName, Message* message)
	{
		for (ComponentVector::iterator it = m_components.begin(), eit = m_components.end(); it != eit; ++it)
		{
			Component* comp = *it;
			if (comp->getComponentName() == receiverName)
			{
				comp->addMessage(message);
			}
		}
	}

}
