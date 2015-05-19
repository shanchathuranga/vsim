#ifndef _InputComponent_
#define _InputComponent_

#include "Component.h"
#include "Entity.h"
#include "IKeyBoard.h"

namespace vsim
{
	class InputComponent : public fire::Component
	{
	public:
		InputComponent();
		~InputComponent();
		const std::string& getComponentName() const;
		static const std::string& getComponentNameStatic();

		void update(fire::Entity* entity, framework::IKeyBoard& keyBoard);

	private:

	};
}

#endif