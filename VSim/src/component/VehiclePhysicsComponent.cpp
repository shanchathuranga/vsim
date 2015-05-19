#include "component/VehiclePhysicsComponent.h"
#include "message/VehicleTransformChangeMessage.h"
#include "message/VehicleDrivingDataChangeMessage.h"

namespace {
	static std::string typeName("VehiclePhysicsComponent");
}

namespace vsim
{
	const std::string& VehiclePhysicsComponent::getComponentName() const
	{
		return VehiclePhysicsComponent::getComponentNameStatic();
	}

	const std::string& VehiclePhysicsComponent::getComponentNameStatic()
	{
		return typeName;
	}

	VehiclePhysicsComponent::VehiclePhysicsComponent( heat::IPhysicsVehicleObject* physicsVehicleObject )
		: m_physicsVehicleObject(physicsVehicleObject)
	{

	}

	VehiclePhysicsComponent::~VehiclePhysicsComponent()
	{
		delete m_physicsVehicleObject;
	}

	void VehiclePhysicsComponent::update(fire::Entity* entity, heat::PhysicsSystem& physicsSystem)
	{
		// process messages
		while(const fire::Message* msg = next())
		{
			const VehicleDrivingDataChangeMessage* vMessage = dynamic_cast<const VehicleDrivingDataChangeMessage*>(msg);
			if (vMessage)
			{
				if (vMessage->getGasPadelPressed())
				{
					m_physicsVehicleObject->setEngineForce(3000.f);
				}
				else
				{
					m_physicsVehicleObject->setEngineForce(0.f);
				}
				if (vMessage->getBreakPadelPressed())
				{
					m_physicsVehicleObject->setBreakForce(100.f);
				}
				else
				{
					m_physicsVehicleObject->setBreakForce(0.f);
				}
				if (vMessage->getSteerDirection() == VehicleDrivingDataChangeMessage::LEFT)
				{
					m_physicsVehicleObject->setSteeringAngle(0.8f);
				}
				else if (vMessage->getSteerDirection() == VehicleDrivingDataChangeMessage::RIGHT)
				{
					m_physicsVehicleObject->setSteeringAngle(-0.8f);
				}
				else
				{
					m_physicsVehicleObject->setSteeringAngle(0.f);
				}
			}
			delete msg;
		}

		VehicleTransformChangeMessage* tMessage = new VehicleTransformChangeMessage();

		float m[16];
		m_physicsVehicleObject->getChassisTransformMatrix(m);
		tMessage->setChassisTransform(m);
		
		for (int i=0; i<4; i++)
		{
			float mm[16];
			m_physicsVehicleObject->getWheelTransformMatrix(i, mm);
			tMessage->setWheelTransform(i, mm);
		}

		std::string reciever("RenderComponent");
		entity->deliverMessage(reciever, tMessage);
	}

}