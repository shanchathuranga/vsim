#ifndef _Component_
#define _Component_

#include <string>
#include <list>
#include "Message.h"

namespace fire
{
	class Component
	{
	public:
		virtual ~Component(){}
		virtual const std::string& getComponentName() const = 0;
	
		void addMessage(Message* msg)
		{
			m_mQ.push_back(msg);
		}
	
	protected:
		const Message* next()
		{
			Message* msg = NULL;
			if ( !m_mQ.empty() )
			{
				msg = m_mQ.front();
				m_mQ.pop_front();
			}
			return msg;
		}

	private:
		typedef std::list<Message*> MessageQueue;
		MessageQueue m_mQ;
	};
}


#endif