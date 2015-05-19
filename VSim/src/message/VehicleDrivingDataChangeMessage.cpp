#include "message/VehicleDrivingDataChangeMessage.h"

namespace vsim
{
	
	VehicleDrivingDataChangeMessage::VehicleDrivingDataChangeMessage()
	{
		m_direction = VehicleDrivingDataChangeMessage::NONE;
		m_pressGasPadel = false;
		m_pressBreakPadel = false;
	}

	VehicleDrivingDataChangeMessage::~VehicleDrivingDataChangeMessage()
	{

	}

	VehicleDrivingDataChangeMessage::SteerDirection VehicleDrivingDataChangeMessage::getSteerDirection() const
	{
		return m_direction;
	}

	void VehicleDrivingDataChangeMessage::setSteerDirection( VehicleDrivingDataChangeMessage::SteerDirection direction )
	{
		m_direction = direction;
	}

	bool VehicleDrivingDataChangeMessage::getGasPadelPressed() const
	{
		return m_pressGasPadel;
	}

	void VehicleDrivingDataChangeMessage::setGasPadelPressed( bool pressed )
	{
		m_pressGasPadel = pressed;
	}

	bool VehicleDrivingDataChangeMessage::getBreakPadelPressed() const
	{
		return m_pressBreakPadel;
	}

	void VehicleDrivingDataChangeMessage::setBreakPadelPressed( bool pressed )
	{
		m_pressBreakPadel = pressed;
	}

}