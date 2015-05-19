#ifndef _Entity_
#define _Entity_

#include "Component.h"
#include <vector>

namespace fire
{
	class Entity
	{
		typedef std::vector<Component*> ComponentVector;
	public:
		template <typename T> 
		T* const getComponent()
		{
			for (ComponentVector::iterator it = m_components.begin(), eit = m_components.end(); it != eit; ++it)
			{
				Component* comp = *it;
				if (T::getComponentNameStatic() == comp->getComponentName())
				{
					return static_cast<T*>(comp);
				}
			}
			return NULL;
		}

		void addComponent(Component* comp)
		{
			for (ComponentVector::iterator it = m_components.begin(), eit = m_components.end(); it != eit; ++it)
			{
				Component* compIt = *it;
				if (compIt->getComponentName() == comp->getComponentName())
				{
					return;
				}
			}
			m_components.push_back(comp);
		}

		long getID();
		void deliverMessage(std::string& receiver, Message* message);

	private:
		friend class EntitySystem;
		Entity(long eid);
		~Entity();

		long m_eID;
		ComponentVector m_components;
	};
}


#endif