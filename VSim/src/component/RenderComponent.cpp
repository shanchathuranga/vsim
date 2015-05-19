#include "component/RenderComponent.h"
#include "message/TransformChangeMessage.h"
#include "message/VehicleTransformChangeMessage.h"

namespace {
	static std::string typeName("RenderComponent");
}

namespace vsim
{

	const std::string& RenderComponent::getComponentName() const
	{
		return RenderComponent::getComponentNameStatic();
	}

	const std::string& RenderComponent::getComponentNameStatic()
	{
		return typeName;
	}

	RenderComponent::RenderComponent( smoke::IRenderObject* renderObject ) : m_renderObject(renderObject)
	{
		m_transform.identity();
	}

	RenderComponent::~RenderComponent()
	{
		delete m_renderObject;
	}

	void RenderComponent::update(fire::Entity* entity, smoke::RenderSystem& renderSystem)
	{
		while(const fire::Message* msg = next())
		{
			const TransformChangeMessage* tMessage = dynamic_cast<const TransformChangeMessage*>(msg);
			if (tMessage)
			{
				m_transform = tMessage->getTransform();
			}
			const VehicleTransformChangeMessage* vtMessage = dynamic_cast<const VehicleTransformChangeMessage*>(msg);
			if (vtMessage)
			{
				m_transform = vtMessage->getChassisTransform();
				m_renderObject->setChildTransform(std::string("front_left"), vtMessage->getWheelTransform(0));
				m_renderObject->setChildTransform(std::string("front_right"), vtMessage->getWheelTransform(1));
				m_renderObject->setChildTransform(std::string("rear_left"), vtMessage->getWheelTransform(2));
				m_renderObject->setChildTransform(std::string("rear_right"), vtMessage->getWheelTransform(3));
			}
			delete msg;
		}

		renderSystem.addToCurrentFrame(m_renderObject, m_transform);
	}
}