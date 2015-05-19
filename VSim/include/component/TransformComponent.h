#ifndef _TransformComponent_
#define _TransformComponent_

#include "Component.h"
#include "vmath.h"

namespace vsim
{
	class TransformComponent : public fire::Component
	{
	public:
		TransformComponent();
		~TransformComponent();
		const std::string& getComponentName() const;
		static const std::string& getComponentNameStatic();

		Matrix4f getTransformMatrix();

	private:
		Matrix4f m_transform;
	};
}

#endif