#ifndef _RenderComponent_
#define _RenderComponent_

#include "Entity.h"
#include "RenderSystem.h"
#include "Component.h"
#include "IRenderObject.h"

namespace vsim
{
	class RenderComponent : public fire::Component
	{
	public:
		RenderComponent(smoke::IRenderObject* renderObject);
		~RenderComponent();
		const std::string& getComponentName() const;
		static const std::string& getComponentNameStatic();

		void update(fire::Entity* entity, smoke::RenderSystem& renderSystem);

	private:
		smoke::IRenderObject* m_renderObject;
		Matrix4f m_transform;
	};
}

#endif