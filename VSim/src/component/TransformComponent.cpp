#include "component/TransformComponent.h"

namespace {
	static std::string typeName("TransformComponent");
}

namespace vsim
{
	TransformComponent::TransformComponent()
	{
		m_transform.identity();
	}

	TransformComponent::~TransformComponent()
	{
	}

	const std::string& TransformComponent::getComponentName() const
	{
		return TransformComponent::getComponentNameStatic();
	}

	const std::string& TransformComponent::getComponentNameStatic()
	{
		return typeName;
	}

	Matrix4f TransformComponent::getTransformMatrix()
	{
		return m_transform;
	}
}