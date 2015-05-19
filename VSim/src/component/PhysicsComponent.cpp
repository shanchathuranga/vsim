#include "component/PhysicsComponent.h"
#include "message/TransformChangeMessage.h"

namespace {
	static std::string typeName("PhysicsComponent");
}

namespace vsim
{
	const std::string& PhysicsComponent::getComponentName() const
	{
		return PhysicsComponent::getComponentNameStatic();
	}

	const std::string& PhysicsComponent::getComponentNameStatic()
	{
		return typeName;
	}

	PhysicsComponent::PhysicsComponent(heat::IPhysicsObject* physicsObject) : m_physicsObject(physicsObject)
	{
		m_transform.identity();
	}

	PhysicsComponent::~PhysicsComponent()
	{
		delete m_physicsObject;
	}

	void PhysicsComponent::update(fire::Entity* entity, heat::PhysicsSystem& physicsSystem)
	{
		// process messages
		while(const fire::Message* msg = next())
		{
			delete msg;
		}

		float m[16];
		m_physicsObject->getTransformMatrix(m);
		TransformChangeMessage* tMessage = new TransformChangeMessage();
		tMessage->setTransform(Matrix4f::fromColumnMajorArray(m));
		std::string reciever("RenderComponent");
		entity->deliverMessage(reciever, tMessage);	
	}
}
