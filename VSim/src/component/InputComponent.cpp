#include "component/InputComponent.h"
#include "message/VehicleDrivingDataChangeMessage.h"

namespace {
	static std::string typeName("InputComponent");
}

namespace vsim
{

	const std::string& InputComponent::getComponentName() const
	{
		return InputComponent::getComponentNameStatic();
	}

	const std::string& InputComponent::getComponentNameStatic()
	{
		return typeName;
	}

	InputComponent::InputComponent()
	{

	}

	InputComponent::~InputComponent()
	{

	}

	void InputComponent::update( fire::Entity* entity, framework::IKeyBoard& keyBoard )
	{
		// process messages
		while(const fire::Message* msg = next())
		{
			delete msg;
		}

		VehicleDrivingDataChangeMessage* vMessage = new VehicleDrivingDataChangeMessage();
		vMessage->setSteerDirection(VehicleDrivingDataChangeMessage::NONE);

		if ( keyBoard.isKeyDown(framework::SK_LEFT) )
		{
			vMessage->setSteerDirection(VehicleDrivingDataChangeMessage::LEFT);
		}
		else if ( keyBoard.isKeyDown(framework::SK_RIGHT) )
		{
			vMessage->setSteerDirection(VehicleDrivingDataChangeMessage::RIGHT);
		}
		if ( keyBoard.isKeyDown(framework::SK_UP) )
		{
			vMessage->setGasPadelPressed(true);
		}
		else
		{
			vMessage->setGasPadelPressed(false);
		}
		if ( keyBoard.isKeyDown(framework::SK_DOWN) )
		{
			vMessage->setBreakPadelPressed(true);
		}
		else
		{
			vMessage->setBreakPadelPressed(false);
		}
		std::string reciever("VehiclePhysicsComponent");
		entity->deliverMessage(reciever, vMessage);	
	}

}